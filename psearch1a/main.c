#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utilities.h"

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
        }
    }

    /* Wait for each child to finish its task. */
    int status;
    int child_tracker = number_of_inputs;

    while (child_tracker > 0) {
        pid = wait(&status);
        child_tracker--;
    }

    FILE *output_file;

    int total_number_of_balls = 0;
    int total_color_count = 0;

    for(int i = 0; i < number_of_inputs; i++) {
        sprintf(temp_output_file_name, "temp%d.t", i);

        int *colorInfo = getChildColorInfo(color_to_be_searched, temp_output_file_name);

        total_color_count += colorInfo[0];
        total_number_of_balls += colorInfo[1];
        free(colorInfo);
    }

    output_file = fopen(output_file_name, "w");
    fprintf(output_file, "Probability:%d/%d\n", total_color_count, total_number_of_balls);
    fclose(output_file);

    for(int i = 0; i < number_of_inputs; i++) {

        file_name_to_read = argv[3+i];

        output_file = fopen(output_file_name, "a");
        char** a = getColors(file_name_to_read);
        fprintf(output_file, "%s", a[i]);

        fclose(output_file);
    }

    free(temp_output_file_name);

    return EXIT_SUCCESS;
}