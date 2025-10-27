#include "dalvik.h"
#include "dalvik_utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Função auxiliar para gerar nomes criativos
string GenerateName(const string& prefix, int index) {
    ostringstream oss;
    oss << prefix << "_" << index;
    return oss.str();
}

// Inicializa Dex IR do ZNA-OS com nomes criativos
ZNA_DexIR InitializeDexIR() {
    ZNA_DexIR ir;

    for (int i = 1; i <= 100; ++i) {
        ir.strings_pool.push_back(GenerateName("ZNA_String", i));
        ir.types_pool.push_back(GenerateName("ZNA_Type", i));
        ir.protos_pool.push_back(GenerateName("ZNA_Proto", i));
        ir.fields_pool.push_back(GenerateName("ZNA_Field", i));
        ir.encoded_fields_pool.push_back(GenerateName("ZNA_EncodedField", i));
        ir.methods_pool.push_back(GenerateName("ZNA_Method", i));
        ir.encoded_methods_pool.push_back(GenerateName("ZNA_EncodedMethod", i));
        ir.classes_pool.push_back(GenerateName("ZNA_Class", i));
        ir.method_handles_pool.push_back(GenerateName("ZNA_MethodHandle", i));
        ir.type_list_pool.push_back(GenerateName("ZNA_TypeList", i));
        ir.code_pool.push_back(GenerateName("ZNA_CodeBlock", i));
        ir.debug_info_pool.push_back(GenerateName("ZNA_DebugInfo", i));
        ir.encoded_value_pool.push_back(GenerateName("ZNA_EncodedValue", i));
        ir.encoded_array_pool.push_back(GenerateName("ZNA_EncodedArray", i));
        ir.annotation_pool.push_back(GenerateName("ZNA_Annotation", i));
        ir.annotation_element_pool.push_back(GenerateName("ZNA_AnnotationElement", i));
        ir.annotation_set_pool.push_back(GenerateName("ZNA_AnnotationSet", i));
        ir.annotation_set_ref_list_pool.push_back(GenerateName("ZNA_AnnotationSetRefList", i));
        ir.annotations_directories_pool.push_back(GenerateName("ZNA_AnnotationsDirectory", i));
        ir.field_annotations_pool.push_back(GenerateName("ZNA_FieldAnnotation", i));
        ir.method_annotations_pool.push_back(GenerateName("ZNA_MethodAnnotation", i));
        ir.param_annotations_pool.push_back(GenerateName("ZNA_ParamAnnotation", i));
    }

    return ir;
}

// Imprime todos os itens de um pool
void PrintPool(const vector<string>& pool, const string& pool_name) {
    printf("\n=== %s ===\n", pool_name.c_str());
    for (size_t i = 0; i < pool.size(); ++i) {
        printf("  %zu : %s\n", i + 1, pool[i].c_str());
    }
}

// Função principal
int main() {
    ZNA_DexIR dex_ir = InitializeDexIR();

    PrintPool(dex_ir.strings_pool, "Strings");
    PrintPool(dex_ir.types_pool, "Types");
    PrintPool(dex_ir.protos_pool, "Protos");
    PrintPool(dex_ir.fields_pool, "Fields");
    PrintPool(dex_ir.encoded_fields_pool, "Encoded Fields");
    PrintPool(dex_ir.methods_pool, "Methods");
    PrintPool(dex_ir.encoded_methods_pool, "Encoded Methods");
    PrintPool(dex_ir.classes_pool, "Classes");
    PrintPool(dex_ir.method_handles_pool, "Method Handles");
    PrintPool(dex_ir.type_list_pool, "Type Lists");
    PrintPool(dex_ir.code_pool, "Code Blocks");
    PrintPool(dex_ir.debug_info_pool, "Debug Info");
    PrintPool(dex_ir.encoded_value_pool, "Encoded Values");
    PrintPool(dex_ir.encoded_array_pool, "Encoded Arrays");
    PrintPool(dex_ir.annotation_pool, "Annotations");
    PrintPool(dex_ir.annotation_element_pool, "Annotation Elements");
    PrintPool(dex_ir.annotation_set_pool, "Annotation Sets");
    PrintPool(dex_ir.annotation_set_ref_list_pool, "Annotation Set Ref Lists");
    PrintPool(dex_ir.annotations_directories_pool, "Annotations Directories");
    PrintPool(dex_ir.field_annotations_pool, "Field Annotations");
    PrintPool(dex_ir.method_annotations_pool, "Method Annotations");
    PrintPool(dex_ir.param_annotations_pool, "Parameter Annotations");

    printf("\nAll Dex IR pools printed successfully for ZNA-OS!\n");
    return 0;
}
