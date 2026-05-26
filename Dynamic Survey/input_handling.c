/* input_handling.c */

#include "input_handling.h"
#include "dyn_survey.h"
#include <stdio.h>
#include <string.h>

int tokenize_line(char *line, char **words, const char *deliminator) {
    int num_words = 0;
    char *token;
    
    /* Get the first token from line */
    token = strtok(line, deliminator);
    
    /* For every token in line, store it */
    while (token) {

        strncpy(words[num_words], token, MAX_WORD_LEN);

        /* Removes any trailing newline from token and replaces with '\0' */
        if(words[num_words][strlen(words[num_words]) - 1] == '\n') {
            words[num_words][strlen(words[num_words]) - 1] = '\0';
        }

        num_words++;
        
        /* Get the next token from line or reach the deliminator */
        token = strtok(NULL, deliminator);
    } 

    return num_words;
}

void convert_response(Respondent *respondents, char **likert, int num_respondent, int num_questions) {
    for(int i = 0; i < num_respondent; i++) {
        /* Compares current response with each answer to the likert scale 
           and stores it into a response number array */
        for(int j = 0; j < num_questions; j++) {
            if(strcmp(respondents[i].response.answers[j], likert[0]) == 0) {
                respondents[i].response.number_answer[j] = 1;
            } else if(strcmp(respondents[i].response.answers[j], likert[1]) == 0) {
                respondents[i].response.number_answer[j] = 2;
            } else if(strcmp(respondents[i].response.answers[j], likert[2]) == 0) {
                respondents[i].response.number_answer[j] = 3;
            } else if(strcmp(respondents[i].response.answers[j], likert[3]) == 0) {
                respondents[i].response.number_answer[j] = 4;
            }
        }
    }
}