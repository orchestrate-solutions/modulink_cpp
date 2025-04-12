#include <gtest/gtest.h>
#include "../src/modulink.h"

// Test TypeScript function parsing
TEST(ParserTest, ParseTypeScriptFunction) {
    std::string tsCode = "export function fetch_data(url: string): object { return {}; }";

    TypeDefinition inputType("string");
    TypeDefinition outputType("object");

    functionRegistry["fetch_data"] = {inputType, outputType};

    ASSERT_EQ(functionRegistry["fetch_data"].first.typeName, "string");
    ASSERT_EQ(functionRegistry["fetch_data"].second.typeName, "object");
}

// Test Python function parsing
TEST(ParserTest, ParsePythonFunction) {
    std::string pyCode = "def analyze_data(data: dict) -> list: return []";

    TypeDefinition inputType("dict");
    TypeDefinition outputType("list");

    functionRegistry["analyze_data"] = {inputType, outputType};

    ASSERT_EQ(functionRegistry["analyze_data"].first.typeName, "dict");
    ASSERT_EQ(functionRegistry["analyze_data"].second.typeName, "list");
}

// Test handling of missing type annotations
TEST(ParserTest, MissingTypeAnnotation) {
    std::string pyCode = "def invalid_function(data):";
    std::pair<TypeDefinition, TypeDefinition> sig = parsePythonFunction(pyCode);


    std::stringstream buffer;
    std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

    parsePythonFunction(pyCode);

    std::cerr.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("❌ Error: Function signature incomplete"), std::string::npos);
    ASSERT_NE(output.find("💡 Fix: Ensure all parameters and return types are explicitly defined."), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
