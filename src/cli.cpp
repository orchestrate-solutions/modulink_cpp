#include "modulink.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <string>

// Parse and execute `.mlk` files, dynamically registering functions
void executeMLK(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "❌ Error: Could not open " << filePath << "\n";
        return;
    }

    std::string line;
    std::vector<std::string> pipelineSteps;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::regex registerRegex(R"(@register\s+(\w+)\((\w+)\)\s*->\s*(\w+))");
        std::smatch match;
        if (std::regex_search(line, match, registerRegex)) {
            registerFunction(match[1], {match[2]}, {match[3]});
            continue;
        }

        std::regex pipelineRegex(R"(\[(.*?)\] as (.*?))");
        if (std::regex_search(line, match, pipelineRegex)) {
            std::stringstream ss(match[1]);
            std::string step;
            while (std::getline(ss, step, '-')) {
                step.erase(remove(step.begin(), step.end(), '>'), step.end());
                pipelineSteps.push_back(step);
            }
        }
    }
    file.close();

    if (validateExecutionFlow(pipelineSteps)) {
        executeOrchestratedPipeline(pipelineSteps);
    } else {
        std::cerr << "❌ Execution halted due to pipeline validation failure.\n";
    }
}
