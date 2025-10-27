#ifndef ZNA_DALVIK_UTILS_H
#define ZNA_DALVIK_UTILS_H

#include <vector>
#include <string>
#include <cstdio>

// Função para imprimir qualquer pool de strings
inline void PrintPool(const std::vector<std::string>& pool, const char* name) {
    printf("==== Pool %s ====\n", name);
    for (size_t i = 0; i < pool.size(); ++i) {
        printf("%s[%zu]: %s\n", name, i, pool[i].c_str());
    }
}

// Funções auxiliares futuras podem ser adicionadas aqui
inline void PrintHeaderInfo(const char* title) {
    printf("\n==== %s ====\n", title);
}

#endif // ZNA_DALVIK_UTILS_H
