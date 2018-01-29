//
// Created by programajor on 10/18/17.
//

#include <string.h>
#include <malloc.h>
#include "fileManager.h"

char *firstInput;
char *secondInput;
char *firstOutput;
char *secondOutput;

void setFiles(char *first, char *second, char *out) {
    firstInput = malloc(strlen(first) * sizeof(char));
    strcpy(firstInput, first);
    secondInput = malloc(strlen(second) * sizeof(char));
    strcpy(secondInput, second);
    firstOutput = malloc(strlen(out) * sizeof(char));
    strcpy(firstOutput, out);
    secondOutput = malloc(strlen(firstOutput) + 2);
    strcpy(secondOutput, firstOutput);
    strcat(secondOutput, "_2");
}

void setDefaultFiles() {
    firstInput = malloc(strlen("a.txt") * sizeof(char));
    strcpy(firstInput, "a.txt");
    secondInput = malloc(strlen("b.txt") * sizeof(char));
    strcpy(secondInput, "b.txt");
    firstOutput = malloc(strlen("c_1.out") * sizeof(char));
    strcpy(firstOutput, "c_1.out");
    secondOutput = malloc(strlen("c_2.out") * sizeof(char));
    strcpy(secondOutput, "c_2.out");
}

FILE* getFirstInputFile() {
    return fopen(firstInput, "r");
}

FILE* getSecondInputFile() {
    return fopen(secondInput, "r");
}

FILE* getFirstOutputFile() {
    return fopen(firstOutput, "w");
}

FILE* getSecondOutputFile() {
    return fopen(secondOutput, "w");
}

void closeFile(FILE* file) {
    if (file != NULL) {
        fclose(file);
    }
}