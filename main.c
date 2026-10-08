#include "toolkit.h"

static void printMenu() {
    printf("\n=============================================\n");
    printf("   MINI SYSTEM SOFTWARE TOOLKIT\n");
    printf("=============================================\n");
    printf(" 1. Lexical Analyzer\n");
    printf(" 2. Symbol Table\n");
    printf(" 3. Two Pass Assembler\n");
    printf(" 4. Macro Processor\n");
    printf(" 5. Linker / Loader\n");
    printf(" 6. Recursive Descent Parser\n");
    printf(" 7. Quadruple Generator\n");
    printf(" 8. Code Optimizer\n");
    printf(" 9. Display Symbol Table\n");
    printf(" 0. Exit\n");
    printf("---------------------------------------------\n");
    printf(" Enter your choice: ");
}

int main() {
    int choice;
    initSymbolTable();

    do {
        printMenu();
        if (scanf("%d", &choice) != 1) { 
            while (getchar() != '\n'); 
            choice = -1; 
        }
        getchar(); // consume newline

        switch (choice) {
            case 1: {
                char src[500];
                printf("Enter source code (single line): ");
                fgets(src, sizeof(src), stdin);
                src[strcspn(src, "\n")] = '\0';
                lexicalAnalyzer(src);
                break;
            }
            case 2: twoPassAssembler();    break; /* assembler also uses symtab */
            case 3: twoPassAssembler();    break;
            case 4: macroProcessor();      break;
            case 5: linkerLoader();        break;
            case 6: recursiveDescentParser(); break;
            case 7: quadrupleGenerator();  break;
            case 8: codeOptimizer();       break;
            case 9: displaySymbolTable();  break;
            case 0: printf("Exiting toolkit. Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}