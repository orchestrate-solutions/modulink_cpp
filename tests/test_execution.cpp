#include <gtest/gtest.h>
#include "../src/modulink.h"

// Test that a valid `.mlk` file executes correctly
TEST(ExecutionTest, ValidPipelineExecution) {
    functionRegistry["fetch_data"] = {TypeDefinition("string"), TypeDefinition("object")};
    functionRegistry["process_data"] = {TypeDefinition("object"), TypeDefinition("list", {TypeDefinition("object")})};
    functionRegistry["analyze_data"] = {TypeDefinition("list", {TypeDefinition("object")}), TypeDefinition("float")};
    functionRegistry["generate_report"] = {TypeDefinition("float"), TypeDefinition("pdf")};    

    std::vector<std::string> validSteps = {"fetch_data", "process_data", "analyze_data", "generate_report"};
    ASSERT_TRUE(validateExecutionFlow(validSteps));

    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    executeMLK("tests/pipeline.mlk");

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("✅ Execution completed successfully!"), std::string::npos);
}

// Test execution fails if a function is missing
TEST(ExecutionTest, FunctionNotFound) {
    functionRegistry.clear();  // Simulate missing function definitions

    std::stringstream buffer;
    std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

    executeMLK("tests/pipeline.mlk");

    std::cerr.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("❌ Error: Function"), std::string::npos);
    ASSERT_NE(output.find("💡 Fix: Ensure it is correctly imported"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
