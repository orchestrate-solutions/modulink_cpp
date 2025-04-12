#include <gtest/gtest.h>
#include "../src/modulink.h"

// Test valid function chaining
TEST(PipelineTest, ValidFunctionChaining) {
    functionRegistry["fetch_data"] = {"string", "object", false, false};
    functionRegistry["process_data"] = {"object", "list", false, false};
    functionRegistry["analyze_data"] = {"list", "float", false, false};
    functionRegistry["generate_report"] = {"float", "pdf", false, false};

    std::vector<std::string> validSteps = {"fetch_data", "process_data", "analyze_data", "generate_report"};
    ASSERT_TRUE(validateExecutionFlow(validSteps));
}

// Test type mismatch detection
TEST(PipelineTest, DetectsTypeMismatch) {
    functionRegistry["fetch_data"] = {"string", "object", false, false};
    functionRegistry["process_data"] = {"list", "string", false, false};  // Expected "object", got "list"

    std::stringstream buffer;
    std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

    validateExecutionFlow({"fetch_data", "process_data"});

    std::cerr.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("❌ Type Mismatch"), std::string::npos);
    ASSERT_NE(output.find("💡 Fix: Ensure"), std::string::npos);
}

// Test missing function detection
TEST(PipelineTest, DetectsMissingFunction) {
    functionRegistry.clear();  // Simulate missing function definitions

    std::stringstream buffer;
    std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

    validateExecutionFlow({"fetch_data", "process_data"});

    std::cerr.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("❌ Error: Function"), std::string::npos);
    ASSERT_NE(output.find("💡 Fix: Ensure it is correctly imported"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
