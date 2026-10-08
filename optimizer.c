#include "toolkit.h"

void codeOptimizer() {
    printf("\n--- Code Optimizer (on last generated quadruples) ---\n");

    if (quadCount == 0) {
        printf("No quadruples found. Please run Quadruple Generator first.\n");
        return;
    }

    printf("\nOriginal Quadruples:\n");
    displayQuadruples();

    /* --- Pass 1: Constant Folding --- */
    for (int i = 0; i < quadCount; i++) {
        Quadruple *q = &quads[i];
        if (isdigit((unsigned char)q->arg1[0]) && isdigit((unsigned char)q->arg2[0])) {
            int a = atoi(q->arg1), b = atoi(q->arg2), r = 0;
            int folded = 0;
            switch (q->op[0]) {
                case '+': r = a + b; folded = 1; break;
                case '-': r = a - b; folded = 1; break;
                case '*': r = a * b; folded = 1; break;
                case '/': if (b) { r = a / b; folded = 1; } break;
            }
            if (folded) {
                snprintf(q->arg1, sizeof(q->arg1), "%d", r);
                strcpy(q->op,   "=");
                strcpy(q->arg2, "-");
            }
        }
    }

    /* --- Pass 2: Copy Propagation (t = a -> replace later t with a) --- */
    for (int i = 0; i < quadCount; i++) {
        Quadruple *q = &quads[i];
        if (strcmp(q->op, "=") == 0 && strcmp(q->arg2, "-") == 0) {
            const char *src = q->arg1;
            const char *dst = q->result;
            for (int j = i + 1; j < quadCount; j++) {
                if (strcmp(quads[j].arg1, dst) == 0) strcpy(quads[j].arg1, src);
                if (strcmp(quads[j].arg2, dst) == 0) strcpy(quads[j].arg2, src);
            }
        }
    }

    printf("\nOptimized Quadruples:\n");
    displayQuadruples();
}