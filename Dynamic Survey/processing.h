#ifndef _PROCESSING_H_
#define _PROCESSING_H_

/* Libraries
 *
 */
#include "dyn_survey.h"
#include <stdio.h>

/*
 * Function declarations
 */

/* Calculates the frequency of each question */
void calculate_frequency(Respondent *respondents, double **frequency, int num_questions, int num_respondent);

/* Calculates the average of each question */
void calculate_average(Respondent *respondents, double *average, int num_questions, int num_respondent);

#endif
