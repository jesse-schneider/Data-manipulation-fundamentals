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
      printf("error: unable to open file: %s please check path and re-run program.", filename);
      exit(1);
  }
}

void sortforWord(int topTen[], int topTenIndex[], int wordCount)
{
  for(int i = 0; i < 10; i++)
  {
    for(int j = i + 1; j < wordCount; j++)
    {
      if(topTen[i] < topTen[j])
      {
        int temp = topTen[i];
        int tempI = topTenIndex[i];

        topTen[i] = topTen[j];
        topTenIndex[i] = j;

        topTen[j] = temp;
        topTenIndex[j] = i;
      }
    }
  }
}

void populateCorrelation(FILE *infile, int wordCount, int correlation[][wordCount])
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

int half2DArray(int wordCount)
{
  int size = 0;
  while(wordCount != 0)
  {
    size += wordCount;
    wordCount--;
  }
  return size;
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
