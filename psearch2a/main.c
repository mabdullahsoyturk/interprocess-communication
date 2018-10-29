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
#include "utilities.h"

int main(int argc, char *argv[]) {

    const char* SHARED_MEMORY_OBJECT_NAME = "../SMO.txt";

    char* word_to_be_searched = argv[1];
    char* number_of_inputs_str = argv[2];
    char* output_file_name = argv[3 + atoi(number_of_inputs_str)];
    int number_of_inputs = atoi(number_of_inputs_str);

    int file_descriptor = (int)fopen(SHARED_MEMORY_OBJECT_NAME, "wr");
    close(file_descriptor);
    struct stat st;

    pid_t pid;
    char *slave_location;
    char *input_file;
    char* output_str;

    for (int i = 0; i < number_of_inputs; i++) {
        input_file = argv[3 + i];
        slave_location = "../psearch2aslave/output";

        if ((pid = fork()) < 0) {
            perror("fork failed");
            abort();
        } else if (pid == 0) {
            execlp(slave_location, slave_location, word_to_be_searched, input_file, (char*)NULL);
            exit(0);
        }else {
            /* Wait for each child to finish its task. */
            int status;
            pid = wait(&status);
        }
    }

    file_descriptor = open(SHARED_MEMORY_OBJECT_NAME, O_RDWR);
    if (file_descriptor == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fstat(file_descriptor, &st);
    size_t size = (size_t)st.st_size;

    output_str = (char*)mmap(0, size , PROT_READ, MAP_SHARED, file_descriptor, 0);

    if (output_str == MAP_FAILED) {
        perror("Map failed!");
        exit(0);
    }

    FILE *output_file = fopen(output_file_name, "w");

    fprintf(output_file, "%s", output_str);

    fclose(output_file);

    if (munmap(output_str, strlen(output_str)) == -1) {
        perror("Error un-mmapping the file");
    }
    close(file_descriptor);

    return EXIT_SUCCESS;
}