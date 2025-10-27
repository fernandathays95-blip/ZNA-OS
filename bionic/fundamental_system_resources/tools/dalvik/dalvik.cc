#include "dalvik.h"
#include "dalvik_utils.h"

int main() {
    zna::DalvikIR ir_system;

    // Aqui você adiciona os elementos conforme o ZNA-OS
    ir_system.string_entries = {"ZnaMain", "ZnaUtils", "ZnaConfig"};
    ir_system.type_entries = {"ZnaClassA", "ZnaClassB"};
    ir_system.proto_entries = {"protoAlpha", "protoBeta"};
    ir_system.field_entries = {"fieldX", "fieldY"};
    ir_system.method_entries = {"methodInit", "methodRun", "methodExit"};
    ir_system.annotation_entries = {"@ZnaNotNull", "@ZnaDeprecated"};

    // Mostra estatísticas do IR do ZNA-OS
    zna::PrintDalvikStats(ir_system);

    return 0;
}
