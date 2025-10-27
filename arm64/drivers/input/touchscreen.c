#include "touchscreen.h"
#include <stdio.h>
#include <string.h>

#define MAX_TOUCH_POINTS 10

static TouchPoint touch_points[MAX_TOUCH_POINTS];

// Inicializa o driver
void init_touchscreen() {
    memset(touch_points, 0, sizeof(touch_points));
    printf("[Touchscreen] Driver initialized successfully.\n");
}

// Captura os pontos de toque atuais
int get_touch_points(TouchPoint* points, int max_points) {
    int count = (max_points < MAX_TOUCH_POINTS) ? max_points : MAX_TOUCH_POINTS;
    for (int i = 0; i < count; i++) {
        points[i] = touch_points[i];
    }
    return count;
}

// Simula toque (para PC)
void simulate_touch(int x, int y, bool press) {
    // Apenas pegamos o primeiro slot disponível
    for (int i = 0; i < MAX_TOUCH_POINTS; i++) {
        if (!touch_points[i].pressed || !press) {
            touch_points[i].x = x;
            touch_points[i].y = y;
            touch_points[i].pressed = press;
            touch_points[i].id = i;
            break;
        }
    }
    printf("[Touchscreen] %s at (%d,%d)\n", press ? "Pressed" : "Released", x, y);
}
