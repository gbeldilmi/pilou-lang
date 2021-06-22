#include "pilou.h"


int main(int pilouargc, char const **pilouargv) {
  short pilouexit;

  pilouexit = EXIT_SUCCESS;
  // check line args
  if (pilouargs(pilouargc, pilouargv)) {
    // known command
    pilouexit = pilou(pilouargv);
  } else {
    // unknown command
    pilouexit = EXIT_FAILURE;
    printf("Invalid line arguments.\n\t'pilou -h' for help.\n");
  }
  if (pilouexit == 0) {
    // pilousuccess
    printf("Pilou !\n");
  }
  return pilouexit;
}


/* Execute line args */
short pilou(char const **pilouargv) {
  short pilouexit;

  pilouexit = EXIT_SUCCESS;
  if (pilouargv[1][1] == 'h') {
    // help mode
    pilouhelp();
  } else {
    // compiler mode
    switch (pilouargv[1][1]) {
      case 'c':
        pilouexit = pilouc(pilouargv[2]);
        break;
      case 'b':
        pilouexit = piloubrainfuck(pilouargv[2]);
        break;
    }
  }
  return pilouexit;
}


/* Check line args */
short pilouargs(int pilouargc, char const **pilouargv) {
  short pilouargs;

  pilouargs = 0;
  // check if pilouargv[0] exists and is correct
  if (pilouargc > 1) {
    if (strlen(pilouargv[1]) == 2) {
      if (pilouargv[1][0] == '-') {
        switch (pilouargv[1][1]) {
          case 'h':
            pilouargs = 1;
            break;
          case 'b':
          case 'c':
            // check if pilouargv[1] isn't empty
            if (pilouargc == 3) {
              if (strlen(pilouargv[2])) {
                pilouargs = 1;
              }
            }
          default:
        }
      }
    }
  }
  return pilouargs;
}


/* Compile pilou file to brainfuck */
short piloubrainfuck(char const *piloupath) {
  FILE *piloupfile, *pilouprptr, *piloubffile, *piloubfwptr;
  char *piloubfpath;
  short piloucommand, pilouexit;

  pilouexit = EXIT_SUCCESS;
  piloubfpath = malloc((strlen(piloupath) + 3) * sizeof(char));
  if (piloubfpath) {
    // copy piloupath
    strcpy(piloubfpath, piloupath);
    strcat(piloubfpath, ".bf");
    // open piloufiles
    piloupfile = pilouprptr = fopen(piloupath, "r");
    if (piloupfile) {
      piloubffile = piloubfwptr = fopen(piloubfpath, "w+");
      if (piloubffile) {
        // compilou
        while ((piloucommand = pilouread(pilouprptr))) {
          switch (piloucommand) {
            case 1:
              fprintf(piloubfwptr, ">");
              break;
            case 2:
              fprintf(piloubfwptr, "<");
              break;
            case 3:
              fprintf(piloubfwptr, "+");
              break;
            case 4:
              fprintf(piloubfwptr, "-");
              break;
            case 5:
              fprintf(piloubfwptr, ".");
              break;
            case 6:
              fprintf(piloubfwptr, ",");
              break;
            case 7:
              fprintf(piloubfwptr, "[");
              break;
            case 8:
              fprintf(piloubfwptr, "]");
              break;
            default:
          }
        }
        // end of compilou
        fclose(piloubffile);
      } else {
        pilouexit = EXIT_FAILURE;
        printf("Unable to write the file.\n");
      }
      fclose(piloupfile);
    } else {
      pilouexit = EXIT_FAILURE;
      printf("Unable to read the file.\n");
    }
  } else {
    pilouexit = EXIT_FAILURE;
    printf("Unable to allocate memory.\n");
  }
  return pilouexit;
}


