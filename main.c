#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100

struct Node {
    int count;
    struct Node *next;
    char word[SIZE];
};

struct Node *head = NULL;
struct Node *current = NULL;

struct Node* insertNewNode(char wordIn[])
{
    struct Node *newNode = (struct node*) calloc(1, sizeof(struct Node));
    strncpy(newNode->word, wordIn, SIZE);
    newNode->count = 1;
    newNode->next = head;
    head = newNode;
}

void printList() 
{
    struct Node *nextNode = head;
    int count = 0;
    
    while(nextNode != NULL)
    {
        printf(" %7i %s \n", nextNode->count, nextNode->word);
        nextNode = nextNode->next;
    }
}

int validWord(char name[], int len)
{
    int valid = 1;
    int *valptr = NULL;
    valptr = &valid;
    char ch;
    ch = name[0];
        
    if(isupper(ch) == 0)
    {
        return valid;
    }
        for(int i = 0; i < len; i++)
        {
            if (isalpha(name[i]) == 0)
            {
                *valptr = 1;
                break;
            } else 
            {
                *valptr = 0;
            }
        }
            return valid;
}

int checkForDuplicates(char word[]) 
{
    struct Node *nextNode = head;
    
     if(head == NULL) 
    {
        return NULL;
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
    char name[SIZE];
    int count;
    
    inputfile = fopen("/home/jesse/Documents/ProgrammingFund/AssignmentTask1/australia.txt", "r");
    
    if (inputfile == NULL) 
    {
        printf("Error opening file. \n");
        return 1;
    }
    count = 0;
    
    while (fscanf(inputfile, "%s", name) == 1)
    {
        int len = strlen(name);
        if (len < 4)
            continue;
     
        int valid = validWord(name, len);
        
        if (checkForDuplicates(name) == 1) 
        {
            valid = 1;
        }
        
        if (valid == 0)
        {
            insertNewNode(name);
            count++;
        }
    }
    printList();
    printf("Number of iterations: %i \n", count);
    
    fclose(inputfile);
    return 0;
}

