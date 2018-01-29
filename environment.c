//
// Created by programajor on 10/18/17.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "environment.h"
#include "fileManager.h"

int firstRowsCount, firstColsCount;
int **firstMatrix;

int secondRowsCount, secondColsCount;
int **secondMatrix;
int **firstOutputMatrix;
int **secondOutputMatrix;

void readMatrix(FILE *file, int **matrix, int *rows, int *cols, int ind);
void writeMatrix(FILE *file, int **matrix, int *rows, int *cols);

int getValue(char *expression);

void fillRow(int **matrix, int row, int cols, FILE *file);

void readInput() {
    FILE* firstInput = getFirstInputFile();
    FILE* secondInput = getSecondInputFile();
    if (firstInput != NULL && secondInput != NULL) {
        readMatrix(firstInput, firstMatrix, &firstRowsCount, &firstColsCount, 1);
        closeFile(firstInput);
        readMatrix(secondInput, secondMatrix, &secondRowsCount, &secondColsCount, 2);
        closeFile(secondInput);
    } else {
        printf("ERROR: cannot open input files\n");
        exit(0);
    }
}

void readMatrix(FILE *file, int **matrix, int *rows, int *cols, int ind) {
    char *rowExpression = malloc(8 * sizeof(char));
    char *colExpression = malloc(8 * sizeof(char));
    fscanf(file, "%s %s", rowExpression, colExpression);
    *rows = getValue(rowExpression);
    *cols = getValue(colExpression);
    matrix = (int **) malloc(*rows * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        matrix[i] = (int *) malloc(*cols * sizeof(int));
        fillRow(matrix, i, *cols, file);
    }
    if (ind == 1) firstMatrix = matrix;
    else secondMatrix = matrix;
}

void fillRow(int **matrix, int row, int cols, FILE *file) {
    for (int i = 0; i < cols; ++i) {
        fscanf(file, "%d", &matrix[row][i]);
    }
}

int getValue(char *expression) {
    return atoi(strchr(expression, '=') + 1);
}

void writeFirstOutput() {
    FILE* firstOutput = getFirstOutputFile();
    if (firstOutput != NULL) {
        writeMatrix(firstOutput, firstOutputMatrix, &firstRowsCount, &secondColsCount);
        closeFile(firstOutput);
    } else {
        printf("ERROR: cannot open output files\n");
        exit(0);
    }
}

void writeSecondOutput() {
    FILE* secondOutput = getSecondOutputFile();
    if (secondOutput != NULL) {
        writeMatrix(secondOutput, secondOutputMatrix, &firstRowsCount, &secondColsCount);
        closeFile(secondOutput);
    } else {
        printf("ERROR: cannot open output files\n");
        exit(0);
    }
}
//
//void writeOutput() {
//    FILE* firstOutput = getFirstOutputFile();
//    FILE* secondOutput = getSecondOutputFile();
//    if (firstOutput != NULL && secondOutput != NULL) {
//        writeMatrix(firstOutput, firstOutputMatrix, &firstRowsCount, &secondColsCount);
//        closeFile(firstOutput);
//        writeMatrix(secondOutput, secondOutputMatrix, &firstRowsCount, &secondColsCount);
//        closeFile(secondOutput);
//    } else {
//        printf("ERROR: cannot open output files\n");
//        exit(0);
//    }
//}

void writeMatrix(FILE *file, int **matrix, int *rows, int *cols) {
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fprintf(file, "%d\t", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

int **getFirstMatrix() { return firstMatrix; }

int **getSecondMatrix() { return secondMatrix; }

int getFirstRows() { return firstRowsCount; }

int getFirstCols() { return firstColsCount; }

int getSecondRows() { return secondRowsCount; }

int getSecondCols() { return secondColsCount; }

int **getFirstOutputMatrix() { return firstOutputMatrix; }

int **getSecondOutputMatrix() { return secondOutputMatrix; }