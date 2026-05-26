/**
* @brief dyn_survey.c
* @author: Joaqui Santiago
* @date: October 19, 2025
**/

#include "dyn_survey.h"
#include "emalloc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char*argv[]) {

    /* Checks if it receives a parameter */
    if (argc != 1) {
        printf("Usage: %s\n", argv[0]);
        printf("Should receive no parameters\n");
        printf("Read from the stdin instead\n");
        exit(1);
    }

    /* Allocates memory and checks if null */
    char *line = emalloc(MAX_LINE_LEN * sizeof(char));
    if(line == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    char **program = emalloc(MAX_WORDS * sizeof(char*));
    for(int i = 0; i < MAX_WORDS; i++) {
        program[i] = emalloc(MAX_WORD_LEN * sizeof(char));
    }
    if(program == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    char **residence_status = emalloc(MAX_WORDS * sizeof(char*));
    for(int i = 0; i < MAX_WORDS; i++) {
        residence_status[i] = emalloc(MAX_WORD_LEN * sizeof(char));
    }
    if(residence_status == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    char **questions = emalloc(MAX_WORDS * sizeof(char*));
    for(int i = 0; i < MAX_WORDS; i++) {
        questions[i] = emalloc(MAX_WORD_LEN * sizeof(char));
    }
    if(questions == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    char **likert = emalloc(MAX_LIKERT * sizeof(char*));
    for(int i = 0; i < MAX_LIKERT; i++) {
        likert[i] = emalloc(MAX_WORD_LEN * sizeof(char));
    }
    if(likert == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    Respondent *respondents = NULL;

    double **frequency = emalloc(MAX_QUESTION * sizeof(double*));
    for(int i = 0; i < MAX_QUESTION; i++) {
        frequency[i] = emalloc(MAX_WORDS * sizeof(double));
    }
    if(frequency == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    double *average = emalloc(MAX_WORDS * sizeof(double));
    if(average == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    double *program_demographic = calloc(MAX_WORDS, sizeof(double));
    if(program_demographic == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }

    double *residence_status_demographic = calloc(MAX_WORDS, sizeof(double));
    if(residence_status_demographic == NULL) {
        printf("Error! Memory not allocated.\n");
        exit(1);
    }
   
    int first_line = 1;
    int do_frequency = 0;
    int do_average = 0;
    int do_demographic = 0;

    int program_line = 0;
    int num_program = 0;

    int residence_status_line = 0;
    int num_residence_status = 0;

    int questions_line = 0;
    int num_questions = 0;

    int likert_line = 0;

    int respondent_line = 0;
    
    int num_respondent = 0;

    int current_respondent = 0;

    /* Loops over stdin lines */
    while(fgets(line, MAX_LINE_LEN, stdin)) {
        /* Skips comment lines */
        if(line[0] == '#') {
            continue;
         } 
        
        /* Scans test configurations (frequency and average) */
        if(first_line) {
            sscanf(line, "%d , %d, %d", &do_frequency, &do_average, &do_demographic);
            first_line = 0;
            continue;
        }

        /* Tokenizes programs */
        if(!program_line) {
            char **temp = emalloc(MAX_WORDS * sizeof(char*));
            for(int i = 0; i < MAX_WORDS; i++) {
                temp[i] = emalloc(MAX_WORD_LEN * sizeof(char));
            }

            num_program = tokenize_line(line, temp, ",");
                  for(int i = 0; i < num_program; i++) {
                    strncpy(program[i], temp[i], MAX_WORD_LEN);
            }
    
            for(int i = 0; i < MAX_WORDS; i++) {
                free(temp[i]);
            }

            program_line = 1;
            free(temp);
            continue;
        }

        /* Tokenizes residence status */
        if(!residence_status_line) {
            char **temp = emalloc(MAX_WORDS * sizeof(char*));
            for(int i = 0; i < MAX_WORDS; i++) {
                temp[i] = emalloc(MAX_WORD_LEN * sizeof(char));
            }

            num_residence_status = tokenize_line(line, temp, ",");

            for(int i = 0; i < num_residence_status; i++) {
                    strncpy(residence_status[i], temp[i], MAX_WORD_LEN);
            }
            for(int i = 0; i < MAX_WORDS; i++) {
                free(temp[i]);
            }

            residence_status_line = 1;
            free(temp);
            continue;
        }
        
        /* Tokenizes questions/assertions */
        if(strchr(line, ';') && !questions_line) {
            line[strcspn(line, "\r\n")] = 0; 
            num_questions = tokenize_line(line, questions, ";");
            questions_line = 1;
            continue;
        }

        /* Locates the likert line */
        if(strchr(line, ',') && !likert_line) {
            char **temp = emalloc(MAX_LIKERT * sizeof(char*));
            for(int i = 0; i < MAX_LIKERT; i++) {
                temp[i] = emalloc(MAX_WORD_LEN * sizeof(char));
            }

            int n = tokenize_line(line, temp, ",");
            
            for(int i = 0; i < n; i++) {
                strncpy(likert[i], temp[i], MAX_WORD_LEN);
            }
            
             for(int i = 0; i < MAX_LIKERT; i++) {
                free(temp[i]);
            }
            free(temp);
            likert_line = 1;
            continue;
        }

        /* Scans number of respondents and allocates memory */
        if(!respondent_line) {
            sscanf(line, "%d", &num_respondent);

            respondents = emalloc(num_respondent * sizeof(Respondent));
            if(respondents == NULL) {
                printf("Error! Memory not allocated.\n");
                 exit(1);
            }

            for(int i = 0; i < num_respondent; i++) {
                respondents[i].program = emalloc(MAX_WORD_LEN * sizeof(char));
                respondents[i].residence_status = emalloc(MAX_WORD_LEN * sizeof(char));
                respondents[i].response.answers = emalloc(num_questions * sizeof(char*));
                respondents[i].response.number_answer = emalloc(num_questions * sizeof(int));

                if(respondents[i].program == NULL || respondents[i].residence_status == NULL ||
                   respondents[i].response.answers == NULL || respondents[i].response.number_answer == NULL) {
                    printf("Error! Memory not allocated.\n");
                    exit(1);
                   }

                for(int j = 0; j < num_questions; j++) {
                    respondents[i].response.answers[j] = emalloc(MAX_WORD_LEN * sizeof(char));
                    if(respondents[i].response.answers[j] == NULL) {
                        printf("Error! Memory not allocated.\n");
                        exit(1);
                    }
                }
            }

            respondent_line = 1;
            continue;
        }

        /* Tokenizes survey answers */
        if(strchr(line, ',') && likert_line){
            char **temp = emalloc(MAX_WORDS * sizeof(char*));
            for(int i = 0; i < MAX_WORDS; i++) {
                temp[i] = emalloc(MAX_WORD_LEN * sizeof(char));
            }
            
            int n = tokenize_line(line, temp, ",");

            strncpy(respondents[current_respondent].program, temp[0], MAX_WORD_LEN);
            strncpy(respondents[current_respondent].residence_status, temp[1], MAX_WORD_LEN);

            for(int i = 2; i < n; i++) {
                strncpy(respondents[current_respondent].response.answers[i - 2], temp[i], MAX_WORD_LEN);
            }

            for(int i = 0; i < MAX_WORDS; i++) {
                free(temp[i]);
            }

            current_respondent++;
            free(temp);
        }
    }

    /* Converts survey answers into a number scale 1-4 */
    convert_response(respondents, likert, num_respondent, num_questions);
    
    /* Calculates the frequencies of the answers */
    calculate_frequency(respondents, frequency, num_questions, num_respondent);

    /* Calculates the average of the frequencies of the answers */
    calculate_average(respondents, average, num_questions, num_respondent);

    /* Calculates the demographic of the programs of the answers */
    calculate_program_demographic(respondents, program, program_demographic, num_respondent, num_program);

    /* calculates the demographic of the residence status of the answers */
    calculate_residence_status_demographic(respondents, residence_status, residence_status_demographic, 
                                           num_respondent, num_residence_status);

    /* Prints the result of the survey */
    print_survey(questions, frequency, likert, average, program, program_demographic, residence_status, 
                 residence_status_demographic, num_respondent, num_questions, do_frequency, do_average, 
                 do_demographic, num_program, num_residence_status);

    /* Frees all of the allocated memory */
    for(int i = 0; i < MAX_WORDS; i++) {
        free(program[i]);
        free(residence_status[i]);
        free(questions[i]);
    }

    for(int i = 0; i < MAX_QUESTION; i++) {
        free(frequency[i]);
    }

    for(int i = 0; i < MAX_LIKERT; i++) {
        free(likert[i]);
    }

    for(int i = 0; i < num_respondent; i++) {
        free(respondents[i].program);
        free(respondents[i].residence_status);
        free(respondents[i].response.number_answer);

        for(int j = 0; j < num_questions; j++) {
            free(respondents[i].response.answers[j]);
        }
        free(respondents[i].response.answers);
    }

    free(line);
    free(respondents);
    free(average);
    free(program_demographic);
    free(residence_status_demographic);

    free(program);
    free(residence_status);
    free(questions);
    free(frequency);

    free(likert);
    
    return 0;
}