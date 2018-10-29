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
        perror("wowowow");

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