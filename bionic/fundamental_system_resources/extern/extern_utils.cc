#include "extern_utils.h"
#include <iostream>
#include <sstream>

std::string ExternUtils::FormatString(const std::string& input) {
    std::string result = "[ZNA-OS Extern] " + input;
    return result;
}

std::vector<std::string> ExternUtils::SplitString(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

void ExternUtils::PrintVector(const std::vector<std::string>& vec) {
    std::cout << "[Vector Contents]\n";
    for (const auto& str : vec) {
        std::cout << "  - " << str << "\n";
    }
}
