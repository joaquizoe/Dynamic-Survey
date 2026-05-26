/* processing.c */

#include "processing.h"
#include "dyn_survey.h"
#include <stdio.h>
#include <string.h>

void calculate_frequency(Respondent *respondents, double **frequency, int num_questions, int num_respondent) {

    for(int i = 0; i < num_questions; i++) {
        
        for(int j = 0; j < num_respondent; j++) {
            if(respondents[j].response.number_answer[i] == 1) {
                frequency[i][0] += 1.0;
            } else if(respondents[j].response.number_answer[i] == 2) {
                frequency[i][1] += 1.0;
            } else if(respondents[j].response.number_answer[i] == 3) {
                frequency[i][2] += 1.0;
            } else if(respondents[j].response.number_answer[i] == 4) {
                frequency[i][3] += 1.0;
            }
        }
        
        for(int k = 0; k < 4; k++) {
            frequency[i][k] = (frequency[i][k] * 100) / num_respondent; 
        }
    }
}

/* Calculates the average of each question */
void calculate_average(Respondent *respondents, double *average, int num_questions, int num_respondent) {

    for(int i = 0; i < num_questions; i++) {
        for(int j = 0; j < num_respondent; j++) {
            if(respondents[j].response.number_answer[j] == 0) {
                continue;
            }
            average[i] += respondents[j].response.number_answer[i];
        }

        average[i] = average[i] / num_respondent;
    }
}

/* Calculates the demographic of each program */
void calculate_program_demographic(Respondent *respondents, char **program, double *program_demographic, int num_respondent, int num_program) {

    for(int i = 0; i < num_respondent; i++) {
        for(int j = 0; j < num_program; j++) {
            if(strcmp(respondents[i].program, program[j]) == 0) {
                program_demographic[j] += 1.0;
            }
        }
    }

    for(int i = 0; i < num_program; i++) {
        program_demographic[i] = (program_demographic[i] * 100) / num_respondent;
    }
}

/* Calculates the demographic of each residence status */
void calculate_residence_status_demographic(Respondent *respondents, char **residence_status, double *residence_status_demographic, 
                                            int num_respondent, int num_residence_status) {
    for(int i = 0; i < num_respondent; i++) {
        for(int j = 0; j < num_residence_status; j++) {
            if(strcmp(respondents[i].residence_status, residence_status[j]) == 0) {
                residence_status_demographic[j] += 1.0;
            }
        }
    }

    for(int i = 0; i < num_residence_status; i++) {
        residence_status_demographic[i] = (residence_status_demographic[i] * 100) / num_respondent;
    }
}