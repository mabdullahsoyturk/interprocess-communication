//
// Created by muhammet on 28.10.2018.
//

#ifndef PSEARCH1C_UTILITIES_H
#define PSEARCH1C_UTILITIES_H

#include <stdlib.h>

void* create_shared_memory(size_t size);
char* readFile(char *filename);
char** getColors(char *file_name_to_read);
char* getChildProbability(char *color_to_be_searched,char *file_name_to_read);
int* getChildColorInfo(char *color_to_be_searched,char *file_name_to_read);

#endif //PSEARCH1C_UTILITIES_H
