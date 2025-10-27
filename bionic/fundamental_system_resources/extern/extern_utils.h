#ifndef EXTERN_UTILS_H
#define EXTERN_UTILS_H

#include <string>
#include <vector>

class ExternUtils {
public:
    static std::string FormatString(const std::string& input);
    static std::vector<std::string> SplitString(const std::string& input, char delimiter);
    static void PrintVector(const std::vector<std::string>& vec);
};

#endif // EXTERN_UTILS_H
