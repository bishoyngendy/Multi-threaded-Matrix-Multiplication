//
// Created by programajor on 10/18/17.
//

#ifndef MATRIXMULTIPLICATION_ENVIRONMENT_H
#define MATRIXMULTIPLICATION_ENVIRONMENT_H

/**
 * reads the input matrices either from default files or selected files
 */
void readInput();

/**
 * write the output matrix from row method to the file.
 */
void writeFirstOutput();

/**
 * write the output matrix from element method to the file.
 */
void writeSecondOutput();

int **getFirstMatrix();
int **getSecondMatrix();

int getFirstRows();
int getFirstCols();
int getSecondRows();
int getSecondCols();

int **getFirstOutputMatrix();
int **getSecondOutputMatrix();

#endif //MATRIXMULTIPLICATION_ENVIRONMENT_H
