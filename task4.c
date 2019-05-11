#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

void printMatrix(int wordCount, int **correlation, char **wordList, FILE *outfile)
{
    printf("Generating combined matrix...");
    char spacer [9] = "        ";
    fprintf(outfile, "%*s", 8, spacer);

    //print top row of words
    for (int i = 0; i < wordCount; i++)
    {
        char *ptr = NULL;
        ptr = (char *) malloc((sizeof(char) * 7));
        ptr = wordList[i];
        ptr[7] = '\0';
        fprintf(outfile, "%-*s ", 7, ptr);
    }
    fprintf(outfile, "\n");

    //print word first, followed by correlation matrix
    for(int i = 0; i < wordCount; i++)
    {
        char *ptr = NULL;
        ptr = (char *) malloc((sizeof(char) * 7));
        ptr = wordList[i];
        ptr[7] = '\0';
        fprintf(outfile, "%*s ", 7, ptr);
        //printf("%*s ", 7, ptr);

        for(int j = 0; j < wordCount; j++)
        {
            fprintf(outfile, "%-*i ", 7, correlation[i][j]);
        }
        fprintf(outfile, "\n");
    }
    printf("Matrix combined Generated!");
}

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


  printf("Please enter a the file(without extensions) to be looking at: \n");
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

   char *line1 = NULL;
   char *line2 = NULL;
   line1 = malloc(max1 * sizeof(char));
   line2 = malloc(max2 * sizeof(char));

   fgets(line1, max1, corrfile1);
   fgets(line2, max2, corrfile2);

   int wordCount1 = getWordCount(line1);
   int wordCount2 = getWordCount(line2);

   char **list1;
   char **list1Plus2;
   char ** list2;

   int wordCount3;
   if(wordCount1 < wordCount2)
   {
     wordCount3 = wordCount2;
   }
   else
   {
     wordCount3 = wordCount1;
   }

   //allocateArray(wordCount1, list1);
   list1 = (char**)malloc(sizeof(char*)* wordCount1);
   for (int i = 0; i < wordCount1; i++)
   {
     list1[i] = (char*)malloc(sizeof(char)* 8);
   }

   list1Plus2 = (char**)malloc(sizeof(char*)* wordCount3);
   for (int i = 0; i < wordCount3; i++)
   {
     list1Plus2[i] = (char*)malloc(sizeof(char)* 8);
   }

   list2 = (char**)malloc(sizeof(char*)* wordCount2);
   for (int i = 0; i < wordCount2; i++)
   {
     list2[i] = (char*)malloc(sizeof(char)* 8);
   }

   populateWordsList(line1, wordCount1, tempIndex, list1);
   tempIndex = 0;

   char *ptr = strtok(line2, delimiter);

   int count = 0;
   int combinedWords = 0;
   //break sentence string into words
   while(count < wordCount2)
   {
     strcpy(list2[count], ptr);
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
    count++;
    ptr = strtok(NULL, delimiter);
  }
  tempIndex = 0;

  int corr1Ind[combinedWords];
  int corr2Ind[combinedWords];

  int **newCorr;
  newCorr = (int**)malloc(sizeof(int*)* combinedWords);
  for (int i = 0; i < combinedWords; i++)
  {
    newCorr[i] = (int*)malloc(sizeof(int)* combinedWords);
  }

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
  tempIndex = 0;

   //init correlation from file, and populate it
   int **correlation1;
   int **correlation2;

   correlation1 = (int**)malloc(sizeof(int*)* wordCount1);
   for (int i = 0; i < wordCount1; i++)
   {
     correlation1[i] = (int*)malloc(sizeof(int)* wordCount1);
   }

   correlation2 = (int**)malloc(sizeof(int*)* wordCount2);
   for (int i = 0; i < wordCount2; i++)
   {
     correlation2[i] = (int*)malloc(sizeof(int)* wordCount2);
   }

   populateCorrelation(corrfile1, wordCount1, correlation1);
   populateCorrelation(corrfile2, wordCount2, correlation2);
   int sum;
   int sumArray[combinedWords];
   int sumIndexArray[combinedWords];
   int num = 0;

   //check both matrices, if they aren't 0, add result into combined matrix
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

   int temp = 0;
   int tempI = 0;

   for(int i = 0; i < combinedWords; i++)
   {
     for(int j = i+1; j < (combinedWords-1); j++)
     {
       if(sumArray[i] < sumArray[j])
       {
         temp = sumArray[i];
         tempI = sumIndexArray[i];

         sumArray[i] = sumArray[j];
         sumIndexArray[i] = sumIndexArray[j];

         sumArray[j] = temp;
         sumIndexArray[j] = tempI;
       }
     }
   }

   int **finalCorr;
   finalCorr = (int**)malloc(sizeof(int*)* num);
   for (int i = 0; i < num; i++)
   {
     finalCorr[i] = (int*)malloc(sizeof(int)* num);
   }

   initArray(num, finalCorr);

   for(int i = 0; i < num; i++)
   {
     for(int j = 0; j < num; j++)
     {
       finalCorr[i][j] = newCorr[sumIndexArray[i]][sumIndexArray[j]];
     }
   }

   char **finalWords;
   finalWords = (char**)malloc(sizeof(char*)* num);
   for (int i = 0; i < num; i++)
   {
     finalWords[i] = (char*)malloc(sizeof(char*)* 8);
   }

   for(int i = 0; i < num; i++)
   {
     strcpy(finalWords[i], list1Plus2[sumIndexArray[i]]);
   }

   printMatrix(num, finalCorr, finalWords, newcorrfile);


   fclose(corrfile1);
   fclose(histinfile1);
   fclose(corrfile2);
   fclose(histinfile2);
   fclose(newcorrfile);
}