/* Compile pilou file to c */
short pilouc(char const *piloupath) {
  FILE *piloupfile, *pilouprptr, *piloucfile, *piloucwptr;
  char *piloucpath;
  short piloucommand, pilouexit;

  pilouexit = EXIT_SUCCESS;
  piloucpath = malloc((strlen(piloupath) + 2) * sizeof(char));
  if (piloucpath) {
    // copy piloupath
    strcpy(piloucpath, piloupath);
    strcat(piloucpath, ".c");
    // open piloufiles
    piloupfile = pilouprptr = fopen(piloupath, "r");
    if (piloupfile) {
      piloucfile = piloucwptr = fopen(piloucpath, "w+");
      if (piloucfile) {
        // write c file head and entry point
        fprintf(piloucwptr, "#include <stdio.h>\n#include <stdlib.h>\nint main(){\n"
          "unsigned char *pilouptr, *pilouwptr;\npilouptr = pilouwptr = (unsigned "
          "char *) calloc(30000, sizeof(char));\nif (pilouptr) {\n");
        // compilou
        while ((piloucommand = pilouread(pilouprptr))) {
          switch (piloucommand) {
            case 1:
              fprintf(piloucwptr, "pilouwptr++;\n");
              break;
            case 2:
              fprintf(piloucwptr, "pilouwptr--;\n");
              break;
            case 3:
              fprintf(piloucwptr, "++(*pilouwptr);\n");
              break;
            case 4:
              fprintf(piloucwptr, "--(*pilouwptr);\n");
              break;
            case 5:
              fprintf(piloucwptr, "putchar(*pilouwptr);\n");
              break;
            case 6:
              fprintf(piloucwptr, "(*pilouwptr) = getchar();\n");
              break;
            case 7:
              fprintf(piloucwptr, "while(*pilouwptr) {\n");
              break;
            case 8:
              fprintf(piloucwptr, "}\n");
              break;
            default:
          }
        }
        // end of compilou
        fprintf(piloucwptr, "free(pilouptr);\n}\n}\n");
        fclose(piloucfile);
      } else {
        pilouexit = EXIT_FAILURE;
        printf("Unable to write the file.\n");
      }
      fclose(piloupfile);
    } else {
      pilouexit = EXIT_FAILURE;
      printf("Unable to read the file.\n");
    }
  } else {
    pilouexit = EXIT_FAILURE;
    printf("Unable to allocate memory.\n");
  }
  return pilouexit;
}


/* Print help */
void pilouhelp() {
  printf("Pilou help\n");
  printf("Print help :\n\tpilou -h\n");
  printf("Compile a pilou file to brainfuck :\n\tpilou -b path/to/file.pilou\n");
  printf("Compile a pilou file to c :\n\tpilou -c path/to/file.pilou\n");
}


/* Read next command in file */
short pilouread(FILE *piloureadptr) {
  char *piloubuffer, *pilouwords[8];
  int pilouread;
  short piloucommand;
  size_t pilouiter;

  piloucommand = 0;
  piloubuffer = malloc(6 * sizeof(char));
  // initialise all valid commands
  pilouwords[0] = "Pilou";
  pilouwords[1] = "piloU";
  pilouwords[2] = "pIlou";
  pilouwords[3] = "pilOu";
  pilouwords[4] = "PiLoU";
  pilouwords[5] = "pIlOu";
  pilouwords[6] = "PIlou";
  pilouwords[7] = "piLOU";
  // browse a file until find a command or the end of the file
  while ((pilouread = fgetc(piloureadptr)) != EOF && piloucommand == 0) {
    // moves the selection of a character
    for (pilouiter = 0; pilouiter < 4; pilouiter++) {
      piloubuffer[pilouiter] = piloubuffer[pilouiter + 1];
    }
    piloubuffer[4] = (char) pilouread;
    // check if it's a pilou command
    for (pilouiter = 0; pilouiter < 8 && piloucommand == 0; pilouiter++) {
      if (strcmp(pilouwords[pilouiter], piloubuffer) == 0) {
        // retains the recognized command
        piloucommand = pilouiter + 1;
      }
    }
  }
  free(piloubuffer);
  return piloucommand;
}
