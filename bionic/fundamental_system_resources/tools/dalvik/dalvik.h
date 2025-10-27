#ifndef ZNA_DALVIK_H
#define ZNA_DALVIK_H

#include <vector>
#include <string>

struct ZNA_DexIR {
    std::vector<std::string> strings_pool;
    std::vector<std::string> types_pool;
    std::vector<std::string> protos_pool;
    std::vector<std::string> fields_pool;
    std::vector<std::string> encoded_fields_pool;
    std::vector<std::string> methods_pool;
    std::vector<std::string> encoded_methods_pool;
    std::vector<std::string> classes_pool;
    std::vector<std::string> method_handles_pool;
    std::vector<std::string> type_list_pool;
    std::vector<std::string> code_pool;
    std::vector<std::string> debug_info_pool;
    std::vector<std::string> encoded_value_pool;
    std::vector<std::string> encoded_array_pool;
    std::vector<std::string> annotation_pool;
    std::vector<std::string> annotation_element_pool;
    std::vector<std::string> annotation_set_pool;
    std::vector<std::string> annotation_set_ref_list_pool;
    std::vector<std::string> annotations_directories_pool;
    std::vector<std::string> field_annotations_pool;
    std::vector<std::string> method_annotations_pool;
    std::vector<std::string> param_annotations_pool;
};

#endif // ZNA_DALVIK_H
