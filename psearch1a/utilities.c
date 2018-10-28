//
// Created by muhammet on 26.10.2018.
//

#include "utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>

char* readFile(char *filename) {
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

char** getColors(char *file_name_to_read) {
    char* content = readFile(file_name_to_read);
    char* cpy = malloc(strlen(content) + 1);
    strcpy(cpy, content);
    char* cpy2 = malloc(strlen(content) + 1);
    strcpy(cpy2, content);
    char *seperators   = ",";
    int number_of_balls = 0;

    char* token = strtok(content, seperators);

    while(token != NULL) {
        number_of_balls++;
        token = strtok(NULL, seperators);
    }

    char **colorPointers = malloc((number_of_balls+1) * sizeof(char*));
    for (int i = 0; i < number_of_balls; i++) {
        colorPointers[i] = malloc(10 * sizeof(char));
    }

    char* token2 = strtok(cpy, ",");

    int counter = 0;
    while(token2 != NULL) {

        bool isAlreadyIncluded = false;

        for(int i = 0; i < number_of_balls; i++) {
            if(strcmp(token2, colorPointers[i]) == 0) {
                isAlreadyIncluded = true;
            }
        }

        if(!isAlreadyIncluded) {
            colorPointers[counter] = token2;
            counter++;
        }

        token2 = strtok(NULL, ",");
    }

    int *color_counts = malloc(sizeof(int) * counter);
    for (int i = 0; i < counter; i++) {
        color_counts[i] = 0;
    }

    char* token3 = strtok(cpy2, ",");

    while(token3 != NULL) {

        for(int i = 0; i < counter; i++) {
            if(strcmp(token3, colorPointers[i]) == 0) {
                color_counts[i]++;
            }
        }

        token3 = strtok(NULL, ",");
    }

    char **outputs = malloc((counter) * sizeof(char*));
    for (int i = 0; i < counter; i++) {
        outputs[i] = malloc(1000 * sizeof(char));
        for(int k = 0; k < counter; k++) {
            char* single_row = malloc(30 * sizeof(char));
            sprintf(single_row, "%s,%s:%d\n", file_name_to_read, colorPointers[k], color_counts[k]);

            if(k == 0) {
                strcpy(outputs[i], single_row);
            }else {
                strcat(outputs[i], single_row);
            }
        }
    }

    return outputs;
}

char* getChildProbability(char *color_to_be_searched,char *file_name_to_read) {
    char* content = readFile(file_name_to_read);
    int number_of_found = 0;
    int number_of_balls = 0;

    char* token = strtok(content, ",");

    while(token != NULL) {
        number_of_balls++;

        char* color = NULL;

        color = malloc(strlen(token) + 1);
        strcpy(color, token);

        if(strcmp(color_to_be_searched, color) == 0) {
            number_of_found++;
        }

        token = strtok(NULL, ",");

        free(color);
    }

    free(content);

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