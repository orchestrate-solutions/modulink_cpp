#include <gtest/gtest.h>
#include "../src/modulink.h"

// Test executing a Python function
TEST(CrossLanguageTest, PythonFunctionExecutes) {
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    system("python3 tests/utilities.py analyze_data 'test_data'");

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("Analyzed test_data"), std::string::npos);
}

// Test executing a TypeScript function (Fixed execution string)
TEST(CrossLanguageTest, TypeScriptFunctionExecutes) {
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    std::string command = "node -e \"const { fetch_data } = require('./tests/functions'); ";
    command += "console.log(fetch_data('test_url'));\"";

    system(command.c_str());

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    ASSERT_NE(output.find("Fetched from test_url"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
