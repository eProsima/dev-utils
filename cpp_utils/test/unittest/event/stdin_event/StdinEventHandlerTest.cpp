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
#endif // if defined(_WIN32) || defined(_WIN64)

#include <cpp_utils/testing/gtest_aux.hpp>
#include <gtest/gtest.h>

#include <cpp_utils/event/StdinEventHandler.hpp>
#include <cpp_utils/utils.hpp>

using namespace eprosima::utils::event;

/**
 * @brief Create an object of StdinEventHandler and let it be destroyed.
 *
 * This test may crush if fails.
 */
TEST(StdinEventHandlerTest, trivial_create_handler)
{
    StdinEventHandler handler(
        [](std::string)
        {
            /* empty callback */ },
        0);

    // Let handler to be destroyed by itself
}

void simulate_stdin(
        const std::queue<std::string>& input_queue)
{
#if defined(_WIN32) || defined(_WIN64)
    // Handles for the pipe
    HANDLE pipe_read, pipe_write;

    // Create a pipe
    if (!CreatePipe(&pipe_read, &pipe_write, nullptr, 0))
    {
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
    if (pipe(pipe_fds) == -1)
    {
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
#endif // if defined(_WIN32) || defined(_WIN64)
}

/**
 * @brief Read from custom source 1 line
 */
TEST(StdinEventHandlerTest, read_lines_start)
{
    // Wait till call ++ 1 time
    CounterWaitHandler counter(0, 0, true);

    std::queue<std::string> expected_result;
    expected_result.push("Hello");

    simulate_stdin(expected_result);

    std::mutex mutex_;

    StdinEventHandler handler(
        [&](std::string read_from_source)
        {
            std::lock_guard<std::mutex> _(mutex_);
            auto& expected = expected_result.front();
            ASSERT_EQ(read_from_source, expected);
            expected_result.pop();
            ++counter;
        },
        true,
        1);

    // Wait for all messages received
    counter.wait_and_decrement();

    ASSERT_TRUE(expected_result.empty());
}

/**
 * @brief Read from custom source 5 strings separated by spaces
 */
TEST(StdinEventHandlerTest, read_spaces_start)
{
    // Wait till call ++ 5 times
    CounterWaitHandler counter(4, 0, true);

    std::string input("This will be read separately.");
    std::queue<std::string> expected_result;
    for (auto& res : eprosima::utils::split_string(input, " "))
    {
        expected_result.push(res);
    }

    simulate_stdin(expected_result);

    std::mutex mutex_;

    StdinEventHandler handler(
        [&](std::string read_from_source)
        {
            std::lock_guard<std::mutex> _(mutex_);
            auto& expected = expected_result.front();
            ASSERT_EQ(read_from_source, expected);
            expected_result.pop();
            ++counter;
        },
        false,
        expected_result.size());

    // Wait for all messages received
    counter.wait_and_decrement();

    ASSERT_TRUE(expected_result.empty());
}

/**
 * @brief Read from custom source 2 lines by calling read_one_more_line for each
 */
TEST(StdinEventHandlerTest, read_lines_running)
{
    CounterWaitHandler counter(0, 0, true);

    std::string str1("some_easy_line");
    std::string str2("Another extra large line to read from our beloved new Event Handler.");

    std::queue<std::string> expected_result;
    expected_result.push(str1);
    expected_result.push(str2);

    simulate_stdin(expected_result);

    std::mutex mutex_;

    StdinEventHandler handler(
        [&](std::string read_from_source)
        {
            std::lock_guard<std::mutex> _(mutex_);
            auto& expected = expected_result.front();
            ASSERT_EQ(read_from_source, expected);
            expected_result.pop();
            ++counter;
        },
        true,
        0);

    // Check nothing is read
    ASSERT_EQ(expected_result.size(), 2u);

    // Open to read one and wait
    handler.read_one_more_line();
    counter.wait_and_decrement();

    // Check there is still one to read
    ASSERT_EQ(expected_result.size(), 1u);

    // Open to read one and wait
    handler.read_one_more_line();
    counter.wait_and_decrement();

    // No more to read
    ASSERT_TRUE(expected_result.empty());
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
