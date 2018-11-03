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
#include <time.h>
#include <mqueue.h>
#include <errno.h>

int main(int argc, char *argv[]) {

    char * fifo_name = "../fifo.txt";
    int fd;

    char *word_to_be_searched = argv[1];
    char *file_to_be_read = argv[2];

    fd = open(fifo_name, O_WRONLY);

    char* child_result = getChildProbability(word_to_be_searched, file_to_be_read);

    write(fd, child_result, strlen(child_result));

    close(fd);

    return EXIT_SUCCESS;
}