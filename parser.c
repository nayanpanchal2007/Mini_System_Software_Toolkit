#include "toolkit.h"

static char *input;
static int   pos;

static void skipSpaces() {
    while (input[pos] == ' ' || input[pos] == '\t') pos++;
}

static int match(char c) {
    skipSpaces();
    if (input[pos] == c) { pos++; return 1; }
    return 0;
}

static int isDigitChar() {
    skipSpaces();
    return isdigit((unsigned char)input[pos]);
}

/* E -> T {(+|-) T} */
static int E();
static int T();
static int F();

static int F() {
    skipSpaces();
    if (match('(')) {
        if (!E()) return 0;
        if (!match(')')) return 0;
        return 1;
    }
    if (isDigitChar() || isalpha((unsigned char)input[pos])) {
        while (isalnum((unsigned char)input[pos]) || input[pos] == '_') pos++;
        return 1;
    }
    return 0;
}

static int T() {
    if (!F()) return 0;
    skipSpaces();
    while (input[pos] == '*' || input[pos] == '/') {
        pos++;
        if (!F()) return 0;
        skipSpaces();
    }
    return 1;
}

static int E() {
    if (!T()) return 0;
    skipSpaces();
    while (input[pos] == '+' || input[pos] == '-') {
        pos++;
        if (!T()) return 0;
        skipSpaces();
    }
    return 1;
}

void recursiveDescentParser() {
    char buf[500];
    printf("\n--- Recursive Descent Parser ---\n");
    printf("Grammar: E -> T {(+|-)T},  T -> F {(*|/)F},  F -> id | num | (E)\n");
    printf("Enter an arithmetic expression: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0';

    input = buf;
    pos = 0;
    if (E()) {
        skipSpaces();
        if (input[pos] == '\0')
            printf("Result: ACCEPTED (valid expression)\n");
        else
            printf("Result: REJECTED (unexpected '%c' at position %d)\n",
                   input[pos], pos);
    } else {
        printf("Result: REJECTED (syntax error near position %d)\n", pos);
    }
}