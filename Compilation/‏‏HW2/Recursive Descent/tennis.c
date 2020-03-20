/* 
This is an example of a recursive descent parser.
    
This  program reads a list  of tennis players and their tournament records from its input.
It prints the player name who has won the most in the Wimbledon tournament that satisfies the following conditions:
     (1)  Must be a male player
      
For an example of an input, see file test_tennis.txt 

To prepare the program, issue the following commands from
  The command line:
  
  flex tennis.lex (This will generate a file called lex.yy.c)
    
  compile the program using a C compiler
  for example: 
       gcc lex.yy.c tennis.c -o tennis.exe (note that file tennis.h is part of the program (it's included in other files)
       
  The input file for the program should be supplied as a command line argument
  for example:
      tennis.exe test_tennis.txt
      
  Here is a grammar describing the input (tokens are written using uppercase letters):
    start -> TITLE list_of_players
    list_of_players -> list_of_players player | (empty)
    player -> NAME PLAYER_NAME GENDER PLAYER_GENDER optional_wimbledon optional_australian_open
    optional_wimbledon -> WIMBLEDON list_of_years | (empty)
    optional_australian_open -> AUSTRALIAN_OPEN list_of_years | (empty)
    list_of_years -> list_of_years ',' year_spec
    list_of_years -> year_spec
    year_spec -> NUM | NUM '-' NUM
*/
#include <stdio.h>
#include <stdlib.h>  /* for exit() */
#include <string.h>
#include "tennis.h"
  
extern enum token yylex (void);
int lookahead;

struct player most_wimbledon_wins(struct player p1, struct player p2);

// the recursive descent parser
void start();
struct player players_list();
struct player get_player_info(); 
int tournament_wins();

void errorMsg(const char *s) {
  extern int yylineno;
  fprintf (stderr, "line %d: %s\n", yylineno, s);
}

void match(int expectedToken) {
    if (lookahead == expectedToken)
        lookahead = yylex();
    else {
        char e[100]; /* todo: error message should mention name of token
                   (not its number) */
        sprintf(e, "error: expected token %s, found token %s", 
                token_name(expectedToken), token_name(lookahead));
        errorMsg(e);
        exit(1);
    }
}

struct player most_wimbledon_wins(struct player p1, struct player p2) {
     if (p1.wimbledon_wins == 0) {
         return p2;
    } else if (p2.wimbledon_wins == 0) {
         return p1;
    }
     if (p2.wimbledon_wins <= p1.wimbledon_wins) {
          return p1;
     }
     return p2;
}

int tournament_wins() {
    match(NUM);
    int wins = 0, min_year = lexicalValue.year;
    if (lookahead == DASH) {
        match(DASH);
        match(NUM);
        int max_year = lexicalValue.year;
        wins = max_year - min_year + 1;
    }
    else {
        wins = 1;
    }
    if (lookahead == COMMA) {
         match(COMMA);
    }
    return wins;
}

struct player get_player_info() {
    match(NAME);
    match(PLAYER_NAME);
    match(GENDER);
    match(PLAYER_GENDER);
    char temp_name[80];
    int temp_gender = lexicalValue._player.gender;
    strcpy(temp_name, lexicalValue._player.name);   
    match(WIMBLEDON);
    int n = 0;
    while ( (lookahead && lookahead != AUSTRALIAN_OPEN && lookahead != NAME) ) {
        n += tournament_wins();
    }
    lexicalValue._player.wimbledon_wins = n;
    if (lookahead == AUSTRALIAN_OPEN) {
        match(AUSTRALIAN_OPEN);
        n = 0;
        while ( (lookahead && lookahead != NAME) ) {
            n += tournament_wins();
        }
    } else {
        n = 0;
    }
    lexicalValue._player.australian_open_wins = n; 
    lexicalValue._player.gender = temp_gender;
    strcpy(lexicalValue._player.name, temp_name);
    struct player p = lexicalValue._player;

    if (p.gender == MALE) {
         return p;
    } else {
        struct player temp_player = {"", MALE, 0, 0};
        return temp_player;
    }
}

struct player players_list() {
    struct player wimbledon_mvp = {"", MALE, 0, 0};
    while (lookahead == NAME) {
        struct player player = get_player_info();
        wimbledon_mvp = most_wimbledon_wins(wimbledon_mvp, player);
    }
    return wimbledon_mvp;
}

void start() {
    match(TITLE);
    struct player p = players_list();
    if (strlen(p.name) == 0) {
        printf("There are no players' data in the input file.\n");
    } else {
        printf("Player with most wins at Wimbledon: %s (%d wins).\n", p.name, p.wimbledon_wins);
    }
}

void parse() {
    lookahead = yylex();
    start();
    if (lookahead != 0) {  // 0 means EOF
        errorMsg("EOF expected");
        exit(1);
    }
}

int main (int argc, char **argv) {
    extern FILE *yyin;
    if (argc != 2) {
       fprintf (stderr, "Usage: %s <input-file-name>\n", argv[0]);
	   return 1;
    }
    yyin = fopen (argv [1], "r");
    if (yyin == NULL) {
       fprintf (stderr, "failed to open %s\n", argv[1]);
	   return 2;
    }
  
    parse();
  
    fclose (yyin);
    return 0;
}
