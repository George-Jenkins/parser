#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char nextChar;
char retLex[200];
char tokenStr[100];
int errorFound = 0;
int lineCount = 1;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen(), *fp;

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
char* lex();
void error();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21

int main(int argc, const char * argv[]) {
    
   
    
    return 0 ;
    
}
