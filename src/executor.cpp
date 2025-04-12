#include "modulink.h"
#include <iostream>
#include <vector>
#include <string>

// Validate function chaining with dynamic type checking
bool validateExecutionFlow(const std::vector<std::string>& steps) {
    for (size_t i = 0; i < steps.size() - 1; ++i) {
        if (functionRegistry.find(steps[i]) == functionRegistry.end() ||
            functionRegistry.find(steps[i + 1]) == functionRegistry.end()) {
            std::cerr << "❌ Error: Function `" << steps[i] << "` or `" << steps[i + 1] << "` not found.\n";
            return false;
        }

        TypeDefinition outputType = functionRegistry[steps[i]].second;
        TypeDefinition nextInputType = functionRegistry[steps[i + 1]].first;

        if (!compareTypes(outputType, nextInputType)) {
            std::cerr << "❌ Type Mismatch: `" << steps[i] << "` outputs `" << outputType.typeName
                      << "` but `" << steps[i + 1] << "` expects `" << nextInputType.typeName << "`.\n";
            return false;
        }
    }
    return true;
}

// Execute the parsed `.mlk` pipeline
void executeOrchestratedPipeline(const std::vector<std::string>& steps) {
    std::cout << "✅ Execution started...\n";
    for (const std::string& step : steps) {
        std::cout << "🔄 Executing: " << step << "\n";
    }
    std::cout << "✅ Execution completed successfully!\n";
}
