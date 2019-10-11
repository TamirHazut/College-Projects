%code {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex (void);
void yyerror (const char* s);
char* getStrippedString(char* name);
struct player_data maxWins(struct player_data p1, struct player_data p2);
}
%code requires {
    enum gender { MAN, WOMAN };
    struct player_data {
        int wins;
        char name[80];
        enum gender _g;
    };
    
}
%union {
    int number;
    char gender[6];
    char name[80];
    struct player_data _player;
}
%token TITLE NAME GENDER WIMBLEDON AUSTRALIAN_OPEN
%token <name> PLAYER_NAME
%token <number> NUM
%token <gender> PLAYER_GENDER

%type <_player> list_of_players player
%type <number> optional_wimbledon
%type <number> optional_australian_open
%type <number> list_of_years ',' year_spec

%error-verbose
%%
input: TITLE list_of_players {
    if (strlen($2.name) == 0) {
        printf("There are no players' data in the input file.\n");
    } else {
        printf("Player with most wins at Wimbledon: %s (%d wins).\n", $2.name, $2.wins);
    }
};
list_of_players: list_of_players player {
        if ($1._g == WOMAN) {
            $$ = $2;
        } else if ($2._g == WOMAN) {
            $$ = $1;
        } else {
            $$ = maxWins($1, $2);
        }
};
list_of_players: /* empty */ { 
    strcpy($$.name, "");
    $$.wins = 0;
    $$._g = MAN;
};

player: NAME PLAYER_NAME GENDER PLAYER_GENDER optional_wimbledon optional_australian_open {
    strcpy($$.name, getStrippedString($2));
    $$.wins = $5;
    if (!strcmp($4,"Man")) {
        $$._g = MAN;
    } else {
        $$._g = WOMAN;
    }
};

optional_wimbledon: WIMBLEDON list_of_years {
    $$ = $2;
} | /* empty */ {
    $$ = 0;
};
optional_australian_open: AUSTRALIAN_OPEN list_of_years {
    $$ = $2;
} | /* empty */ {
    $$ = 0;
};

list_of_years: list_of_years ',' year_spec {
    $$ = $1 + $3;
};
list_of_years: year_spec {
    $$ = $1;
};

year_spec: NUM { $$ = 1; } | NUM'-'NUM
    {
        $$ = ($3 - $1 + 1);
    };
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

struct player_data maxWins(struct player_data p1, struct player_data p2) {
    if (p1.wins >= p2.wins) {
        return p1;
    } else {
        return p2;
    }
}

int main(int argc, char** argv) {
    extern FILE *yyin;
    if (argc <= 1) {
        perror("Not enough arguments passed");
        exit(EXIT_FAILURE);
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stderr, "failed to open %s\n",  argv[1]);
        return(EXIT_FAILURE);
    }

    yyparse();

    fclose(yyin);
    exit(EXIT_SUCCESS);
}

void yyerror (const char* s) {
    fprintf(stderr, "%s\n", s);
}