#include "toolkit.h"

Symbol symTable[MAX_SYMBOLS];
int    symCount = 0;

void initSymbolTable() {
    symCount = 0;
}

int searchSymbol(const char *name) {
    for (int i = 0; i < symCount; i++)
        if (strcmp(symTable[i].name, name) == 0) return i;
    return -1;
}

int insertSymbol(const char *name, const char *type, int address) {
    if (symCount >= MAX_SYMBOLS) return -1;
    if (searchSymbol(name) != -1)  return -1; /* already exists */
    strncpy(symTable[symCount].name, name, sizeof(symTable[0].name) - 1);
    strncpy(symTable[symCount].type, type, sizeof(symTable[0].type) - 1);
    symTable[symCount].address = address;
    return symCount++;
}

void displaySymbolTable() {
    printf("\n--- Symbol Table ---\n");
    printf("%-5s %-20s %-15s %-10s\n", "IDX", "NAME", "TYPE", "ADDRESS");
    printf("--------------------------------------------------\n");
    if (symCount == 0) {
        printf("(empty)\n");
    } else {
        for (int i = 0; i < symCount; i++)
            printf("%-5d %-20s %-15s %-10d\n",
                   i, symTable[i].name, symTable[i].type, symTable[i].address);
    }
    printf("--------------------------------------------------\n");
}