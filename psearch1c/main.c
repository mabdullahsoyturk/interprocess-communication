#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <linux/mman.h>
#include <stdbool.h>

#define READ_END 0
#define WRITE_END 1
#define SHARED_BETWEEN_PROCESSES 2
#define BUFFER_SIZE 100

sem_t* semaphores;
int p[2];

char* readFile(char *filename)
{
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

            close(p[READ_END]);

            child_result = getChildProbability(color_to_be_searched, file_name_to_read);

            write(p[WRITE_END], child_result, strlen(child_result));

            close(p[WRITE_END]);

            sem_post(&semaphores[i + 1]);
            exit(0);
        }
    }

    free(child_result);

    char buffer[BUFFER_SIZE];
    ssize_t number_of_bytes;
    char *output_str = malloc(BUFFER_SIZE * 3);
    close(p[WRITE_END]);

    for(int i = 0; i < number_of_inputs; i++) {

        while((number_of_bytes = read(p[READ_END],buffer,BUFFER_SIZE)) > 0)  {
            strcat(output_str, buffer);
            sprintf (buffer, "%s", buffer);
        }

    }
    close(p[READ_END]);

    FILE *output = fopen(output_file_name, "w");
    fprintf(output, "%s", output_str);
    free(output_str);
    fclose(output);

    for(int i = 0; i <= number_of_inputs; i++) { //destroy semaphors
        sem_destroy(&semaphores[i]);
    }

    return EXIT_SUCCESS;
}