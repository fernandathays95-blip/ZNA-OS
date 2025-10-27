#ifndef ZNA_DALVIK_UTILS_H
#define ZNA_DALVIK_UTILS_H

#include <vector>
#include <string>
#include <cstdio>

// Função template para imprimir qualquer pool grande
template<typename T>
void PrintLargePool(const std::vector<T>& pool, const std::string& pool_name) {
    printf("\nPrinting pool: %s\n", pool_name.c_str());
    for (size_t i = 0; i < pool.size(); ++i) {
        printf("  %-35s[%zu] = %s\n", pool_name.c_str(), i, pool[i].c_str());
    }
}

#endif // ZNA_DALVIK_UTILS_H
