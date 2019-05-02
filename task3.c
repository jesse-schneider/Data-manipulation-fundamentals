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
    char delimiter[] = " ";
    int lineChars = 0;
    int wordCount = 0;
    int tempIndex = 0;
    char c;

    infile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "r");
    //infile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "r");    //linux input
   // outfile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "w");
   // outfile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "w");   //linux output

   if(infile == NULL)
   {
       printf("error opening file");
   }

    while(c = fgetc(infile) != EOL)
    {
        lineChars++;
    }

    char line[lineChars];
    fseek(infile, 0, SEEK_SET);
    fgets(line, lineChars, infile);

    char *ptr = strtok(line, delimiter);

    //break sentence string into words
    while(ptr != NULL)
    {
        char word[7];
        strcpy(word, ptr);
        int len = strlen(word);

        //iterate through chars in word, add to list of words at tempIndex
        for(int j = 0; j < len + 1; j++)
        {
          listofWords[tempIndex][j] = word[j];
        }
        listofWords[tempIndex][len + 1] = '\0';

        tempIndex++;

          ptr = strtok(NULL, delimiter);
         }

          for(int i = 0; i < SIZE; i++)
          {
            printf("[%s] \n", listofWords[i]);
          }
      fclose(infile);
}
