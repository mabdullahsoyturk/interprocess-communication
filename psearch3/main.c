
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "utilities.h"

pthread_mutex_t lock;

typedef struct node{
    char* data;
    struct node *next;
    struct node *previous;
} NODE;


typedef struct arguments {
    char* word_to_be_searched;
    char* input_file_name;
} ARG;

NODE* head;

void init() {
    head = malloc(sizeof(NODE));
    head->data = NULL;
    head->next = NULL;
    head->previous = NULL;
}

void* thread_work(void *arg)
{

    ARG* arguments = (ARG*)arg;

    pthread_mutex_lock(&lock);

    char* child_result = getChildProbability(arguments->word_to_be_searched, arguments->input_file_name);

    NODE* current = head;
    while(current->next != NULL) {
        current = current->next;
    }

    if(head->data == NULL) {
        head->data = child_result;
    }else {
        current->next = malloc(sizeof(NODE));
        current->next->data = child_result;
        current->next->next = NULL;
        current->next->previous = current;
    }

    pthread_mutex_unlock(&lock);

    return NULL;
}

void free_list() {
    NODE* current = head;
    while(current->next != NULL) {
        current = current->next;
    }

    while(current != head) {
        current = current->previous;
        free(current->next);
    }

    free(head);
}

int main(int argc, char *argv[]) {

    init();

    char* word_to_be_searched = argv[1];
    char* number_of_inputs_str = argv[2];
    char* output_file_name = argv[3 + atoi(number_of_inputs_str)];
    int number_of_inputs = atoi(number_of_inputs_str);

    pthread_t tid[number_of_inputs];

    int i = 0;
    int error;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    char* input_file;

    while(i < number_of_inputs) {

        ARG* arguments = malloc(sizeof(ARG));
        input_file = argv[3 + i];

        arguments->input_file_name = input_file;
        arguments->word_to_be_searched = word_to_be_searched;

        error = pthread_create(&(tid[i]), NULL, &thread_work, arguments);
        if (error != 0){
            printf("\nThread can't be created :[%s]", strerror(error));
        }
        i++;
    }

    for(int k = 0; k < number_of_inputs; k++) {
        pthread_join(tid[k], NULL);
    }

    pthread_mutex_destroy(&lock);

    FILE *output_file = fopen(output_file_name, "w");

    NODE* current = head;
    while(current != NULL) {
        fprintf(output_file, "%s", current->data);
        current = current->next;
    }

    fclose(output_file);

    free_list();

    return 0;
}
