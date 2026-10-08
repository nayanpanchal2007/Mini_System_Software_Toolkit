#include "toolkit.h"

Token tokens[MAX_TOKENS];
int   tokenCount = 0;

static int isKeyword(const char *s) {
    const char *kw[] = {"int","float","char","if","else","while","for",
                        "return","void","do","break","continue", NULL};
    for (int i = 0; kw[i]; i++)
        if (strcmp(s, kw[i]) == 0) return 1;
    return 0;
}

static int isOperator(char c) {
    return strchr("+-*/%=<>!&|", c) != NULL;
}

void lexicalAnalyzer(const char *source) {
    int i = 0, n = strlen(source);
    tokenCount = 0;

    printf("\n--- Lexical Analysis ---\n");
    printf("%-20s %-15s\n", "LEXEME", "TOKEN");
    printf("--------------------------------\n");

    while (i < n) {
        /* skip whitespace */
        if (isspace((unsigned char)source[i])) { i++; continue; }

        /* identifiers / keywords */
        if (isalpha((unsigned char)source[i]) || source[i] == '_') {
            int j = 0;
            char buf[50];
            while (i < n && (isalnum((unsigned char)source[i]) || source[i] == '_'))
                buf[j++] = source[i++];
            buf[j] = '\0';

            const char *type = isKeyword(buf) ? "KEYWORD" : "IDENTIFIER";
            strcpy(tokens[tokenCount].lexeme, buf);
            strcpy(tokens[tokenCount].token,  type);
            printf("%-20s %-15s\n", buf, type);

            /* auto-insert identifiers into symbol table */
            if (!isKeyword(buf) && searchSymbol(buf) == -1)
                insertSymbol(buf, "IDENTIFIER", 0);

            tokenCount++;
            continue;
        }

        /* numbers */
        if (isdigit((unsigned char)source[i])) {
            int j = 0;
            char buf[50];
            while (i < n && (isdigit((unsigned char)source[i]) || source[i] == '.'))
                buf[j++] = source[i++];
            buf[j] = '\0';
            strcpy(tokens[tokenCount].lexeme, buf);
            strcpy(tokens[tokenCount].token,  "NUMBER");
            printf("%-20s %-15s\n", buf, "NUMBER");
            tokenCount++;
            continue;
        }

        /* operators */
        if (isOperator(source[i])) {
            char buf[3] = { source[i], '\0', '\0' };
            if (i + 1 < n && isOperator(source[i+1])) {
                buf[1] = source[i+1];
                i++;
            }
            strcpy(tokens[tokenCount].lexeme, buf);
            strcpy(tokens[tokenCount].token,  "OPERATOR");
            printf("%-20s %-15s\n", buf, "OPERATOR");
            tokenCount++;
            i++;
            continue;
        }

        /* punctuation */
        if (strchr("(){}[];,", source[i])) {
            char buf[2] = { source[i], '\0' };
            strcpy(tokens[tokenCount].lexeme, buf);
            strcpy(tokens[tokenCount].token,  "PUNCTUATION");
            printf("%-20s %-15s\n", buf, "PUNCTUATION");
            tokenCount++;
            i++;
            continue;
        }

        /* unknown */
        printf("%-20c %-15s\n", source[i], "UNKNOWN");
        i++;
    }
    printf("--------------------------------\n");
    printf("Total tokens: %d\n", tokenCount);
}