#include "modulink.h"
#include <unordered_map>
#include <string>

// Function signature storage
std::unordered_map<std::string, std::pair<TypeDefinition, TypeDefinition>> functionRegistry;

// Register a function dynamically
void registerFunction(const std::string& name, TypeDefinition inputType, TypeDefinition outputType) {
    functionRegistry[name] = {inputType, outputType};
}
