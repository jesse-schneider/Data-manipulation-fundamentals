#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 500

int longestWord(FILE *inputfile)
{
    char word[SIZE];
    int largeLen = 0;

    while(fscanf(inputfile, "%s", word) == 1)
    {
        int len = strlen(word);

        if(len > largeLen)
        {
            largeLen = len;
        }

    }
    return largeLen;
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

void checkInfile(FILE *infile)
{
  if(infile == NULL)
  {
      printf("error: unable to open file, please check path and re-run program.");
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

// int countArray(int temp[])
// {
//     int count = 0;
//     for(int i = 0; i != '\0'; i++)
//     {
//         count++;
//     }
//
//     return count;
// }
