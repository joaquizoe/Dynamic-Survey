#ifndef _DYN_SURVEY_H_
#define _DYN_SURVEY_H_

/* Libraries
 *
 */
#include <stdio.h>

/*
 * Compile-time constants
 */
#define MAX_WORDS 1000
#define MAX_WORD_LEN 1000
#define MAX_LINE_LEN 1000
#define MAX_LIKERT 4
#define MAX_QUESTION 15

/*
 * Structs declarations
 */
typedef struct {
    char **answers;
    int *number_answer;
} Response;

typedef struct {
    Response response;
    char *program;
    char *residence_status;
} Respondent;

/*
 * Function declarations
 */
int tokenize_line(char *line, char **words, const char *deliminator);
void convert_response(Respondent *respondents, char **likert, int num_respondent, int num_questions);
void calculate_frequency(Respondent *respondents, double **frequency, int num_questions, int num_respondent);
void calculate_average(Respondent *respondents, double *average, int num_questions, int num_respondent);
void calculate_program_demographic(Respondent *respondents, char **program, double *program_demographic, int num_respondent, int num_program);
void calculate_residence_status_demographic(Respondent *respondents, char **residence_status, double *residence_status_demographic, 
                                            int num_respondent, int num_residence_status);
void print_survey(char **questions, double **frequency, char **likert, double *average, char ** program, double *program_demographic, 
                  char ** residence_status, double *residence_status_demographic, int num_respondent, int num_questions, int do_frequency, 
                  int do_average, int do_demographic, int num_program, int num_residence_status);

#endif