#include <gtest/gtest.h>
#include "../src/modulink.h"

// Test missing `.mlk` file error handling
TEST(ErrorHandlingTest, MissingMLKFile) {
    std::stringstream buffer;
    std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

    executeMLK("nonexistent.mlk");

    std::cerr.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("❌ Error: Could not open nonexistent.mlk"), std::string::npos);
}

// Test missing function error handling
TEST(ErrorHandlingTest, MissingFunction) {
    functionRegistry.clear();

    std::stringstream buffer;
    std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

    executeMLK("pipeline.mlk");

    std::cerr.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("❌ Error: Function not found"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
