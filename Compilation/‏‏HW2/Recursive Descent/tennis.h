#ifndef TENNIS

// yylex returns 0 when EOF is encountered
enum token {
      TITLE = 1,
      NAME,
      PLAYER_NAME,
      GENDER,
      PLAYER_GENDER,
      WIMBLEDON,
      AUSTRALIAN_OPEN,
      NUM,
      DASH,
      COMMA   
};

enum player_gender {
   MALE = 1,
   FEMALE
};

char *token_name(enum token token);
char* getStrippedString(char* name);

struct player {
   char name[80];
   int gender;
   int wimbledon_wins;
   int australian_open_wins;
};

union _lexVal{
   int year;
   struct player _player;
};

extern union _lexVal lexicalValue;

void errorMsg(const char *s);

#endif
