#ifndef _OUTPUT_H_
#define _OUTPUT_H_

/* Libraries
 *
 */
#include "dyn_survey.h"
#include <stdio.h>

/*
 * Function declarations
 */

 /* Prints the result of the survey */
void print_survey(char **questions, double **frequency, char **likert, double *average, char ** program, double *program_demographic, 
                  char ** residence_status, double *residence_status_demographic, int num_respondent, int num_questions, int do_frequency, 
                  int do_average, int do_demographic, int num_program, int num_residence_status);

#endif
