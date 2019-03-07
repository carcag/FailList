#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct failures{
    unsigned int ID_FAILURE;
    unsigned int DATETIME;
    unsigned int ID_COMPONENT;
    unsigned int LEVEL_CRITICITY;
    int COMMENT_SIZE;
    char COMMENT[1024];
} failures;

typedef struct failuresMan{
    char ID_FAILURE[127];
    unsigned int DATETIME;
    char ID_COMPONENT[127];
    unsigned int LEVEL_CRITICITY;
    int COMMENT_SIZE;
    char COMMENT[1024];
} failuresMan;

#endif // MAIN_H_
