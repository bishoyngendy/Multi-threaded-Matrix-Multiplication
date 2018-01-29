#include <stdio.h>
#include "fileManager.h"
#include "environment.h"
#include "multiplier.h"

/**
* entry point to the application
* @param argc the number of arguments when running the app.
* @param argv the arguments when running the app.
*/
int main (int argc, char *argv[]) {
    if (argc == 1) {
        setDefaultFiles();
        readInput();
        startMultiplication();
    } else if (argc == 4) {
        setFiles(argv[1], argv[2], argv[3]);
        readInput();
        startMultiplication();
    } else {
        printf("%s\n", "invalid command");
    }
    return 0;
}

