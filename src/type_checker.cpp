#include "modulink.h"
#include <vector>
#include <string>

// Type definition structure for full dynamic type support
struct TypeDefinition {
    std::string typeName;
    std::vector<TypeDefinition> subTypes;
    bool isGeneric;

    TypeDefinition(std::string name, bool generic = false) 
        : typeName(std::move(name)), isGeneric(generic) {}

    TypeDefinition(std::string name, std::vector<TypeDefinition> subs, bool generic = false)
        : typeName(std::move(name)), subTypes(std::move(subs)), isGeneric(generic) {}
};

// Deep type comparison for complex structures
bool compareTypes(const TypeDefinition& expected, const TypeDefinition& actual) {
    if (expected.isGeneric || actual.isGeneric) return true;
    if (expected.typeName != actual.typeName) return false;
    if (expected.subTypes.size() != actual.subTypes.size()) return false;

    for (size_t i = 0; i < expected.subTypes.size(); ++i) {
        if (!compareTypes(expected.subTypes[i], actual.subTypes[i])) return false;
    }
    return true;
}
