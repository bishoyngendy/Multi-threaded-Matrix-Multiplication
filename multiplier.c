//
// Created by programajor on 10/18/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "multiplier.h"
#include "environment.h"
#include <sys/time.h>
#include <pthread.h>

int **firstInputMatrix;
int **secondInputMatrix;

int firstRows;
int firstCols;
int secondRows;
int secondCols;

int **firstOutputMatrix;
int **secondOutputMatrix;

struct timeval stop, start;

struct ElementData {
    int rowIndex;
    int colIndex;
};

struct RowData {
    int rowIndex;
};

void initializeData();

void* calculateRow(void* rowData);
void* calculateElement(void* elementData);

void multiplyRowWise();
void multiplyElementWise();

void emptyOutputMatrices();
void allocateOutputMatrices();

/**
 * Multiplies both matrices by row method and element method.
 */
void startMultiplication() {
    initializeData();
    if (firstCols != secondRows) {
        printf("Invalid Multiplication Operation\n");
        exit(0);
    }
    allocateOutputMatrices();
    emptyOutputMatrices();

    multiplyRowWise();
    writeFirstOutput();

    multiplyElementWise();
    writeSecondOutput();

//    for (int i = 0; i < firstRows; ++i) {
//        for (int j = 0; j < secondCols; ++j) {
//            for (int k = 0; k < firstCols; ++k) {
//                int a = firstInputMatrix[i][k];
//                int b = secondInputMatrix[k][j];
//                firstOutputMatrix[i][j] += a * b;
//            }
//        }
//    }

//    for (int i = 0; i < firstRows; ++i) {
//        for (int j = 0; j < secondCols; ++j) {
//            printf("%d ", firstOutputMatrix[i][j]);
//        }
//        printf("\n");
//    }
}

void allocateOutputMatrices() {
    firstOutputMatrix = malloc(firstRows * sizeof(int *));
    secondOutputMatrix= malloc(firstRows * sizeof(int *));
    for (int i = 0; i < firstRows; ++i) {
        firstOutputMatrix[i] = malloc(secondCols * sizeof(int));
        secondOutputMatrix[i] = malloc(secondCols * sizeof(int));
    }
}

void emptyOutputMatrices() {
    for (int i = 0; i < firstRows; ++i) {
        for (int j = 0; j < secondCols; ++j) {
            firstOutputMatrix[i][j] = 0;
            secondOutputMatrix[i][j] = 0;
        }
    }
}

/**
 * multiply the two matrices with a thread for every row.
 */
void multiplyRowWise() {
    pthread_t threads[firstRows];
    gettimeofday(&start, NULL); // start checking time
    int counter = 0;
    for (int i = 0; i < firstRows; ++i) {
        struct RowData* data = malloc(sizeof(struct RowData));
        data -> rowIndex = i;
        int code = pthread_create(&threads[i], NULL, calculateRow, (void *) data);
        if (code == 0) {
            counter++;
        } else {
            printf(" ERROR : return code from pthread_create() is %d\n", code);
            exit(-1);
        }
    }
    for (int i = 0; i < firstRows; ++i) { pthread_join(threads[i], NULL); }
    gettimeofday(&stop, NULL); // end checking time

    printf("Row Method\n");
    printf("Number of threads %d\n", counter);
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
}

/**
 * multiply the two matrices with a thread for every element.
 */
void multiplyElementWise() {
    pthread_t threads[firstRows * secondCols];
    gettimeofday(&start, NULL); // start checking time
    int counter = 0;
    int index = 0;
    for (int i = 0; i < firstRows; ++i) {
        for (int j = 0; j < secondCols; ++j) {
            struct ElementData* data = malloc(sizeof(struct ElementData));
            data -> rowIndex = i;
            data -> colIndex = j;
            int code = pthread_create(&threads[index++], NULL, calculateElement, (void *) data);
            if (code == 0) {
                counter++;
            } else {
                printf(" ERROR : return code from pthread_create() is %d\n", code);
                exit(-1);
            }
        }
    }
    index = 0;
    for (int i = 0; i < firstRows; ++i) {
        for (int j = 0; j < secondCols; ++j) {
            pthread_join(threads[index++], NULL);
        }
    }
    gettimeofday(&stop, NULL); // end checking time

    printf("Element Method\n");
    printf("Number of threads %d\n", counter);
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
}

void initializeData() {
    firstInputMatrix = getFirstMatrix();
    secondInputMatrix = getSecondMatrix();
    firstRows = getFirstRows();
    firstCols = getFirstCols();
    secondRows = getSecondRows();
    secondCols = getSecondCols();
    firstOutputMatrix = getFirstOutputMatrix();
    secondOutputMatrix = getSecondOutputMatrix();
}

/**
 * executes on a thread responsible for a row in the output matrix.
 * @param rowData contains the index of the row.
 */
void* calculateRow(void* rowData) {
    struct RowData *data;
    data = (struct RowData *) rowData;
    int rowIndex = data -> rowIndex;
    for (int i = 0; i < secondCols; ++i) {
        for (int j = 0; j < firstCols; ++j) {
            firstOutputMatrix[rowIndex][i] += firstInputMatrix[rowIndex][j] * secondInputMatrix[j][i];
        }
    }
    pthread_exit(NULL);
}

/**
 * executes on a thread responsible for am element in the output matrix.
 * @param elementData contains the index of the row and index of the column of the element.
 */
void* calculateElement(void* elementData) {
    struct ElementData *data;
    data = (struct ElementData *) elementData;
    int rowIndex = data -> rowIndex;
    int colIndex = data -> colIndex;
    for (int i = 0; i < firstCols; i++) {
        secondOutputMatrix[rowIndex][colIndex] += firstInputMatrix[rowIndex][i] *
                                                    secondInputMatrix[i][colIndex];
    }
    pthread_exit(NULL);
}
