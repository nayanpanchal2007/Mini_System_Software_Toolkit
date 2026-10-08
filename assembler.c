#include "toolkit.h"

/* Minimal opcode table */
typedef struct { const char *mnemonic; int opcode; } OpEntry;
static OpEntry opTable[] = {
    {"START", 0}, {"LDA", 1}, {"STA", 2}, {"ADD", 3}, {"SUB", 4},
    {"END", 99}, {NULL, 0}
};

static int lookupOpcode(const char *m) {
    for (int i = 0; opTable[i].mnemonic; i++)
        if (strcmp(opTable[i].mnemonic, m) == 0) return opTable[i].opcode;
    return -1;
}

void twoPassAssembler() {
    printf("\n--- Two Pass Assembler ---\n");
    printf("Enter assembly source (end with a line containing only 'END'):\n");

    char lines[50][100];
    int  lineCount = 0;
    while (lineCount < 50) {
        char buf[100];
        if (!fgets(buf, sizeof(buf), stdin)) break;
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) continue;
        strcpy(lines[lineCount++], buf);
        /* stop when line starts with END */
        char tmp[100]; strcpy(tmp, buf);
        char *tok = strtok(tmp, " \t");
        if (tok && strcmp(tok, "END") == 0) break;
    }

    /* ---------- PASS 1: build symbol table ---------- */
    int lc = 0;
    printf("\n[Pass 1] Location Counter Assignment:\n");
    for (int i = 0; i < lineCount; i++) {
        char tmp[100]; strcpy(tmp, lines[i]);
        char *label = strtok(tmp, " \t");
        char *op    = strtok(NULL, " \t");

        if (!op) continue; /* only label present */

        if (strcmp(op, "START") == 0) {
            char *operand = strtok(NULL, " \t");
            lc = operand ? atoi(operand) : 0;
        } else {
            if (label && lookupOpcode(label) == -1) {
                insertSymbol(label, "LABEL", lc);
                printf("  %-10s -> %d\n", label, lc);
            }
            lc++;
        }
    }

    /* ---------- PASS 2: generate code ---------- */
    printf("\n[Pass 2] Generated Object Code:\n");
    printf("%-5s %-10s %-8s %-8s\n", "LC", "LABEL", "OPCODE", "OPERAND");
    printf("----------------------------------------\n");

    lc = 0;
    for (int i = 0; i < lineCount; i++) {
        char tmp[100]; strcpy(tmp, lines[i]);
        char *label = strtok(tmp, " \t");
        char *op    = strtok(NULL, " \t");
        char *operand = strtok(NULL, " \t");

        if (!op) continue;

        if (strcmp(op, "START") == 0) {
            lc = operand ? atoi(operand) : 0;
            printf("%-5d %-10s %-8s %-8s\n", lc, label, op, operand ? operand : "");
            continue;
        }
        if (strcmp(op, "END") == 0) {
            printf("%-5d %-10s %-8s %-8s\n", lc, "", op, "");
            break;
        }

        int opcode = lookupOpcode(op);
        printf("%-5d %-10s %-8s %-8s\n",
               lc, (lookupOpcode(label) == -1 ? label : ""),
               op, operand ? operand : "");
        lc++;
    }
    displaySymbolTable();
}