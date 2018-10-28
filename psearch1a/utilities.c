//
// Created by muhammet on 26.10.2018.
//

#include "utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

char* readFile(char *filename)
{
    char *content = NULL;
    long string_size;
    size_t read_size;
    FILE *handler = fopen(filename, "r");

    if (handler)
    {
        fseek(handler, 0, SEEK_END);            // Seek the last byte of the file
        string_size = ftell(handler);           // Offset from the first to the last byte, or in other words, filesize
        rewind(handler);                        // go back to the start of the file

        content = (char*) malloc(sizeof(char) * (string_size + 1) );

        read_size = fread(content, sizeof(char), (size_t)string_size, handler);

        content[string_size] = '\0';

        if (string_size != read_size) { // Something went wrong
            free(content);
            content = NULL;
        }

        fclose(handler);
    }

    return content;
}

char* getChildProbability(char *color_to_be_searched,char *file_name_to_read) {
    char* content = readFile(file_name_to_read);
    int number_of_found = 0;
    int number_of_balls = 0;

    char *seperators   = ",";

    char* token = strtok(content, seperators);

    while(token != NULL) {
        number_of_balls++;

        char* color = NULL;

        color = malloc(strlen(token) + 1);
        strcpy(color, token);

        if(strcmp(color_to_be_searched, color) == 0) {
            number_of_found++;
        }

        token = strtok(NULL, seperators);

        free(color);
    }

    char* probability = malloc(sizeof(int) * 2 + sizeof(char) * 2);
    sprintf(probability, "%i/%i\n", number_of_found, number_of_balls);

    return probability;
}

int* getChildColorInfo(char *color_to_be_searched,char *file_name_to_read) {
    char* content = readFile(file_name_to_read);
    int* info = malloc(sizeof(int) * 2);
    info[0] = 0;
    info[1] = 0;

    char *seperators   = "/";

    info[0] = atoi(strtok(content, seperators));
    info[1] = atoi(strtok(NULL, seperators));

    return info;
}