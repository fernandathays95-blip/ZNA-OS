#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <stdint.h>
#include <stdbool.h>

// Estrutura representando um ponto de toque
typedef struct {
    int x;
    int y;
    bool pressed;  // true se a tela está sendo pressionada
    int id;        // ID do toque (para multitouch)
} TouchPoint;

// Inicializa o driver de touchscreen
void init_touchscreen();

// Captura o estado atual dos toques
int get_touch_points(TouchPoint* points, int max_points);

// Simula toque no computador (mouse)
void simulate_touch(int x, int y, bool press);

#endif
