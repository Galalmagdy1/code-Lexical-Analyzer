#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;


int charClass;
string lexeme;
char nextChar;
int lexLen;
int token;
int nextToken;
ifstream in_fp;


#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99


#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20 
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26


void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

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
    case '=':  
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (in_fp.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF;
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexeme = "";
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }
    cout << "Next token is: " << nextToken << " Next lexeme is " << lexeme << endl;
    return nextToken;
}

int main() {
    in_fp.open("front.in");
    if (!in_fp) {
        cout << "ERROR - cannot open file front.in" << endl;
        return 1;
    }
    else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }
    in_fp.close();
    return 0;
}
