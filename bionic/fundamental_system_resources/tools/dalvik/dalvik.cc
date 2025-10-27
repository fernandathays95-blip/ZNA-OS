#include "dalvik.h"
#include "dalvik_utils.h"

// Função auxiliar para imprimir pools de forma genérica
template<typename T>
void PrintPool(const std::vector<T>& pool, const std::string& name) {
    printf("  %-30s: %zu\n", name.c_str(), pool.size());
    for (size_t i = 0; i < pool.size(); ++i) {
        printf("    [%zu] %s\n", i, pool[i].c_str());
    }
}

int main() {
    ZNA_DexIR ir;

    // Populando os pools restantes
    ir.type_list_pool = {"[I", "[Ljava/lang/String;"};
    ir.code_pool = {"code1", "code2", "code3"};
    ir.debug_info_pool = {"dbg1", "dbg2"};
    ir.encoded_value_pool = {"val1", "val2"};
    ir.encoded_array_pool = {"arr1", "arr2"};
    ir.annotation_pool = {"annot1", "annot2"};
    ir.annotation_element_pool = {"elem1", "elem2"};
    ir.annotation_set_pool = {"set1", "set2"};
    ir.annotation_set_ref_list_pool = {"ref1", "ref2"};
    ir.annotations_directories_pool = {"dir1", "dir2"};
    ir.field_annotations_pool = {"field_annot1", "field_annot2"};
    ir.method_annotations_pool = {"method_annot1", "method_annot2"};
    ir.param_annotations_pool = {"param_annot1", "param_annot2"};

    // Print de cada pool
    PrintHeaderInfo(".dex IR statistics (cont.):");

    PrintPool(ir.type_list_pool, "type_lists");
    PrintPool(ir.code_pool, "code");
    PrintPool(ir.debug_info_pool, "debug_info");
    PrintPool(ir.encoded_value_pool, "encoded_values");
    PrintPool(ir.encoded_array_pool, "encoded_arrays");
    PrintPool(ir.annotation_pool, "annotations");
    PrintPool(ir.annotation_element_pool, "annotation_elements");
    PrintPool(ir.annotation_set_pool, "annotation_sets");
    PrintPool(ir.annotation_set_ref_list_pool, "annotation_set_ref_lists");
    PrintPool(ir.annotations_directories_pool, "annotations_directories");
    PrintPool(ir.field_annotations_pool, "field_annotations");
    PrintPool(ir.method_annotations_pool, "method_annotations");
    PrintPool(ir.param_annotations_pool, "param_annotations");

    printf("\nAll pools printed successfully!\n");

    return 0;
}
