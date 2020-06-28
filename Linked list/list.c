#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int value;
    struct Node *next;
}Node;

struct List
{
    Node * head;
};

typedef struct List List;

// create and returns instance of List
List * create_list(void)
{
    List *list = malloc(sizeof(Node));
    list->head=NULL;
    return list;

}

// releases all memory used by list, list is set to NULL
void destroy_list(List ** list)
{
    if (0 != list)
    {
        if(NULL ==*list)
        {
            printf("List doesn't exist\n");
            return;
        }
        else
        {
            free(*list);
            *list = NULL;
        }
        printf("List destroyed\n");
    }
    else
    {
        printf("Invalid Pointer\n");
    }
}

// return amount of elements in list
int count_elements(List *list)
{
    int counter = 0;
    Node *nodePtr=list->head;
    if (0 != list)
    {
        while (NULL!=nodePtr)
        {
            counter++;
            nodePtr=nodePtr->next;
            printf("ptr %p\n", nodePtr);
        }
        printf("Nr of elements: %d\n", counter);
    }
    else
    {
        printf("Invalid Pointer\n");
    }
    return counter;
}

// append element to list at the end
void append_to_list(List *list, int elem)
{
    if (0 != list)
    {
        Node* newNode =malloc(sizeof(Node));
        newNode ->value=elem;
        newNode ->next=NULL;
        if(NULL==list->head)
        {
            list->head= newNode;
        }
        else
        {
            Node* lastNode =list->head;
            while(NULL!=lastNode->next)
            {
                lastNode=lastNode->next;
            }
            lastNode->next=newNode;
        }
    }
    else
    {
        printf("Invalid Pointer\n");
    }
}
// elements are indexed from 0
int get_nth_element(List * list, int index)
{
    int returnValue = 0;
    if(0 != list)
    {
        Node* nodePtr = list->head;
        if(0 != nodePtr)
        {
            int counter = 0;
            while(0 != nodePtr)
            {
                if(index == counter)
                {
                    returnValue = nodePtr->value;
                    printf("Value from index [%d] is %d\n", index, returnValue);
                    break;
                }
                else
                {
                    if(0 != nodePtr->next)
                    {
                        nodePtr = nodePtr->next;
                        counter++;
                    }
                    else
                    {
                        printf("There is no index [%d] \n", index);
                        break;
                    }
                }
            }
        }
        else
        {
            printf("List is empty\n");
        }
    }
    else
    {
        printf("Invalid Pointer\n");
    }
    return returnValue;
}

// remove nth element - indexed from 0
void remove_nth_element(List * list, int index)
{
    if(0 != list)
    {
        Node *temp = list->head;
        Node *nextNode = NULL;
        if (NULL==list->head)
        {
            printf("List is empty\n", index);
            return;
        }
        if (0 == index)
        {
            list->head = temp->next;
            free(temp);
            printf("Index [%d] was removed\n", index);
        }
        else
        {
            int i = 1;
            while (i <= index - 1)
            {
                temp = temp->next;
                i++;
            }
            nextNode = temp->next;
            temp->next = nextNode->next;
            free(nextNode);
        }
    }
    else
    {
        printf("List is empty\n");
    }
}

// clear list - remove all elements
void clear_list(List * list)
//{
//    if(NULL != list)
//    {
//        if(NULL == list->head)
//        {
//            printf("List is empty\n");
//        }
//        else if(NULL == list->head->next)
//        {
//            free(list->head);
//            list->head = NULL;
//            printf("Head Element cleared, list is empty\n");
//        }
//        else
//        {
//            Node *prevNode = list->head;
//            Node *nodePtr = list->head;
//            while (nodePtr->next != 0)
//            {
//                prevNode = nodePtr;
//                nodePtr = nodePtr->next;
//                if(NULL == nodePtr->next)
//                {
//                    free(nodePtr);
//                    prevNode->next = NULL;
//                    printf("Last element cleared, left: %d\n", count_elements(list));
//                    break;
//                }
//            }
//        }
//    }
//    else
//    {
//        printf("Invalid Pointer\n");
//    }
//}
{
    Node *node = list->head;
    node = list->head;

    while (node->next->next != 0)
    {
        node = node->next;
    }

    free(node->next);
    node->next = NULL;
    free(node);
    list->head = NULL;
}

void insert_to_list(List * list, int elem, int index)
{
    Node* node = list->head;
    int counter = -1;

    if (0==index)
    {
        if (NULL == list->head)
        {
            append_to_list(list, elem);
            return;
        }
    }
    while (0 !=node->next)
    {
        counter++;
        if (counter == index)
        {
            break;
        }
        node = node->next;
    }
    if(counter+1 < index)
    {
        append_to_list(list, elem);
        return;
    }
    Node* swap = (Node*)malloc(sizeof(Node));
    if(NULL==swap)
    {
        exit (-1);
    }
    swap->value = node->value;
    swap->next = node->next;
    node->value = elem;
    node->next = swap;
}

// sort elements in list
void sort_list(List * list)
{
    assert(list);
    int cnt = count_elements(list);
    if (cnt<2) return;

    for (int end=cnt-1; end>0; --end)
    {
        int noswap = 1;
        Node * n1 = list->head;
        for (int pos=0; pos<end; ++pos)
        {
            Node * n2 = n1->next;
            if (n1->value > n2->value) {
                int tmp = n1->value;
                n1->value = n2->value;
                n2->value = tmp;
                noswap = 0;
            }
            n1 = n2;
        }
        if (noswap) return;
    }
}
// reverse list
void reverse_list(List * list)
{
    if(NULL != list)
    {
        if (NULL != list->head)
        {
            Node *node=list->head;
            Node *prevNode=NULL;
            Node *nextNode=node->next;

            while (NULL != node)
            {
                node->next=prevNode;
                prevNode=node;
                node=nextNode;

                if (NULL != nextNode)
                {
                    nextNode=nextNode->next;
                }
            }
            list->head=prevNode;
        }
        else
        {
            printf("List is empty\n");
        }
    }
    else
    {
        printf("Invalid Pointer\n");
    }
}