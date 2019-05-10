#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

NODE *head = NULL;

NODE * createNode(char wordIn[], int countInit, int size)
{
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Failed to create new node");
    }
    else
    {
      newNode->word = malloc(size * sizeof(char));
        strncpy(newNode->word, wordIn, size);
        newNode->count = countInit;
        newNode->next = NULL;
    }
    return newNode;
}

void insertAtHead(NODE *newNode)
{
    NODE *ptr = head;

    if(ptr == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

void printList(FILE *outfile)
{
    NODE *nextNode = head;

    while(nextNode != NULL)
    {
        fprintf(outfile, " %7i %s \n", nextNode->count, nextNode->word);
        nextNode = nextNode->next;
    }
}

void outputList()
{
    NODE *nextNode = head;

    while(nextNode != NULL)
    {
        printf(" %7i %s \n", nextNode->count, nextNode->word);
        nextNode = nextNode->next;
    }
}

int checkForDuplicates(char word[])
{
    NODE *nextNode = head;

     if(head == NULL)
    {
        return 0;
    }

    while(nextNode != NULL)
    {
        if (strcmp(word, nextNode->word) == 0)
        {
            nextNode->count++;
            return 1;
        }
        nextNode = nextNode->next;
    }
    return 0;
}

void addToArray(int popTopTen[], int popTopTenIndex[], char **list)
{
  NODE *nextNode = head;
  int inx = 0;

  while(nextNode != NULL)
  {
      popTopTen[inx] = nextNode->count;
      strcpy(list[inx], nextNode->word);
      popTopTenIndex[inx] = inx;

      inx++;

      nextNode = nextNode->next;
  }

}
