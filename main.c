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

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define ERROR 27

/* lookup - a function to lookup operators and parentheses
 and return the token */
int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        default:
            addChar();
            nextToken = ERROR;
            break;
    }
    return nextToken;
}

/* addChar - a function to add nextChar to lexeme */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

/* getChar - a function to get the next character of
 input and determine its character class */
void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

/* lex - a simple lexical analyzer for arithmetic
 expressions */
char* lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
            /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
            /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
            /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */
    if(nextToken != ERROR){
        strcat(retLex, "Next token is: ");
        sprintf(tokenStr, "%i", nextToken);
        strcat(retLex, tokenStr );
        strcat(retLex, ", Next lexeme is ");
        strcat(retLex, lexeme);
        strcat(retLex, "\n");
    }
    else{
        strcpy(retLex,"Error\n");
        errorFound = 1;
    }
    return retLex;
} /* End of function lex */

int main(int argc, const char * argv[]) {
    
    if ((in_fp = fopen(argv[1], "r")) == NULL)
        printf("ERROR - cannot open %s \n", argv[1]);
    else {
        
        getChar();
        printf("--Parsing line %i--\n", lineCount);
    
        do {
            if (nextChar=='\n'){
                lineCount++;
                printf("\n--Parsing line %i--\n", lineCount);
            }
            lex();
            printf("%s", retLex);
            strcpy(retLex, "");
            
            if( errorFound == 1 ){
                while((nextChar = getc(in_fp)) != EOF){
                    if(nextChar == '\n'){
                        errorFound = 0;
                        break;
                    }
                }//while
            }//if
            
        } while (nextToken != EOF);
    }
    
    return 0 ;
    
}
