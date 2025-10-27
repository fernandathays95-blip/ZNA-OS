#ifndef ZNA_DALVIK_H
#define ZNA_DALVIK_H

#include <vector>
#include <string>
#include <cstddef>

namespace zna {

struct DalvikIR {
    std::vector<std::string> string_entries;
    std::vector<std::string> type_entries;
    std::vector<std::string> proto_entries;
    std::vector<std::string> field_entries;
    std::vector<std::string> method_entries;
    std::vector<std::string> annotation_entries;
};

} // namespace zna

#endif // ZNA_DALVIK_H
