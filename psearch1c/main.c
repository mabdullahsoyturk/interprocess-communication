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

#define READ_END 0
#define WRITE_END 1

sem_t* semaphores;
int p[2];

int main(int argc, char *argv[]) {

    char* color_to_be_searched = argv[1];
    char* number_of_inputs_str = argv[2];
    char* output_file_name = argv[3 + atoi(number_of_inputs_str)];
    int number_of_inputs = atoi(number_of_inputs_str);
    pipe(p);

    semaphores = mmap(
            NULL,
            (number_of_inputs + 1) * sizeof(sem_t),
            PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS,
            -1,
            0
    );

    if (semaphores == MAP_FAILED){
        printf("Mapping failed!");
        exit(0);
    }

    pid_t pid;
    char *file_name_to_read;
    char *child_result;

    for (int i = 0; i <= number_of_inputs; i++) {
        sem_init(&semaphores[i], number_of_inputs, 0);
    }

    sem_post(&semaphores[0]);

    for (int i = 0; i < number_of_inputs; i++) {
        file_name_to_read = argv[3+i];

        if ((pid = fork()) < 0) {
            perror("fork failed");
            abort();
        } else if (pid == 0) {
            sem_wait(&semaphores[i]);

            close(p[READ_END]);

            child_result = getChildProbability(color_to_be_searched, file_name_to_read);

            write(p[WRITE_END], child_result, strlen(child_result));

            close(p[WRITE_END]);

            sem_post(&semaphores[i + 1]);
            exit(0);
        }
    }

    free(child_result);

    char buffer[100];
    ssize_t number_of_bytes;
    char *output_str = malloc(200);
    close(p[WRITE_END]);

    for(int i = 0; i < number_of_inputs; i++) {

        while((number_of_bytes = read(p[READ_END],buffer,100)) > 0)  {
            strcat(output_str, buffer);
            sprintf (buffer, "%s", buffer);
        }

    }
    close(p[READ_END]);

    FILE *output = fopen(output_file_name, "w");
    fprintf(output, "%s", output_str);
    free(output_str);
    fclose(output);

    return EXIT_SUCCESS;
}