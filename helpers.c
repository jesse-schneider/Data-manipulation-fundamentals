#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 500

int longestWord(FILE *inputfile)
{
    char word[SIZE];
    int largeLen = 0;

    while(fscanf(inputfile, "%s", word) == 1)
    {
        int len = strlen(word);

        if(len > largeLen)
        {
            largeLen = len;
        }

    }
    return largeLen;
}