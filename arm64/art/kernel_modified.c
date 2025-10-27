#include "kernel_utils.h"

// Implementações simplificadas para demonstração

void vibrate_motor(int duration_ms) {
    printf("[ZNA-OS] Vibrating motor for %d ms\n", duration_ms);
}

void check_battery_status() {
    printf("[ZNA-OS] Battery status: 100%%\n"); // Exemplo
}

void enable_camera_access() {
    printf("[ZNA-OS] Camera access enabled\n");
}

void send_notification(const char* message) {
    printf("[ZNA-OS] Notification: %s\n", message);
}

void log_kernel(const char* msg) {
    printf("[KERNEL LOG] %s\n", msg);
}
