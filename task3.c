#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#define SIZE 10


int main()
{
    int correlation [SIZE][SIZE];
    char listofWords[SIZE][SIZE];

    FILE *infile = NULL;
    FILE *outfile = NULL;
    char EOL = '\n';

    //char *line = (char*) malloc(2 * sizeof(char));

    infile = fopen("C:\\Users\\Jesse\\CLionProjects\\Prog-fund\\testdata.histogram.txt", "r");
   // outfile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "w");

   if(infile == NULL)
   {
       printf("error opening file");
   }

    char delimiter[] = " ";

    int lineChars = 0;
    int temparray[SIZE];
    int tempIndex = 0;

    char c;

    while(c = fgetc(infile) != EOL)
    {
        lineChars++;
    }

    char line[lineChars];
    fseek(infile, 0, SEEK_SET);
    fgets(line, lineChars, infile);

    printf("%s", line);

    char *ptr = strtok(line, delimiter);

    //break sentence string into words
    while(ptr != NULL)
    {
        char word[7];
        strcpy(word, ptr);
        int len = strlen(word);

        if(word[len-1] == '.')
        {
            word[len-1] = '\0';
        }

        //navigate through sentence word by word, check for word in list of words
        for(int i = 0; i < SIZE; i++)
        {
              temparray[tempIndex] = word;
              temparray[tempIndex + 1] = '\0';
              tempIndex++;
            }
        }
        ptr = strtok(NULL, delimiter);
    }

    printf("%s", temparray);


}
