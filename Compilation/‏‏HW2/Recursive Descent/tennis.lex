%{
#include "tennis.h"
extern int atoi (const char *);
extern void exit(int);

union _lexVal lexicalValue; // semantic value of current token
%}

%option noyywrap
%option yylineno

%%
[*]+(" "[A-Za-z]+(" "[A-Za-z]+)*" ")[*]+ {
    return TITLE;
}
"<name>" {
    return NAME;
}

["][A-Z][a-z]*(" "[A-Za-z]+)*["] { 
    strcpy(lexicalValue._player.name, getStrippedString(yytext));
    return PLAYER_NAME;
}

"<gender>" {
    return GENDER;
}

"Man"|"Woman" {
    lexicalValue._player.gender = (!strcmp(yytext, "Man") ? MALE : FEMALE);
    return PLAYER_GENDER;
}

"<Wimbledon>" {
    return WIMBLEDON;
}
"<Australian Open>" {
    return AUSTRALIAN_OPEN;
}

[1-9][0-9]* { 
    lexicalValue.year = atoi(yytext);
    return NUM;
}
, { return COMMA; }
- { return DASH; }
                      
[\t\n ]+   /* skip white space */

.          { char e[100];
            sprintf(e, "unrecognized token %c", yytext[0]);  
            errorMsg(e);  
             exit(1);
           }

%%
/* useful for error messages */
char *token_name(enum token token) {
    static char *names[] = {
         "EOF", "TITLE", "NAME", "PLAYER_NAME", "GENDER",
         "PLAYER_GENDER", "WIMBLEDON", "AUSTRALIAN_OPEN", "NUM", "DASH", "COMMA" };
    return token <= COMMA ? names[token] : "unknown token";
}

char* getStrippedString(char* name) {
    char* temp = strdup(name);
    int i;
    for (i = 1; i < strlen(temp)-1; i++) {
        temp[i-1] = temp[i]; 
    }
    temp[i-1] = '\0';
    return temp;
}
