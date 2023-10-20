#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//this could be confusing make note of the pointers
void* roll_dice()
{
    int value = (rand() % 6) + 1;   
    // printf("%d\n", value);
    int* result = malloc(sizeof(int));
    printf("thread result: %p\n",result);//checking the res values are the same
    *result = value;

    return (void*) result;
}

int main(int argc, char* argv[]){
    int* res;   //declaring the return vairable
    srand(time(NULL));
    pthread_t th;
    if(pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
        return 1;
    }
    if(pthread_join(th,(void**)&res) != 0){//assigning the return variable to the pointers
        return 2;
    }
    printf("Main res: %p\n",res);//checking if values are the same
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}