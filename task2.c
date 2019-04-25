#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#define SIZE 50

int main()
{
//    FILE *inputfile = NULL;
//    FILE *outfile = NULL;
//    char sentence[SIZE];
//    int count = 0;
//    char sentences[SIZE];
//
//    inputfile = fopen("/home/jesse/Documents/Progfund-Assignment/wombat.txt", "r");
//    //outfile = fopen("/home/jesse/Documents/Progfund-Assignment/wombat.histogram.txt", "w");
//
//    if (inputfile == NULL)
//    {
//        printf("Error opening file. \n");
//        return 1;
//    }
//    char ch;
//    int counter = 0;
    
    
    
    int correlation [SIZE][SIZE];
    
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            correlation[i][j] = 0;
            printf("%i", correlation[i][j]);
        }
    }
    
    
    
    
    
    
    //fclose(inputfile);
    //fclose(outfile);
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
 * 
 * /
