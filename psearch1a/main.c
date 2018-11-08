#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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

    char* probability = malloc(5 + strlen(file_name_to_read) + strlen(color_to_be_searched) + (number_of_found + number_of_balls) * sizeof(int));
    sprintf(probability, "%s %s %i/%i\n", file_name_to_read, color_to_be_searched, number_of_found, number_of_balls);

    return probability;
}

int main(int argc, char *argv[]) {

    char* color_to_be_searched = argv[1];
    char* number_of_inputs_str = argv[2];
    char* output_file_name = argv[3 + atoi(number_of_inputs_str)];
    int number_of_inputs = atoi(number_of_inputs_str);

    pid_t pid;
    char *file_name_to_read;
    char *temp_output_file_name = malloc((7 + number_of_inputs) * sizeof(char));
    FILE *temp_output_file;
    char *child_result;

    for (int i = 0; i < number_of_inputs; i++) {
        file_name_to_read = argv[3+i];

        if ((pid = fork()) < 0) {
            perror("fork failed");
            abort();
        } else if (pid == 0) {
            child_result = getChildProbability(color_to_be_searched, file_name_to_read);

            sprintf(temp_output_file_name, "temp%d.t", i);

            temp_output_file = fopen(temp_output_file_name, "w");
            fprintf(temp_output_file, "%s", child_result);
            free(child_result);
            fclose(temp_output_file);
            exit(0);
        }else {
            /* Wait for each child to finish its task. */
            int status;
            pid = wait(&status);
        }
    }

    FILE *output_file = fopen(output_file_name, "w");
    fclose(output_file);

    for(int i = 0; i < number_of_inputs; i++) {

        file_name_to_read = argv[3+i];

        output_file = fopen(output_file_name, "a");

        char* result = getChildProbability(color_to_be_searched, file_name_to_read);
        fprintf(output_file, "%s", result);

        fclose(output_file);
    }

    free(temp_output_file_name);

    return EXIT_SUCCESS;
}