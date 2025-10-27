#include <stdio.h>
#include "kernel_utils.h"
#include "art_functions.h"
#include "drivers.h"

void initialize_kernel() {
    printf("\n=== ZNA-OS Kernel Initialization ===\n");
    
    // Inicializando subsistemas principais
    printf("  Initializing CPU cores...\n");
    init_cpu();
    printf("    CPU cores initialized successfully.\n");

    printf("  Initializing memory management...\n");
    init_memory();
    printf("    Memory management active.\n");

    printf("  Initializing filesystem drivers...\n");
    init_fs();
    printf("    Filesystem ready.\n");

    printf("  Initializing device drivers...\n");
    init_drivers();
    printf("    All drivers loaded:\n");
    print_loaded_drivers();
    
    printf("  Initializing networking modules...\n");
    init_network();
    printf("    Network stack is up.\n");

    printf("  Initializing ART extensions (mobile functions)...\n");
    init_art_functions();
    print_art_functions();
    printf("  ART functions initialized successfully.\n");

    printf("\n=== ZNA-OS Kernel Initialization Complete ===\n\n");
}

int main() {
    printf("[ZNA-OS] Booting kernel...\n");
    
    // Inicializa o kernel e módulos
    initialize_kernel();

    // Loop principal simulando kernel ativo
    while (1) {
        printf("[ZNA-OS] Kernel active, monitoring tasks...\n");
        sleep(5); // Delay simula processamento contínuo
    }

    return 0; // Nunca será alcançado
}
