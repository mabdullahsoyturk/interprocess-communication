#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/mman.h>
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

    free(content);

    char* probability = malloc(sizeof(int) * 2 + sizeof(char) * 2);
    sprintf(probability, "%s %s %i/%i\n", file_name_to_read, color_to_be_searched, number_of_found, number_of_balls);

    return probability;
}

int main(int argc, char *argv[]) {

    const char* SHARED_MEMORY_OBJECT_NAME = "../SMO.txt";

    int file_descriptor;
    char* output_str;

    file_descriptor = open(SHARED_MEMORY_OBJECT_NAME, O_CREAT | O_RDWR, (mode_t)0777);
    if (file_descriptor == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    char *word_to_be_searched = argv[1];
    char *file_to_be_read = argv[2];

    char* child_result = getChildProbability(word_to_be_searched, file_to_be_read);
    struct stat st;

    fstat(file_descriptor, &st);
    size_t size = (size_t)st.st_size;

    fallocate(file_descriptor, 0, size, strlen(child_result));

    output_str = (char *) mmap(0, size + strlen(child_result), PROT_WRITE, MAP_SHARED, file_descriptor, 0);

    if (output_str == MAP_FAILED)
        perror("Map failed!");

    int t;

    for(t=0; t< strlen(child_result); t++) {
        output_str[size+t] = child_result[t];
    }

    if (munmap(output_str, strlen(output_str)) == -1) {
        perror("Error un-mmapping the file");
    }

    close(file_descriptor);

    return EXIT_SUCCESS;
}