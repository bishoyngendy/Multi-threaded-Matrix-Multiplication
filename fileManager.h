//
// Created by programajor on 10/18/17.
//

#ifndef MATRIXMULTIPLICATION_FILEMANAGER_H
#define MATRIXMULTIPLICATION_FILEMANAGER_H

/**
 * Set Files with default values.
 */
void setDefaultFiles();

/**
 * set the files for input and output
 * @param first first input file.
 * @param second second input file
 * @param out output file.
 */
void setFiles(char *first, char *second, char *out);

FILE* getFirstInputFile();
FILE* getSecondInputFile();
FILE* getFirstOutputFile();
FILE* getSecondOutputFile();

void closeFile(FILE* file);

#endif //MATRIXMULTIPLICATION_FILEMANAGER_H
