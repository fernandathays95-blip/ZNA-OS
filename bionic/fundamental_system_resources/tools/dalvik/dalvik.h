#ifndef ZNA_DALVIK_H
#define ZNA_DALVIK_H

#include <vector>
#include <string>

// Estrutura principal do IR do ZNA-OS
struct ZNA_DexIR {
    std::vector<std::string> string_pool;
    std::vector<std::string> type_pool;
    std::vector<std::string> proto_pool;
    std::vector<std::string> field_pool;
    std::vector<std::string> encoded_field_pool;
    std::vector<std::string> method_pool;
    std::vector<std::string> encoded_method_pool;
    std::vector<std::string> class_pool;
    std::vector<std::string> method_handle_pool;
    std::vector<std::string> type_list_pool;
    std::vector<std::string> code_pool;
    std::vector<std::string> debug_info_pool;
    std::vector<std::string> encoded_value_pool;
    std::vector<std::string> encoded_array_pool;
    std::vector<std::string> annotation_pool;
    std::vector<std::string> annotation_element_pool;
    std::vector<std::string> annotation_set_pool;
    std::vector<std::string> annotation_set_ref_list_pool;
    std::vector<std::string> annotation_dir_pool;
    std::vector<std::string> field_annotation_pool;
    std::vector<std::string> method_annotation_pool;
    std::vector<std::string> param_annotation_pool;
};

#endif // ZNA_DALVIK_H
