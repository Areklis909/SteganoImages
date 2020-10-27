#include "gtest/gtest.h"
#include <CommandLineParser/CommandLineParser.hpp>

TEST(CommandLineParserTest, shouldRetreiveInputPath) {
    //given
    NsSteganoCommandLineParser::CommandLineParser parser;
    const int mockArgc = 3;
    const char * mockArgv[mockArgc] = {"/some/path/", "--input", "arek"};
    //when
    parser.parseCommandLine(mockArgc, mockArgv);
    //then
    ASSERT_EQ(parser.getInputImagePath(), "arek");
}

TEST(CommandLineParserTest, shouldRetrieveOutputPath) {
    //given
    NsSteganoCommandLineParser::CommandLineParser parser;
    const int mockArgc = 3;
    const char * mockArgv[mockArgc] = {"/some/path/", "--output", "paula"};
    //when
    parser.parseCommandLine(mockArgc, mockArgv);
    //then
    ASSERT_EQ(parser.getOutputImagePath(), "paula");
}

TEST(CommandLineParserTest, shouldRetrieveEncodingMode) {
    //given
    NsSteganoCommandLineParser::CommandLineParser parser;
    const int mockArgc = 3;
    const char * mockArgv[mockArgc] = {"/some/path/", "--mode", "encoding"};
    //when
    parser.parseCommandLine(mockArgc, mockArgv);
    const auto result = parser.getProcessingMode();
    const auto expected = NsProcessingMode::ProcessingMode::fromString("encoding");
    //then
    ASSERT_EQ(result, expected);
}

TEST(CommandLineParserTest, shouldRetrieveOutputMode) {
    //given
    NsSteganoCommandLineParser::CommandLineParser parser;
    const int mockArgc = 3;
    const char * mockArgv[mockArgc] = {"/some/path/", "--message-file", "/path/to/file"};
    //when
    parser.parseCommandLine(mockArgc, mockArgv);
    const auto result = parser.getOutputMode();
    const auto expected = NsOutputMode::OutputMode::fromString("file");
    //then
    ASSERT_EQ(result, expected);
}

TEST(CommandLineParserTest, shouldRetrieveMessage) {
    //given
    NsSteganoCommandLineParser::CommandLineParser parser;
    const int mockArgc = 3;
    const char * mockArgv[mockArgc] = {"/some/path/", "--message", "blahbloh"};
    //when
    parser.parseCommandLine(mockArgc, mockArgv);
    const auto result = parser.getMessage();
    const std::string expected = "blahbloh";
    //then
    ASSERT_EQ(result, expected);
}