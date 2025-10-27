#ifndef ZNA_DALVIK_UTILS_H
#define ZNA_DALVIK_UTILS_H

#include "dalvik.h"
#include <iostream>

namespace zna {

inline void PrintDalvikStats(const DalvikIR& ir) {
    std::cout << "\n.ZNA Dalvik IR Statistics:\n";
    std::cout << "  Strings      : " << ir.string_entries.size() << "\n";
    std::cout << "  Types        : " << ir.type_entries.size() << "\n";
    std::cout << "  Protos       : " << ir.proto_entries.size() << "\n";
    std::cout << "  Fields       : " << ir.field_entries.size() << "\n";
    std::cout << "  Methods      : " << ir.method_entries.size() << "\n";
    std::cout << "  Annotations  : " << ir.annotation_entries.size() << "\n";
}

} // namespace zna

#endif // ZNA_DALVIK_UTILS_H
