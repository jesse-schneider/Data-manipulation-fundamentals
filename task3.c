#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int skipSpaces(int i, char *str)
{
  if (str[i+1] != ' ')
  {
    return i+1;
  }
  else
  {
    skipSpaces(i+1, str);
  }
}

int main()
{
    FILE *infile = NULL;
    FILE *outfile = NULL;
    const char EOL = '\n';
    const char delimiter[] = " ";
    char *strcat;
    int lineChars = 0;
    int wordCount = 0;
    int tempIndex = 0;
    char c;

    infile = fopen("C:\\Users\\Jesse\\CLionProjects\\Prog-fund\\testdata.correlation.txt", "r"); //windows input
    //infile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "r");    //linux input
   // outfile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "w");
   // outfile = fopen("/home/jesse/Documents/Progfund-Assignment/testdata.histogram.txt", "w");   //linux output

   if(infile == NULL)
   {
       printf("error opening file");
   }

    while(c = getc(infile) != EOL)
    {
        lineChars++;
    }

    char line[lineChars+1];
    line[lineChars+1] = '\0';

    fseek(infile, 0, SEEK_SET);
    fgets(line, lineChars, infile);

    int i = 8;
    while(line[i] != '\0')
    {
      if(line[i] == ' ')
      {
        wordCount++;
        i = skipSpaces(i, line);
      }
      i++;
    }
    printf("wordcount: %i\n", wordCount);
    char listofWords[wordCount][8];
    char *ptr = strtok(line, delimiter);

    //break sentence string into words
    while(ptr != NULL)
    {
      strcpy(listofWords[tempIndex], ptr);
      tempIndex++;
      ptr = strtok(NULL, delimiter);
    }

    int correlation [wordCount][wordCount];
    fclose(infile);

    // for(int i = 0; i < wordCount; i++)
    // {
    //   printf("%s \n", listofWords[i]);
    // }

    char input[] = "CQUni";
}
