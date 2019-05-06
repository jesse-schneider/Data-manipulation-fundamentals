//
// Created by Jesse on 24/04/2019.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef PROG_FUND_HELPERS_H
#define PROG_FUND_HELPERS_H

int longestWord(FILE *inputfile);
int validWord(char name[], int len);
int skipSpaces(int i, char *str);
void checkInfile(FILE *infile);
void sortforWord(int topTen[], int topTenIndex[], int wordCount);
void populateCorrelation(FILE *infile, int wordCount, int correlation[][wordCount]);

#endif //PROG_FUND_HELPERS_H
