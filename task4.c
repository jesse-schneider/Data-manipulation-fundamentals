#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int main()
{
  const char delimiter[] = " ";
  FILE *corrfile1 = NULL;
  FILE *corrfile2 = NULL;
  FILE *newcorrfile = NULL;
  int tempIndex = 0;

  char filename[20];
  char filename2[20];
  char histFilename[30];
  char histFilename2[30];
  char correlationFilename[30];
  char correlationFilename2[30];


  printf("Please enter 2 different files (without extensions) to be looking at: \n");
  scanf("%s %s", filename, filename2);

  ammendFileNames(filename, correlationFilename, histFilename);
  ammendFileNames(filename2, correlationFilename2, histFilename2);

  char newcorrFilename[50];
  strcpy(newcorrFilename, filename);
  strcat(newcorrFilename, "_");
  strcat(newcorrFilename, filename2);
  strcat(newcorrFilename, ".correlation.txt");

  corrfile1 = fopen(correlationFilename, "r");
  corrfile2 = fopen(correlationFilename2, "r");
  newcorrfile = fopen(newcorrFilename, "w");

  checkInfile(corrfile1, correlationFilename);
  checkInfile(corrfile2, correlationFilename2);

  //count number of chars in top line for dynamic fgets
   int max1 = findLargestLine(corrfile1);
   fseek(corrfile1, 0, SEEK_SET);
   int max2 = findLargestLine(corrfile2);
   fseek(corrfile2, 0, SEEK_SET);

   //dynamic pointers for the top row of the correlation
   char *line1 = NULL;
   char *line2 = NULL;
   line1 = malloc(max1 * sizeof(char));
   line2 = malloc(max2 * sizeof(char));

   fgets(line1, max1, corrfile1);
   fgets(line2, max2, corrfile2);

   int wordCount1 = getWordCount(line1);
   int wordCount2 = getWordCount(line2);
   int wordCount3;

   //create and allocate memory for word lists 1, 2 and list of all words combinedWords
   char **list1;
   char **list1Plus2;
   char ** list2;

   if(wordCount1 < wordCount2)
   {
     wordCount3 = wordCount2;
   }
   else
   {
     wordCount3 = wordCount1;
   }

   allocateWordsArray(wordCount1, &list1, 8);
   allocateWordsArray(wordCount2, &list2, 8);
   allocateWordsArray(wordCount3, &list1Plus2, 8);

   populateWordsList(line1, wordCount1, tempIndex, list1);
   tempIndex = 0;

   char *ptr = strtok(line2, delimiter);

   int iterator = 0;
   int combinedWords = 0;
   //break sentence string into words
   while(iterator < wordCount2)
   {
     strcpy(list2[iterator], ptr);
     for(int i = 0; i < wordCount1; i++)
     {
       int cmp = strcmp(list1[i], ptr);
       if(cmp == 0)
       {
         strcpy(list1Plus2[tempIndex], ptr);
         tempIndex++;
         combinedWords++;
         break;
       }
    }
    iterator++;
    ptr = strtok(NULL, delimiter);
  }

  tempIndex = 0;

  int corr1Ind[combinedWords];
  int corr2Ind[combinedWords];

  int **newCorr;
  allocateCorrArray(combinedWords, &newCorr);
  initArray(combinedWords, newCorr);

  for(int i = 0; i < combinedWords; i++)
  {
    for(int j = 0; j < wordCount1; j++)
    {
      if(strcmp(list1Plus2[i], list1[j]) == 0)
      {
        corr1Ind[tempIndex] = j;
        tempIndex++;
        break;
      }
    }
  }

  tempIndex = 0;

  for(int i = 0; i < combinedWords; i++)
  {
    for(int j = 0; j < wordCount2; j++)
    {
      if(strcmp(list1Plus2[i], list2[j]) == 0)
      {
        corr2Ind[tempIndex] = j;
        tempIndex++;
        break;
      }
    }
  }

  //free word lists, done with them
  freeWordArray(wordCount1, list1);
  freeWordArray(wordCount2, list2);

  tempIndex = 0;

   //init correlation from file, and populate it
   int **correlation1;
   int **correlation2;

   allocateCorrArray(wordCount1, &correlation1);
   allocateCorrArray(wordCount2, &correlation2);

   populateCorrelation(corrfile1, wordCount1, correlation1);
   populateCorrelation(corrfile2, wordCount2, correlation2);
   int sum;
   int sumArray[combinedWords];
   int sumIndexArray[combinedWords];
   int num = 0;

   //check both matrices, if they aren't 0, add result into combined matrix
   //also sum entire line, if > 0, then add to a matrix for sorting, and save index
   for(int i = 0; i < combinedWords; i++)
   {
     sum = 0;
     for(int j = 0; j < combinedWords; j++)
     {

       if(correlation1[corr1Ind[i]][corr1Ind[j]] != 0 && correlation2[corr2Ind[i]][corr2Ind[j]] != 0)
       {
         newCorr[i][j] = correlation1[corr1Ind[i]][corr1Ind[j]] + correlation2[corr2Ind[i]][corr2Ind[j]];
       }
       sum += newCorr[i][j];
     }
     sumArray[i] = sum;
     sumIndexArray[i] = i;

     if(sum != 0)
     {
       num++;
     }
   }
   freeCorrArray(wordCount1, correlation1);
   freeCorrArray(wordCount2, correlation2);

   //sort summed values, to get rid of zero values
   sort(sumArray, sumIndexArray, combinedWords);

   //init a correlation to the correct final size
   int **finalCorr;
   allocateCorrArray(num, &finalCorr);
   initArray(num, finalCorr);


   for(int i = 0; i < num; i++)
   {
     for(int j = 0; j < num; j++)
     {
       finalCorr[i][j] = newCorr[sumIndexArray[i]][sumIndexArray[j]];
     }
   }
   //free newCorr, done with
   freeCorrArray(combinedWords, newCorr);

   //init a list of words to the correct final size
   char **finalWords;
   allocateWordsArray(num, &finalWords, 8);

   for(int i = 0; i < num; i++)
   {
     strcpy(finalWords[i], list1Plus2[sumIndexArray[i]]);
   }
   //free list1Plus2, done with
   freeWordArray(wordCount3, list1Plus2);

   //print final correlation to file
   printMatrix(num, finalCorr, finalWords, newcorrfile);

   //free data after printing to file
   freeCorrArray(num, finalCorr);
   freeWordArray(num, finalWords);

   fclose(corrfile1);
   fclose(corrfile2);
   fclose(newcorrfile);
}
