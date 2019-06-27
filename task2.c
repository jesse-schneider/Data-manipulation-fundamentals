#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"


int main()
{
    FILE *inputfile = NULL;
    FILE * histinfile = NULL;
    FILE *outfile = NULL;
    char filename[20];
    char histFilename[30];
    char correlationFilename[30];

    printf("please input a filename (without .txt extension) to generate a correlation matrix: \n");
    scanf("%s", filename);

    ammendFileNames(filename, correlationFilename, histFilename);
    strcat(filename, ".txt");

    inputfile = fopen(filename, "r");
    histinfile = fopen(histFilename, "r");
    checkInfile(inputfile, filename);
    checkInfile(histinfile, histFilename);

    outfile = fopen(correlationFilename, "w");

    int maxword = longestWord(inputfile);
    fseek(inputfile, 0, SEEK_SET);
    int max = findLargestLine(inputfile);
    fseek(inputfile, 0, SEEK_SET);


    int histMaxWord = longestWord(histinfile);
    fseek(histinfile, 0, SEEK_SET);
    int wordCount = countHistWords(histinfile, histMaxWord);
    fseek(histinfile, 0, SEEK_SET);


    int temparray[wordCount];
    int tempIndex = 0;

    int **correlation;
    allocateCorrArray(wordCount, &correlation);

    char **listofWords;
    allocateWordsArray(wordCount, &listofWords, histMaxWord);

    char sentence[max];

    initArray(wordCount, correlation);

    char *word = NULL;
    int occurence = 0;
    word = malloc(histMaxWord * sizeof(char));

    while(fscanf(histinfile, "%i %s", &occurence, word) == 2)
    {
      strcpy(listofWords[tempIndex], word);
      tempIndex++;
    }
    
    free(word);

    tempIndex = 0;
    fclose(histinfile);


      while(fgets(sentence, sizeof(sentence), inputfile) != NULL)
      {
          int size = strlen(sentence);
          char delimiter[] = " ";

          char *ptr = strtok(sentence, delimiter);

          //break sentence string into words
          while(ptr != NULL)
          {
              char word[maxword];
              strcpy(word, ptr);

              int len = strlen(word);

              if(word[len-1] == '.')
              {
                  word[len-1] = '\0';
              }
              int valid = validWord(word, len);

               if(valid != 0)
                break;

              //navigate through sentence word by word, check for word in list of words
              //if found, store index of word
              for(int i = 0; i < wordCount; i++)
              {
                  int compare = strcmp(word,listofWords[i]);
                  if (compare == 0)
                  {
                      temparray[tempIndex] = i;
                      temparray[tempIndex + 1] = '\0';
                      tempIndex++;
                  }
              }
              ptr = strtok(NULL, delimiter);
          }
      }
      fclose(inputfile);

      //navigate to coordinates of correlation matrix, increment value
      for (int i = 0; i < tempIndex; i++)
      {
          for(int j = i+1; j < tempIndex; j++)
          {
              correlation[temparray[i]][temparray[j]]++;
              correlation[temparray[j]][temparray[i]]++;
          }
      }

      //print correlation to file
      printMatrix(wordCount, correlation, listofWords, outfile);

      //free data
      for (int i = 0; i < wordCount; i++)
      {
        free(correlation[i]);
        free(listofWords[i]);
      }
   free(correlation);
   free(listofWords);

   fclose(outfile);
}
