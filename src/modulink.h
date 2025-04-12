#ifndef MODULINK_H
#define MODULINK_H

#include <unordered_map>
#include <vector>
#include <string>

// Type Definition
struct TypeDefinition {
    std::string typeName;
    std::vector<TypeDefinition> subTypes;
    bool isGeneric;
    
    TypeDefinition(std::string name, bool generic = false);
    TypeDefinition(std::string name, std::vector<TypeDefinition> subs, bool generic = false);
};

// Function Signatures
extern std::unordered_map<std::string, std::pair<TypeDefinition, TypeDefinition>> functionRegistry;

// Function Prototypes
void registerFunction(const std::string& name, TypeDefinition inputType, TypeDefinition outputType);
bool compareTypes(const TypeDefinition& expected, const TypeDefinition& actual);
bool validateExecutionFlow(const std::vector<std::string>& steps);
void executeOrchestratedPipeline(const std::vector<std::string>& steps);
void executeMLK(const char* filePath);

#endif
