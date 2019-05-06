#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int main()
{
    FILE *infile = NULL;
    const char EOL = '\n';
    const char delimiter[] = " ";
    int lineChars = 0;
    int wordCount = 0;
    int tempIndex = 0;
    char c;

    infile = fopen("testdata.correlation.txt", "r"); //windows input

   checkInfile(infile);

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

    for(int i = 0; i < wordCount; i++)
    {
      for(int j = 0; j < wordCount+1; j++)
      {
        char scan[8];
        if(fscanf(infile, "%s", &scan) != EOF)
        {
          if(j == 0)
          continue;

          int corint = atoi(scan);
          correlation[i][j-1] = corint;
        }
      }
    }
    fclose(infile);

    // for(int i = 0; i < wordCount; i++)
    // {
    //   for(int j = 0; j < wordCount; j++)
    //   {
    //     printf("%i ", correlation[i][j]);
    //   }
    //   printf("\n");
    // }

    // for(int i = 0; i < wordCount; i++)
    // {
    //   printf("%s \n", listofWords[i]);
    // }

    char input[] = "CQUni";
    int topTen[wordCount];
    int topTenIndex[wordCount];
    int index = 0;

    for(int k = 0; k < wordCount; k++)
    {
      if(strcmp(input, listofWords[k]) == 0)
      {
        index = k;
      }
    }

    //store correlation matrix row to compare, and it's indexs
    for(int i = 0; i < wordCount; i++)
    {
      topTen[i] = correlation[index][i];
      topTenIndex[i] = i;
    }

    sortforWord(topTen, topTenIndex, wordCount);

    //display top ten words and the number of occurences
    for(int i = 0; i < wordCount; i++)
    {
      printf("%i ", topTen[i]);
      printf("%s\n", listofWords[topTenIndex[i]]);
    }

}
