
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* sumElements(void* arg);

int main() {
    int array[1000] = {0};
    pthread_t threadId[5] = {0};

    srand(time(NULL));
    int min = -1000;
    int max = 1000;
    int range = max - min + 1;
    int index;
    for (index = 0; index < 1000; index++)
    {
        array[index] = rand() % range + min;
    }

    for (index = 0; index < 1000; index++)
    {
        printf("%d, ", array[index]);
        printf("\n");
    }

    int temp = 0;
    for (index = 0; index < 1000; index++)
    {
        temp += array[index];
    }
    printf("Sum of elements = %d\n", temp);


    int start = 0;
    int threadNr[5] = {0};
    int i;
    for ( i = 0; i < 5; i++)
    {
        threadNr[i] = pthread_create(&threadId[i], NULL, &sumElements, (void*)(array + start));
        start = start + 200;
    }

    void *tempSum = 0;
    int threadsSum = 0;
    for (i = 0; i < 5; i++)
    {
        if (threadNr[i] == 0)
        {
            pthread_join(threadId[i], &tempSum);
            threadsSum += *(int*)tempSum;
            free(tempSum);
        }
        else
        {
            printf("Error.\n");
        }
    }
    printf("Sum of all array elements (threads)= %d\n", threadsSum);
return 0;
}

void* sumElements(void* arg)
{
    int* lokal = NULL;
    lokal = (int*)arg;

    int* result = NULL;
    result = (int*)malloc(sizeof(int));

    for(int i = 0; i < 200; i++)
    {
        *result = *result + lokal[i];
    }

    return (void*)result;
}
