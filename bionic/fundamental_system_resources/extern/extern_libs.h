#ifndef EXTERN_LIBS_H
#define EXTERN_LIBS_H

#include <string>
#include <vector>

struct ZNA_ExternLib {
    std::string name;
    std::string version;
    bool loaded;
};

class ExternLibManager {
public:
    void AddLib(const std::string& name, const std::string& version);
    void LoadLib(const std::string& name);
    void UnloadLib(const std::string& name);
    void ListLibs() const;

private:
    std::vector<ZNA_ExternLib> libs_;
};

#endif // EXTERN_LIBS_H
