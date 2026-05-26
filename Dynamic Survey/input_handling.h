#ifndef _INPUT_HANDLING_H_
#define _INPUT_HANDLING_H_

/* Libraries
 *
 */
#include "dyn_survey.h"
#include <stdio.h>

/*
 * Function declarations
 */

/* Tokenizes each line by splitting words from given 
   deliminator and stores them in a given string array */
int tokenize_line(char *line, char **words, const char *deliminator);

/* Converts survey answers from 
   likert to a number scale 1-4 */
void convert_response(Respondent *respondents, char **likert, int num_respondent, int num_questions);

#endif