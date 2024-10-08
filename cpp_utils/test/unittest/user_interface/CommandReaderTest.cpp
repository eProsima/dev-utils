// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <queue>

#if defined(_WIN32) || defined(_WIN64)
    #define NOMINMAX
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <cpp_utils/testing/gtest_aux.hpp>
#include <gtest/gtest.h>

#include <cpp_utils/enum/EnumBuilder.hpp>
#include <cpp_utils/macros/custom_enumeration.hpp>
#include <cpp_utils/user_interface/CommandReader.hpp>

namespace test {

//! Test enumeration with 2 values
ENUMERATION_BUILDER(
    Enum1,
    value_1,
    value_2
    );

//! Test EnumBuilder to create enums of type \c Enum1 .
eprosima::utils::EnumBuilder<Enum1> create_builder()
{
    return eprosima::utils::EnumBuilder<Enum1>(
        {
            {"value_1", Enum1::value_1},
            {"value_2", Enum1::value_2},
        }
        );
}

//! Test enumeration with 3 heterogenous values
ENUMERATION_BUILDER(
    Enum2,
    some_value,
    other,
    AND_THE_END
    );

//! Singleton EnumBuilder for \c Enum2
eProsima_ENUMERATION_BUILDER(
    Enum2_Builder,
    Enum2,
    {
        { Enum2::some_value COMMA { "1" } } COMMA
        { Enum2::AND_THE_END COMMA { "value_2" COMMA "andtheend" COMMA "and_the_end" } }
    }
    );

void simulate_stdin(
        const std::queue<std::string>& input_queue)
{
#ifdef _WIN32
    // Handles for the pipe
    HANDLE pipe_read, pipe_write;

    // Create a pipe
    if (!CreatePipe(&pipe_read, &pipe_write, nullptr, 0)) {
        std::cerr << "Pipe creation failed!" << std::endl;
        return;
    }

    // Write simulated input to the pipe
    for (auto input = input_queue; !input.empty(); input.pop())
    {
        const std::string& str = input.front();
        DWORD written;

        // Write the string to the pipe
        WriteFile(pipe_write, str.c_str(), str.length(), &written, nullptr);

        // Write a newline character to simulate pressing enter
        WriteFile(pipe_write, "\n", 1, &written, nullptr);
    }

    // Close the writing end of the pipe
    CloseHandle(pipe_write);

    // Redirect stdin to read from the pipe
    SetStdHandle(STD_INPUT_HANDLE, pipe_read);

#else
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        std::cerr << "Pipe failed!" << std::endl;
        return;
    }

    // Write simulated input to the pipe (write to pipe_fds[1])
    for (auto input = input_queue; !input.empty(); input.pop())
    {
        const std::string& str = input.front();
        const char* simulated_input = str.c_str();

        write(pipe_fds[1], simulated_input, str.length());

        // Write newline character to simulate pressing enter
        write(pipe_fds[1], "\n", 1);
    }

    // Close the writing end of the pipe
    close(pipe_fds[1]);

    // Redirect stdin to read from the pipe
    dup2(pipe_fds[0], STDIN_FILENO);
    close(pipe_fds[0]);  // Close the reading end of the pipe after redirecting
#endif
}

} /* namespace test */

using namespace eprosima::utils;

/**
 * Create a CommandReader and check it does not break or have memory leaks.
 */
TEST(CommandReaderTest, trivial_create)
{
    auto builder = test::create_builder();
    CommandReader<test::Enum1> reader(builder);
}

/**
 * Read 3 commands of type enum 1.
 */
TEST(CommandReaderTest, read_lines_enum_1)
{
    std::queue<std::string> expected_result;
    expected_result.push("value_1");
    expected_result.push("value_1 arg");
    expected_result.push("value_2 more than 1 arg");

    test::simulate_stdin(expected_result);

    auto builder = test::create_builder();
    CommandReader<test::Enum1> reader(
        builder);

    {
        Command<test::Enum1> command_result;
        ASSERT_TRUE(reader.read_next_command(command_result));
        ASSERT_EQ(command_result.command, test::Enum1::value_1);
        ASSERT_EQ(command_result.arguments.size(), 1);
        ASSERT_EQ(command_result.arguments[0], "value_1");
    }

    {
        Command<test::Enum1> command_result;
        ASSERT_TRUE(reader.read_next_command(command_result));
        ASSERT_EQ(command_result.command, test::Enum1::value_1);
        ASSERT_EQ(command_result.arguments.size(), 2);
        ASSERT_EQ(command_result.arguments[0], "value_1");
        ASSERT_EQ(command_result.arguments[1], "arg");
    }

    {
        Command<test::Enum1> command_result;
        ASSERT_TRUE(reader.read_next_command(command_result));
        ASSERT_EQ(command_result.command, test::Enum1::value_2);
        ASSERT_EQ(command_result.arguments.size(), 5);
        ASSERT_EQ(command_result.arguments[0], "value_2");
        ASSERT_EQ(command_result.arguments[1], "more");
        ASSERT_EQ(command_result.arguments[2], "than");
        ASSERT_EQ(command_result.arguments[3], "1");
        ASSERT_EQ(command_result.arguments[4], "arg");
    }
}

/**
 * Read a line that does not contains any allowed command value.
 */
TEST(CommandReaderTest, read_lines_enum_1_negative)
{
    std::queue<std::string> expected_result;
    expected_result.push("value_3");

    test::simulate_stdin(expected_result);

    auto builder = test::create_builder();
    CommandReader<test::Enum1> reader(
        builder);

    {
        Command<test::Enum1> command_result;
        ASSERT_FALSE(reader.read_next_command(command_result));
    }
}

/**
 * Read 2 commands using a singleton EnumBuilder
 */
TEST(CommandReaderTest, read_lines_enum_2_singleton)
{
    std::queue<std::string> expected_result;
    expected_result.push("andtheend");
    expected_result.push("1 args");

    test::simulate_stdin(expected_result);

    CommandReader<test::Enum2> reader(
        *test::Enum2_Builder::get_shared_instance());

    {
        Command<test::Enum2> command_result;
        ASSERT_TRUE(reader.read_next_command(command_result));
        ASSERT_EQ(command_result.command, test::Enum2::AND_THE_END);
        ASSERT_EQ(command_result.arguments.size(), 1);
        ASSERT_EQ(command_result.arguments[0], "andtheend");
    }

    {
        Command<test::Enum2> command_result;
        ASSERT_TRUE(reader.read_next_command(command_result));
        ASSERT_EQ(command_result.command, test::Enum2::some_value);
        ASSERT_EQ(command_result.arguments.size(), 2);
        ASSERT_EQ(command_result.arguments[0], "1");
        ASSERT_EQ(command_result.arguments[1], "args");
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
