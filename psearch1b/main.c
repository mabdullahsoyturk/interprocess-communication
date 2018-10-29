#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <linux/mman.h>
#include "utilities.h"

sem_t* semaphores;
#define SHARED_BETWEEN_PROCESSES 2

int main(int argc, char *argv[]) {

    char* color_to_be_searched = argv[1];
    char* number_of_inputs_str = argv[2];
    char* output_file_name = argv[3 + atoi(number_of_inputs_str)];
    int number_of_inputs = atoi(number_of_inputs_str);

    char *output_str = mmap(
        NULL,
        1,
        PROT_READ|PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    semaphores = mmap(
        NULL,
        (number_of_inputs + 1) * sizeof(sem_t),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    if (semaphores == MAP_FAILED || output_str == MAP_FAILED){
        printf("Mapping failed!");
        exit(0);
    }

    pid_t pid;
    char *file_name_to_read;
    char *child_result;

    for (int i = 0; i <= number_of_inputs; i++) {  //initialize semaphores
        sem_init(&semaphores[i], SHARED_BETWEEN_PROCESSES, 0);
    }

    sem_post(&semaphores[0]);

    for (int i = 0; i < number_of_inputs; i++) {
        file_name_to_read = argv[3+i];

        if ((pid = fork()) < 0) {
            perror("fork failed");
            abort();
        } else if (pid == 0) {
            sem_wait(&semaphores[i]);
            child_result = getChildProbability(color_to_be_searched, file_name_to_read);

            size_t oldsize = strlen(output_str);

            mremap(
                output_str,
                oldsize,
                oldsize + strlen(child_result)+1,
                MREMAP_MAYMOVE
            );

            for(int k = 0; k < strlen(child_result); k++) {
                output_str[oldsize + k] = child_result[k];
            }

            sem_post(&semaphores[i + 1]);
            exit(0);
        }
    }

    sem_wait(&semaphores[number_of_inputs]);

    FILE *output = fopen(output_file_name, "w");
    fprintf(output, "%s", output_str);
    fclose(output);

    for(int i = 0; i <= number_of_inputs; i++) { //destroy semaphors
        sem_destroy(&semaphores[i]);
    }

    return EXIT_SUCCESS;
}