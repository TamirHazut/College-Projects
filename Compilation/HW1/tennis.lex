%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getStrippedString(char* name);
char* getYears(char* years);

enum semantic_values { END_OF_FILE, TAG, PLAYER_NAME, PLAYER_GENDER, YEAR_WON, YEARS_WON, NEW_LINE, COMMA, TOKEN_ERROR };
enum gender { MAN, WOMAN };

union
{
    char lexeme[80];
} yylval;
%}

%option noyywrap
%x COMMENT

%%
"<name>"|"<gender>"|"<Wimbledon>"|"<Australian Open>" {
    strcpy(yylval.lexeme, yytext);
    return TAG;
}

\"[A-Z][a-z]*(" "[A-Za-z]+)*\" { 
    strcpy(yylval.lexeme, yytext);
    return PLAYER_NAME;
}

"Man"|"Woman" {
    strcpy(yylval.lexeme, yytext);
    return PLAYER_GENDER;
}

[1-9][0-9]* { 
    strcpy(yylval.lexeme, yytext);
    return YEAR_WON;
}
[1-9][0-9]*[-][1-9][0-9]* { 
    strcpy(yylval.lexeme, yytext);
    return YEARS_WON;
}

, {
    strcpy(yylval.lexeme, yytext);
    return COMMA;
}

[\n] {
    return NEW_LINE;
}

[ \t]+  /* skip white space */

"//" { BEGIN(COMMENT); }
<COMMENT>.+ /* skip comment */
<COMMENT>\n { /* end of comment --> resume normal processing */ BEGIN(0); }

. { return TOKEN_ERROR; }
%%
char* getStrippedString(char* name) {
    char* temp = strdup(name);
    int i;
    for (i = 1; i < strlen(temp)-1; i++) {
        temp[i-1] = temp[i]; 
    }
    temp[i-1] = '\0';
    return temp;
}
void main(int argc, char** argv) {
    if (argc <= 1) {
        perror("Not enough arguments passed");
        exit(EXIT_FAILURE);
    }
    char* tokens_as_string[] = { "END_OF_FILE", "TAG", "PLAYER_NAME", "PLAYER_GENDER", "YEAR_WON", "YEARS_WON", "NEW_LINE", "COMMA", "TOKEN_ERROR" };
    char* temp_string;
    int token, line = 1;
    printf("%-30s %-30s %-30s\n", "TOKEN", "LEXEME", "SEMANTIC VALUE");
    printf("----------------------------------------------------------------------------\n");
    yyin = fopen(argv[1], "r");
    while ((token = yylex()) != END_OF_FILE) {
        switch (token) {
            case TAG:
            case PLAYER_NAME:
                temp_string = getStrippedString(yylval.lexeme);
                printf("%-30s %-30s %-30s\n", tokens_as_string[token], yylval.lexeme, temp_string);
                break;
            case PLAYER_GENDER:
            case YEAR_WON:
            case YEARS_WON:
                printf("%-30s %-30s %-30s\n", tokens_as_string[token], yylval.lexeme, yylval.lexeme);
                break;
            case NEW_LINE:
                line++;
                break;
            case COMMA:
                printf("%-30s %-30s\n", "COMMA", yylval.lexeme);
                break;
            default:
                fprintf(stderr, "(Line %d) illegal token: %s\n", line, yytext);
                break;
        }
    }
    if (temp_string) {
        free(temp_string);
    }
    fclose(yyin);
    exit(EXIT_SUCCESS);
}