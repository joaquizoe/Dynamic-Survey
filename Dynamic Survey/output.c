/* output.c */

#include "output.h"
#include "dyn_survey.h"
#include <stdio.h>

void print_survey(char **questions, double **frequency, char **likert, double *average, char ** program, double *program_demographic, 
                  char ** residence_status, double *residence_status_demographic, int num_respondent, int num_questions, int do_frequency, 
                  int do_average, int do_demographic, int num_program, int num_residence_status) {

    printf("ECS Student Survey\nSURVEY RESPONSE STATISTICS\n\n");
    printf("NUMBER OF RESPONDENTS: %d\n", num_respondent);

    /* Checks if the survey is printing frequency results */
    if(do_frequency) {
        printf("\n#####\nFOR EACH QUESTION/ASSERTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");
        for(int i = 0; i < num_questions; i++) {
            printf("%d. %s\n", i + 1, questions[i]);

            for(int k = 0; k < 4; k++) {
                printf("%.2f: %s\n", frequency[i][k], likert[k]);
                }

                if(i < num_questions - 1) {
                    printf("\n");
                }
        }
    }

    /* Checks if the survey is printing average results */
    if(do_average) {
        printf("\n#####\nFOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT)\n\n");
        
        for(int i = 0; i < num_questions; i++) {
            printf("%d. %s - %.2f\n", i + 1, questions[i], average[i]);
        }
    }

    /* Checks if the survey is printing demographic results */
    if(do_demographic) {
        printf("\n#####\nFOR EACH DEMOGRAPHIC CATEGORY BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH ATTRIBUTE VALUE\n\n");
        printf("UNDERGRADUATE PROGRAM\n");

        for(int i = 0; i < num_program; i++) {
            printf("%.2f: %s\n", program_demographic[i], program[i]);
        }

        printf("\nRESIDENCE STATUS\n");

        for(int i = 0; i < num_residence_status; i++) {
            printf("%.2f: %s\n", residence_status_demographic[i], residence_status[i]);
        }
    }
}