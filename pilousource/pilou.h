#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int pilouargc, char const **pilouargv);

/* Execute line args */
short pilou(char const **pilouargv);

/* Check line args */
short pilouargs(int pilouargc, char const **pilouargv);

/* Compile pilou file to brainfuck */
short piloubrainfuck(char const *piloupath);

/* Compile pilou file to c */
short pilouc(char const *piloupath);

/* Print help */
void pilouhelp();

/* Read next command in file */
short pilouread(FILE *piloureadptr);
