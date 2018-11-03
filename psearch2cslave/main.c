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

    mqd_t mq = mq_open("/test8", O_WRONLY);

    // -1 indicates an error.
    if (mq == -1)
    {
        printf("Failed to open queue.\n");
        exit(0);
    }

    char *word_to_be_searched = argv[1];
    char *file_to_be_read = argv[2];

    char* child_result = getChildProbability(word_to_be_searched, file_to_be_read);
    mq_send(mq , child_result, strlen(child_result) + 1, 1);

    return EXIT_SUCCESS;
}