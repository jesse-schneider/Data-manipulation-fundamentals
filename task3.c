#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int main()
{
    //init file pointer, const variables and count variables
    FILE *infile = NULL;
    FILE *histinfile = NULL;
    const char EOL = '\n';
    const char delimiter[] = " ";
    int lineChars = 0;
    int wordCount = 0;
    int tempIndex = 0;
    char c;

    infile = fopen("testdata.correlation.txt", "r");
    histinfile = fopen("", "r");


   checkInfile(infile);

   //count number of chars in top line for dynamic fgets
    while(c = getc(infile) != EOL)
    {
        lineChars++;
    }

    //init line string, add extra char for '\0'
    char line[lineChars+1];
    line[lineChars+1] = '\0';

    //return to file start, read in first line and store in char line[]
    fseek(infile, 0, SEEK_SET);
    fgets(line, lineChars, infile);

    //start after first block of chars, skip over excess spaces and
    //count the number of words in the line
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

    //init list of words array,
    char listofWords[wordCount][8];
    char *ptr = strtok(line, delimiter);

    //break sentence string into words
    while(ptr != NULL)
    {
      strcpy(listofWords[tempIndex], ptr);
      tempIndex++;
      ptr = strtok(NULL, delimiter);
    }

    //init correlation from file, and populate it
    int correlation [wordCount][wordCount];
    populateCorrelation(infile, wordCount, correlation);

    fclose(infile);

    char input[] = "CQUni";
    int topTen[wordCount];
    int topTenIndex[wordCount];
    int index = 0;
    int found = 0;

    for(int k = 0; k < wordCount; k++)
    {
      if(strcmp(input, listofWords[k]) == 0)
      {
        index = k;
        found = 1;
        break;
      }
    }

    if (found == 1)
    {
      //store correlation matrix row to compare, and it's indexs
      for(int i = 0; i < wordCount; i++)
      {
        topTen[i] = correlation[index][i];
        topTenIndex[i] = i;
      }

      sortforWord(topTen, topTenIndex, wordCount);

      //display top ten words and the number of occurences
      for(int i = 0; i < 10; i++)
      {
        printf("%i ", topTen[i]);
        printf("%s\n", listofWords[topTenIndex[i]]);
      }
    }
    else {
      printf("word not in correlation matrix\n");
    }
}
