#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#include "linkedList.h"

int main()
{
    //init file pointer, const variables and count variables
    FILE *inputfile = NULL;
    FILE *histinfile = NULL;
    const char delimiter[] = " ";
    int wordCount = 0;
    int tempIndex = 0;

    char input[20];
    char filename[20];
    char histFilename[30];
    char correlationFilename[30];

    printf("Please enter a the file(without extensions) to be looking at: \n");
    scanf("%s", filename);

    ammendFileNames(filename, correlationFilename, histFilename);

    inputfile = fopen(correlationFilename, "r");
    histinfile = fopen(histFilename, "r");
    checkInfile(inputfile, correlationFilename);

    printf("please enter a 7 character word from the \ncorrelation matrix to find it's top ten most associated words: \n");
    scanf("%s", input);

   //count number of chars in top line for dynamic fgets
    int max = findLargestLine(inputfile);

    //init line string pointer
    char *line = NULL;
    line = malloc(max * sizeof(char));

    //return to file start, read in first line and store in char line[]
    fseek(inputfile, 0, SEEK_SET);
    fgets(line, max, inputfile);

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
    int **correlation;
    correlation = (int**)malloc(sizeof(int*)* wordCount);
    for (int i = 0; i < wordCount; i++)
    {
      correlation[i] = (int*)malloc(sizeof(int)* wordCount);
    }

    populateCorrelation(inputfile, wordCount, correlation);

    fclose(inputfile);

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

      sort(topTen, topTenIndex, wordCount);

      //display top ten words and the number of occurences
      for(int i = 0; i < 10; i++)
      {
        printf("%i ", topTen[i]);
        printf("%s \n", listofWords[topTenIndex[i]]);
      }
      for (int i = 0; i < wordCount; i++)
        free(correlation[i]);
      free(correlation);
    fclose(inputfile);
    }
    else {
      printf("word not in correlation matrix\n");

      checkInfile(histinfile, histFilename);

      int size = longestWord(histinfile);
      fseek(histinfile, 0, SEEK_SET);
      char *word = NULL;
      int occurence = 0;
      word = malloc(size * sizeof(char));

      while(fscanf(histinfile, "%i %s", &occurence, word) != EOF)
      {
        NODE *addToList = createNode(word, occurence, size);
        insertAtHead(addToList);
      }

      int popTopTen[wordCount];
      int popTopTenIndex[wordCount];

      char **listArr;
      listArr = (char**)malloc(sizeof(char*)* wordCount);
      for (int i = 0; i < wordCount; i++)
      {
        listArr[i] = (char*)malloc(sizeof(char)* size);
      }

      addToArray(popTopTen, popTopTenIndex, listArr);
      fclose(histinfile);

      sort(popTopTen, popTopTenIndex, wordCount);

      for(int i = 0; i < 10; i++)
      {
        printf("%i %s \n", popTopTen[i], listArr[popTopTenIndex[i]]);
      }
    }
}
