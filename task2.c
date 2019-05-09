#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#define SIZE 10


void printMatrix(int correlation[][SIZE], char wordList[][SIZE], FILE *outfile)
{
    char spacer [9] = "        ";
    printf("%*s", 8, spacer);
    fprintf(outfile, "%*s", 8, spacer);

    //print top row of words
    for (int i = 0; i < SIZE; i++)
    {
        char *ptr = NULL;
        ptr = (char *) malloc((sizeof(char) * 7));
        ptr = wordList[i];
        ptr[7] = '\0';
        fprintf(outfile, "%-*s ", 7, ptr);
        printf("%-*s ", 7, ptr);
    }
    fprintf(outfile, "\n");
    printf("\n");

    //print word first, followed by correlation matrix
    for(int i = 0; i < SIZE; i++)
    {
        char *ptr = NULL;
        ptr = (char *) malloc((sizeof(char) * 7));
        ptr = wordList[i];
        ptr[7] = '\0';
        fprintf(outfile, "%*s ", 7, ptr);
        printf("%*s ", 7, ptr);

        for(int j = 0; j < SIZE; j++)
        {
            fprintf(outfile, "%-*i ", 7, correlation[i][j]);
            printf("%-*i ", 7, correlation[i][j]);
        }
        fprintf(outfile, "\n");
        printf("\n");
        //free(ptr);
    }
}

int main()
{
//    FILE *inputfile = NULL;
    FILE *outfile = NULL;
//    char sentence[SIZE];
//    int count = 0;
//    char sentences[SIZE];
//
//    inputfile = fopen("wombat.txt", "r");
    outfile = fopen("testdata.correlation.txt", "w");
//
//    checkInfile(inputfile);

//    char ch;
//    int counter = 0;

    int correlation [SIZE][SIZE];

    char listofWords[SIZE][SIZE];

    int temparray[SIZE];
    int tempIndex = 0;

    strcpy(listofWords[0], "Test");
    strcpy(listofWords[1], "Jesse");
    strcpy(listofWords[2], "Samuel");
    strcpy(listofWords[3], "Danos");
    strcpy(listofWords[4], "Cook");
    strcpy(listofWords[5], "Freedcamp");
    strcpy(listofWords[6], "Github");
    strcpy(listofWords[7], "Gitlab");
    strcpy(listofWords[8], "Griffith");
    strcpy(listofWords[9], "CQUni");

    char sentence[] = "This is a Test sentence Jesse Github Cook CQUni.";

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            correlation[i][j] = 0;
        }
    }

    int size = strlen(sentence);
    char delimiter[] = " ";

    char *ptr = strtok(sentence, delimiter);

    //break sentence string into words
    while(ptr != NULL)
    {
        char word[SIZE];
        strcpy(word, ptr);
        int len = strlen(word);

        if(word[len-1] == '.')
        {
            word[len-1] = '\0';
        }

        int valid = validWord(word, len);

        //navigate through sentence word by word, check for word in list of words
        for(int i = 0; i < SIZE; i++)
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

        //navigate to coordinates of correlation matrix, increment value
        for (int i = 0; i < tempIndex; i++)
        {
            for(int j = i+1; j < tempIndex; j++)
            {
                correlation[temparray[i]][temparray[j]]++;
                correlation[temparray[j]][temparray[i]]++;
            }
        }

        printMatrix(correlation, listofWords, outfile);

    //fclose(inputfile);
    fclose(outfile);
    return 0;
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
