#include "kernel_utils.h"

void init_art_functions() {
    log_kernel("Initializing ZNA-OS ART kernel extensions...");
    
    check_battery_status();
    enable_camera_access();
    send_notification("Welcome to ZNA-OS!");
    vibrate_motor(500); // Vibra 0,5s ao iniciar
}
