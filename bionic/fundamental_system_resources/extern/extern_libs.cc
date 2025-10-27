#include "extern_libs.h"
#include <iostream>

void ExternLibManager::AddLib(const std::string& name, const std::string& version) {
    ZNA_ExternLib lib{name, version, false};
    libs_.push_back(lib);
}

void ExternLibManager::LoadLib(const std::string& name) {
    for (auto& lib : libs_) {
        if (lib.name == name) {
            lib.loaded = true;
            std::cout << "Library " << name << " loaded successfully!\n";
            return;
        }
    }
    std::cout << "Library " << name << " not found!\n";
}

void ExternLibManager::UnloadLib(const std::string& name) {
    for (auto& lib : libs_) {
        if (lib.name == name) {
            lib.loaded = false;
            std::cout << "Library " << name << " unloaded successfully!\n";
            return;
        }
    }
    std::cout << "Library " << name << " not found!\n";
}

void ExternLibManager::ListLibs() const {
    std::cout << "\n=== Extern Libraries ===\n";
    for (const auto& lib : libs_) {
        std::cout << "Name: " << lib.name
                  << " | Version: " << lib.version
                  << " | Loaded: " << (lib.loaded ? "Yes" : "No") << "\n";
    }
}
