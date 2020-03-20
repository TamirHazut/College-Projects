%{
#include <string.h>
#include "tennis.tab.h"
extern int atoi (const char*);
%}

%option noyywrap
%x COMMENT

%%
[*]+(" "[A-Za-z]+(" "[A-Za-z]+)*" ")[*]+ {
    return TITLE;
}
"<name>" {
    return NAME;
}

["][A-Z][a-z]*(" "[A-Za-z]+)*["] { 
    strcpy(yylval.name, yytext);
    return PLAYER_NAME;
}

"<gender>" {
    return GENDER;
}

"Man"|"Woman" {
    strcpy(yylval.gender, yytext);
    return PLAYER_GENDER;
}

"<Wimbledon>" {
    return WIMBLEDON;
}
"<Australian Open>" {
    return AUSTRALIAN_OPEN;
}

[1-9][0-9]* { 
    yylval.number = atoi(yytext);
    return NUM;
}
, { return ','; }
- { return '-'; }

[ \t\n]+  /* skip white space */

"//" { BEGIN(COMMENT); }
<COMMENT>.+ /* skip comment */
<COMMENT>\n { /* end of comment --> resume normal processing */ BEGIN(0); }

. { fprintf(stderr, "unrecognized token %s\n", yytext); }
%%