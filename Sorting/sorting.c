#include <stdio.h>
#include <stdlib.h>

void swap(int *pInt, int *pInt1);

void bubble_sort (int *bubbleSortedArray , int ArrSize)
{
    for (int i=1;i<ArrSize;i++)
        for(int j =ArrSize-1; j>=1; j--)
        {
            if(bubbleSortedArray[j]<bubbleSortedArray[j-1])
            {
                int bufor;
                bufor=bubbleSortedArray[j-1];
                bubbleSortedArray[j-1]=bubbleSortedArray[j];
                bubbleSortedArray[j]=bufor;
            }
        }
}

void insertion_sort(int *insertionSortedArray , int ArrSize)
{
    int bufor, j;
    for(int i=1; i<ArrSize; i++)
    {
        bufor = insertionSortedArray[i];
        j = i-1;
        while(j>=0 && insertionSortedArray[j]>bufor)
        {
            insertionSortedArray[j+1] = insertionSortedArray[j];
            --j;
        }
        insertionSortedArray[j+1] = bufor;
    }
}

void selection_sort(int *selectionSortedArray,int ArrSize)
{
    int j;
    int i;
    for (j = 0; j < ArrSize-1; j++)
    {
        int bufor = j;
        for (i = j+1; i < ArrSize; i++)
        {
            if (selectionSortedArray[i] < selectionSortedArray[bufor])
            {
                bufor = i;
            }
        }
        if(bufor != j)
        {
            int temp = selectionSortedArray[j];
            selectionSortedArray[j] = selectionSortedArray[bufor];
            selectionSortedArray[bufor] = temp;
        }
    }
}



int main() {
    int *bubbleSortedArray = 0;
    int *insertionSortedArray = 0;
    int *selectionSortedArray = 0;
    int ArrSize = 0;

    printf("How many numbers to sort: \n");
    scanf("%d", &ArrSize);

    bubbleSortedArray = malloc(sizeof(int) * ArrSize);
    insertionSortedArray = malloc(sizeof(int) * ArrSize);
    selectionSortedArray = malloc(sizeof(int) * ArrSize);

    printf("-------------: \n");

    for (int i = 0; i < ArrSize; i++) {
        if (i == 0) {
            printf("First number: \n");
        } else if (i == ArrSize - 1) {
            printf("Last number: \n");
        } else {
            printf("Next number: \n");
        }
        scanf("%d", &bubbleSortedArray[i]);
        insertionSortedArray[i] = bubbleSortedArray[i];
        selectionSortedArray[i] = bubbleSortedArray[i];
    }
    printf("-------------: \n");
    printf("Bubble sorting: \n");
    bubble_sort(bubbleSortedArray, ArrSize);
    for (int i = 0; i < ArrSize; i++) {
        printf("%d ", bubbleSortedArray[i]);

    }
    printf("\n");

    printf("Insertion sorting: \n");
    insertion_sort(insertionSortedArray, ArrSize);
    for (int i = 0; i < ArrSize; i++) {
        printf("%d ", insertionSortedArray[i]);
    }
    printf("\n");


    printf("Selection sorting: \n");
    selection_sort(selectionSortedArray, ArrSize);
    for (int i = 0; i < ArrSize; i++) {
        printf("%d ", selectionSortedArray[i]);
    }
    printf("\n");
    free(bubbleSortedArray);
    free(insertionSortedArray);
    free(selectionSortedArray);

    return 0;
}

