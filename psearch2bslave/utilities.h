//
// Created by muhammet on 01.11.2018.
//

#ifndef PSEARCH2BSLAVE_UTILITIES_H
#define PSEARCH2BSLAVE_UTILITIES_H

#include <stdlib.h>

void* create_shared_memory(size_t size);
char* readFile(char *filename);
char** getColors(char *file_name_to_read);
char* getChildProbability(char *color_to_be_searched,char *file_name_to_read);
int* getChildColorInfo(char *color_to_be_searched,char *file_name_to_read);

#endif //PSEARCH2BSLAVE_UTILITIES_H
