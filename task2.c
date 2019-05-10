#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

void printMatrix(int wordCount, int histMaxWord, int **correlation, char **wordList, FILE *outfile)
{
    printf("Generating matrix...");
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
    printf("Matrix Generated!");
}

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
    correlation = (int**)malloc(sizeof(int*)* wordCount);
    for (int i = 0; i < wordCount; i++)
    {
      correlation[i] = (int*)malloc(sizeof(int)* wordCount);
    }

    char **listofWords;
    listofWords = (char**)malloc(sizeof(char*)* wordCount);
    for (int i = 0; i < wordCount; i++)
    {
      listofWords[i] = (char*)malloc(sizeof(char)* histMaxWord);
    }

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

      printMatrix(wordCount, histMaxWord, correlation, listofWords, outfile);

      for (int i = 0; i < wordCount; i++)
      {
        free(correlation[i]);
        free(listofWords[i]);
      }
   free(correlation);
   free(listofWords);

   fclose(outfile);
}


/*
 *
 * 1. Create 2D array with len = Listofwords, initiate all [i][j] as 0
 * 2. Read in a sentence word by word until '.', compare word to listofwords, if yes, add word index to temp array
 * 3. (output only) Print List of words as first array
 * 4. Iterate 2D loop through each index, ignoring what is on the left of it
 * 5. Add 1 to value in 2D array at each other index in temp array, 2D array [i][j] and [j][i] i = word1Tempindex, j = word2Tempindex
 * 6. Repeat until EOF
 * */
