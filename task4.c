#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int main()
{
    FILE *inputfile = NULL;
    FILE *outfile = NULL;
    char sentence[SIZE];
    
    
    

 
    return 0;
}


/*
 * 
 * 1. Read in both histograms and corr matrices
 * 2. Create an array containing all the words contained in both histograms - called ComboArr
 * 3. Create 2 arrays of the indexes of words in both histograms, both separate (should be same len as other array)
 * 4. Bonus meme -> Create an array where all the values above are saved as a struct
 * 5. Perform look up using comboArr as index, to both other indexes, then check values in both Corrs
 * 6. If both more than 1, add numbers, else if either numbers equal 0, don't plot
 * 7.
 * 8.
 * 9.
 * 10.
 * 
 * 
 * /