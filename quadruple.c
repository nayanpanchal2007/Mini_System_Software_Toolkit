#include "toolkit.h"

Quadruple quads[MAX_QUADS];
int       quadCount = 0;

static int tempCount = 1;

static void emit(const char *op, const char *a1, const char *a2, const char *res) {
    if (quadCount >= MAX_QUADS) return;
    strncpy(quads[quadCount].op,     op,  sizeof(quads[0].op) - 1);
    strncpy(quads[quadCount].arg1,   a1,  sizeof(quads[0].arg1) - 1);
    strncpy(quads[quadCount].arg2,   a2,  sizeof(quads[0].arg2) - 1);
    strncpy(quads[quadCount].result, res, sizeof(quads[0].result) - 1);
    quadCount++;
}

void displayQuadruples() {
    printf("\n%-5s %-10s %-10s %-10s %-10s\n", "NO", "OP", "ARG1", "ARG2", "RESULT");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < quadCount; i++)
        printf("%-5d %-10s %-10s %-10s %-10s\n",
               i, quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result);
}

void quadrupleGenerator() {
    printf("\n--- Quadruple Generator ---\n");
    printf("Enter a simple assignment of the form:  x = a + b * c\n");
    printf("Expression: ");

    char buf[300];
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0';

    /* Very simple infix -> quads for a * b + c style.
       Supports only one operator per term for academic demo. */
    char lhs[20], rhs[300];
    char *eq = strchr(buf, '=');
    if (!eq) { printf("Invalid: missing '='\n"); return; }

    *eq = '\0';
    sscanf(buf, "%s", lhs);
    strcpy(rhs, eq + 1);

    /* Tokenize RHS by spaces */
    char *t[50]; int n = 0;
    char *tok = strtok(rhs, " ");
    while (tok && n < 50) { t[n++] = tok; tok = strtok(NULL, " "); }

    /* Handle "a op b" or "a op b op c" (left-associative) */
    if (n < 3) { printf("Expression too simple.\n"); return; }

    char cur[20];
    strcpy(cur, t[0]);
    for (int i = 1; i + 1 < n; i += 2) {
        const char *op = t[i];
        const char *r  = t[i + 1];
        char temp[20];
        snprintf(temp, sizeof(temp), "t%d", tempCount++);
        emit(op, cur, r, temp);
        strcpy(cur, temp);
    }
    emit("=", cur, "-", lhs);

    printf("\n--- Quadruples ---\n");
    displayQuadruples();
}