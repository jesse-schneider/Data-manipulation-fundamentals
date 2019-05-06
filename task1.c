#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#define SIZE 500

struct Node {
    int count;
    struct Node *next;
    char word[SIZE];
};
typedef struct Node NODE;

NODE *head = NULL;

NODE * createNode(char wordIn[])
{
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Failed to create new node");
    }
    else
    {
        strncpy(newNode->word, wordIn, SIZE);
        newNode->count = 1;
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
    struct Node *nextNode = head;

    while(nextNode != NULL)
    {
        fprintf(outfile, " %7i %s \n", nextNode->count, nextNode->word);
        nextNode = nextNode->next;
    }
}

int checkForDuplicates(char word[])
{
    struct Node *nextNode = head;

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

int main()
{
    FILE *inputfile = NULL;
    FILE *outfile = NULL;
    char name[SIZE];
    int count = 0;

   inputfile = fopen("australia.txt", "r");
   outfile = fopen("australia.histogram.txt", "w");

    if (inputfile == NULL)
    {
        printf("Error opening file. \n");
        return 1;
    }

    while (fscanf(inputfile, "%s", name) == 1)
    {
        int len = strlen(name);

        int valid = validWord(name, len);
        int *valptr = NULL;
        valptr = &valid;

        if (checkForDuplicates(name) == 1)
        {
            *valptr = 1;
        }

        if (valid == 0)
        {
            NODE *addToList = createNode(name);
            insertAtHead(addToList);
            count++;
        }
    }
    printList(outfile);
    printf("Number of unique words found: %d \n", count);
    fclose(inputfile);
    fclose(outfile);
    return 0;
}
