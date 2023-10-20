#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg)
{
    //  sleep(1);
     int index = *(int*) arg; 
     printf("%d ",primes[index]);
     free(arg);
     return NULL;
}
   


int main(int argc, char* argv[])
{
    int n = 2;
    pthread_t th[n];

    for (int i = 0; i < n; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL,&routine,a) != 0)
        {
            return 1;
        }
        
    }

    for (int i = 0; i < n; i++)
    {
        if(pthread_join(th[i], NULL) != 0){
            perror("failed to join thread");
        }
    }
    
       
    return 0;
}