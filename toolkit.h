#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOLS 100
#define MAX_TOKENS  200
#define MAX_MACROS  50
#define MAX_QUADS   100

/* ---------- Symbol Table ---------- */
typedef struct {
    char name[50];
    char type[20];
    int  address;
} Symbol;

extern Symbol symTable[MAX_SYMBOLS];
extern int    symCount;

void initSymbolTable();
int  insertSymbol(const char *name, const char *type, int address);
int  searchSymbol(const char *name);
void displaySymbolTable();

/* ---------- Lexical Analyzer ---------- */
typedef struct {
    char lexeme[50];
    char token[20];
} Token;

extern Token tokens[MAX_TOKENS];
extern int   tokenCount;

void lexicalAnalyzer(const char *source);

/* ---------- Two Pass Assembler ---------- */
void twoPassAssembler();

/* ---------- Macro Processor ---------- */
void macroProcessor();

/* ---------- Linker / Loader ---------- */
void linkerLoader();

/* ---------- Recursive Descent Parser ---------- */
void recursiveDescentParser();

/* ---------- Quadruple Generator ---------- */
typedef struct {
    char op[10];
    char arg1[20];
    char arg2[20];
    char result[20];
} Quadruple;

extern Quadruple quads[MAX_QUADS];
extern int       quadCount;

void quadrupleGenerator();
void displayQuadruples();

/* ---------- Code Optimizer ---------- */
void codeOptimizer();

#endif