#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// void* routine(){
//     printf("begining of threads\n");
//     sleep(3);
//         printf("end of threads\n");

//     return NULL;
// }
int mails = 0;
pthread_mutex_t mutex;
void* routine()
{
    for (int i = 0; i < 10000000; i++)//this code,witout the mutext. when running 1 thread is meant to return a million running two should give 2m..but its not so due to some theory explained in yt aint writing allat
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }//so basically with the mutex some shit happens aint writing allat but it works
    return NULL;
    
}//run  gcc -S main.c -pthread and go to main.s

int main(int argc, char* argv[])
{

    //Threads share memories..they use the same memory address what ever happens to a value of a  variable  in one thread gets affected by the other.
    

    // pthread_t t1,t2;
    // pthread_mutex_init(&mutex,NULL);  

    //creating a basic thread
    // pthread_create(&t1, NULL, routine, NULL);
    // pthread_create(&t2, NULL, routine, NULL);


    //threads as arrays


    if (argc != 2){
        printf("wrong number of arguments");
    }

    int n = atoi(argv[1]);
    pthread_t th[n];
    pthread_mutex_init(&mutex,NULL);  
    for (int i = 0; i < n; i++)
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n",i+1);//returning the particular thread in execution
        
    }

    for (int i = 0; i < n; i++)
    {
        
        if(pthread_join(th[i], NULL) != 0){
            perror("failed to join thread");
            return 2;
        }

        printf("Thread %d has finished\n",i);//dont put the join and create function in the same forloop itll sequentially which defeats its purpose
    }
    
    


    //way of writing threads with exception handling
    // if(pthread_create(&t1, NULL, &routine, NULL) != 0){
    //     return 1;
    // }
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);


    pthread_mutex_destroy(&mutex);
    printf("%d",mails);


    return 0;
}

