#include "toolkit.h"

void linkerLoader() {
    printf("\n--- Linker / Loader Simulation ---\n");

    int n;
    printf("How many object modules to link? ");
    scanf("%d", &n);
    getchar();

    int base = 1000; /* starting load address */
    int totalSize = 0;
    printf("\n%-10s %-15s %-15s\n", "MODULE", "SIZE", "LOAD ADDRESS");
    printf("------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        char name[30]; int size;
        printf("Enter module %d name and size: ", i + 1);
        scanf("%s %d", name, &size);
        printf("%-10s %-15d 0x%X\n", name, size, base + totalSize);
        totalSize += size;
    }
    printf("------------------------------------------\n");
    printf("Total linked size: %d bytes\n", totalSize);
    printf("Entry point set to: 0x%X\n", base);
    printf("[Loader] Program loaded successfully.\n");
}