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
#include <semaphore.h>


int main(int argc, char *argv[]) {

    const char* SHARED_MEMORY_OBJECT_NAME = "SMO";
    const char* SEMAPHORE_NAME = "/semaphorename12";
    char *word_to_be_searched = argv[1];
    char *file_to_be_read = argv[2];

    sem_t *semaphore = sem_open(SEMAPHORE_NAME, O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
    int shm_fd = shm_open(SHARED_MEMORY_OBJECT_NAME, O_RDWR, 0666);

    struct stat st;

    fstat(shm_fd, &st);
    size_t size = (size_t)st.st_size;

    if (semaphore == SEM_FAILED) {
        perror("sem_open(3) failed");
        exit(EXIT_FAILURE);
    }

    if (sem_wait(semaphore) < 0) {
        perror("sem_wait(3) failed on child");
    }

    char* child_result = getChildProbability(word_to_be_searched, file_to_be_read);

    ftruncate(shm_fd, size + strlen(child_result));

    char* output_str = (char*)mmap(0, size + strlen(child_result), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    for(int t = 0; t < strlen(child_result); t++) {
        output_str[size + t] = child_result[t];
    }

    if (sem_post(semaphore) < 0) {
        perror("sem_post(3) error on child");
    }

    sem_close(semaphore);


    return 0;
}