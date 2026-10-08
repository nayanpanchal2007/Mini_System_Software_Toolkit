#include "toolkit.h"

#define MAX_MNEMONICS 10

typedef struct {
    char name[30];
    char body[10][80];
    int  bodyLines;
} Macro;

static Macro macros[MAX_MACROS];
static int   macroCount = 0;

void macroProcessor() {
    printf("\n--- Macro Processor ---\n");
    printf("Enter macro definitions (format: MACRO <name> ... <body> ... MEND)\n");
    printf("Type 'END' on its own line to finish input.\n");

    char lines[100][80];
    int  n = 0;
    while (n < 100) {
        if (!fgets(lines[n], sizeof(lines[n]), stdin)) break;
        lines[n][strcspn(lines[n], "\n")] = '\0';
        if (strcmp(lines[n], "END") == 0) break;
        n++;
    }

    /* Parse macros */
    macroCount = 0;
    for (int i = 0; i < n; ) {
        if (strncmp(lines[i], "MACRO", 5) == 0) {
            char name[30];
            sscanf(lines[i] + 5, "%s", name);
            Macro *m = &macros[macroCount++];
            strcpy(m->name, name);
            m->bodyLines = 0;
            i++;
            while (i < n && strcmp(lines[i], "MEND") != 0) {
                strcpy(m->body[m->bodyLines++], lines[i]);
                i++;
            }
            i++; /* skip MEND */
        } else i++;
    }

    printf("\n--- Expanded Output ---\n");
    for (int i = 0; i < n; i++) {
        int expanded = 0;
        for (int j = 0; j < macroCount; j++) {
            if (strcmp(lines[i], macros[j].name) == 0) {
                printf("; expanding macro '%s'\n", macros[j].name);
                for (int k = 0; k < macros[j].bodyLines; k++)
                    printf("   %s\n", macros[j].body[k]);
                expanded = 1;
                break;
            }
        }
        if (!expanded) {
            /* skip MACRO / MEND lines in output */
            if (strncmp(lines[i], "MACRO", 5) != 0 && strcmp(lines[i], "MEND") != 0)
                printf("   %s\n", lines[i]);
        }
    }
}