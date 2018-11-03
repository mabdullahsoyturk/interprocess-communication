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
#include <mqueue.h>
#include <errno.h>
#define MESSAGE_LENGTH 1000

int main(int argc, char *argv[]) {

    char* word_to_be_searched = argv[1];
    char* number_of_inputs_str = argv[2];
    char* output_file_name = argv[3 + atoi(number_of_inputs_str)];
    int number_of_inputs = atoi(number_of_inputs_str);

    char * fifo_name = "../fifo.txt";

    mkfifo(fifo_name, 0666);

    int fd;
    char arr1[100];

    pid_t pid;
    char *slave_location;
    char *input_file;
    FILE *output_file = fopen(output_file_name, "w");

    for (int i = 0; i < number_of_inputs; i++) {
        input_file = argv[3 + i];
        slave_location = "../psearch2dslave/output";

        if ((pid = fork()) < 0) {
            perror("fork failed");
            abort();
        } else if (pid == 0) {
            execlp(slave_location, slave_location, word_to_be_searched, input_file, (char*)NULL);
            exit(0);
        }else {
            /* Wait for each child to finish its task. */
            int st;

            fd = open(fifo_name, O_RDONLY);
            read(fd, arr1, sizeof(arr1));

            fprintf(output_file, "%s", arr1);

            close(fd);
        }
    }


    fclose(output_file);

    return EXIT_SUCCESS;
}