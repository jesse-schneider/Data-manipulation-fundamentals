#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longestWord(FILE *inputfile)
{
    char *word = malloc(500 * sizeof(char));
    int largeLen = 0;

    while(fscanf(inputfile, "%s", word) == 1)
    {
        int len = strlen(word);

        if(len > largeLen)
        {
            largeLen = len;
        }
    }
    free(word);
    return largeLen;
}

int countHistWords(FILE *histfile, int histMaxWord)
{
  int words = 0;
  int occurence;
  char *word = malloc(histMaxWord * sizeof(char));

    while(fscanf(histfile, "%i %s", &occurence, word) != EOF)
    {
        words++;
    }
    return words;
}

void initArray(int wordCount, int **array)
{
  for(int i = 0; i < wordCount; i++)
  {
      for(int j = 0; j < wordCount; j++)
      {
          array[i][j] = 0;
      }
  }
}

int validWord(char name[], int len)
{
    int valid = 1;
    int isUp = 0, isLow = 0;

    if(name[0] < 'A' || name[0] > 'Z')
    {
        return valid;
    }
        for(int i = 0; name[i] != '\0'; i++)
        {
            if (name[i] >= 'A' && name[i] <= 'Z')
            {
                isUp = 1;

            } else if (name[i] >= 'a' && name[i] <= 'z')
            {
                isLow = 1;

            } else
            {
                valid = 1;
                break;
            }

            if(isUp == 1 && isLow == 1)
            {
                valid = 0;
            }
        }
        return valid;
}

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

void checkInfile(FILE *infile, char *filename)
{
  if(infile == NULL)
  {
      printf("error: unable to open file: %s please check path and re-run program.\n", filename);
      exit(1);
  }
}

void sort(int topTen[], int topTenIndex[], int wordCount)
{
  int temp = 0;
  int tempI = 0;
  for(int i = 0; i < 10; i++)
  {
    for(int j = i+1; j < (wordCount-1); j++)
    {
      if(topTen[i] < topTen[j])
      {
        temp = topTen[i];
        tempI = topTenIndex[i];

        topTen[i] = topTen[j];
        topTenIndex[i] = topTenIndex[j];

        topTen[j] = temp;
        topTenIndex[j] = tempI;
      }

    }

  }
}

void populateCorrelation(FILE *infile, int wordCount, int **correlation)
{
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
}

int findLargestLine(FILE *inputfile)
{
  int lineChars = 0;
  int max = 0;
  char c;

  while(c = getc(inputfile) != EOF)
  {
     if(c!='\n')
     {
       lineChars++;
     }
     if(lineChars > max)
     {
       max = lineChars;
     }
  }
  return max;
}
void ammendFileNames(char *filename, char *correlationFilename, char *histFilename)
{
  strcpy(correlationFilename, filename);
  strcpy(histFilename, filename);

  strcat(histFilename, ".histogram.txt");
  strcat(correlationFilename, ".correlation.txt");
}

int getWordCount(char *line)
{
  //start after first block of chars, skip over excess spaces and
  //count the number of words in the line
  int wordCount = 0;
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
  return wordCount;
}

void allocateArray(int wordCount, char **list)
{
  list = (char**)malloc(sizeof(char*)* wordCount);
  
  for (int i = 0; i < wordCount; i++)
  {
    list[i] = (char*)malloc(sizeof(char)* 8);
  }
}

void  populateWordsList(char *line, int wordCount, int tempIndex, char **listofWords)
{
  const char delimiter[] = " ";

  char *ptr = strtok(line, delimiter);

  //break sentence string into words
  while(tempIndex < wordCount)
  {
    strcpy(listofWords[tempIndex], ptr);
    tempIndex++;
    ptr = strtok(NULL, delimiter);
  }
}
