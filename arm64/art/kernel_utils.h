#ifndef KERNEL_UTILS_H
#define KERNEL_UTILS_H

#include <stdint.h>
#include <stdio.h>

// Exemplo de função que só existe no ZNA-OS para celular
void vibrate_motor(int duration_ms);
void check_battery_status();
void enable_camera_access();
void send_notification(const char* message);

// Funções comuns do kernel
void log_kernel(const char* msg);

#endif // KERNEL_UTILS_H
