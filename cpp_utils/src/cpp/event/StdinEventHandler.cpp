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

#include <thread>

#if defined(_WIN32) || defined(_WIN64)
    #define NOMINMAX
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include <cpp_utils/event/StdinEventHandler.hpp>
#include <cpp_utils/exception/InitializationException.hpp>
#include <cpp_utils/Log.hpp>

namespace eprosima {
namespace utils {
namespace event {

StdinEventHandler::StdinEventHandler(
        std::function<void(std::string)> callback,
        const bool read_lines /* = true */,
        const int lines_to_read /* = 0 */,
        std::istream& source /* = std::cin */)
    : activation_times_(0, lines_to_read, false)
    , source_(source)
    , read_lines_(read_lines)
{
    set_callback(callback);
}

StdinEventHandler::~StdinEventHandler()
{
    unset_callback();
}

void StdinEventHandler::read_one_more_line()
{
    ++activation_times_;
}

void StdinEventHandler::set_terminal_mode_(bool enable) noexcept
{
#if defined(_WIN32) || defined(_WIN64)
    static DWORD old_mode;
    static HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (enable)
    {
        // Save actual configuration in 'old_mode'
        GetConsoleMode(hStdin, &old_mode);

        // Modify line mode flags
        // - ENABLE_ECHO_INPUT: Desactivate echo (does not print what the user writes on terminal)
        // - ENABLE_LINE_INPUT: Desactivate line mode (process each character)
        DWORD new_mode = old_mode;
        new_mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
        SetConsoleMode(hStdin, new_mode);
        std::cout << "New console mode set" << std::endl;
    }
    else
    {
        // Restore original terminal configuration
        SetConsoleMode(hStdin, old_mode);
    }

#else

    static struct termios oldt, newt;
    if (enable)
    {
        // Save actual configuration in 'oldt'
        tcgetattr(STDIN_FILENO, &oldt);

        // Copy actual configuration in 'newt'
        newt = oldt;

        // Modify line mode flags
        // - ICANON: Desactivate canonic mode (process each character)
        // - ECHO: Desactivate echo (does not print what the user writes on terminal)
        newt.c_lflag &= ~(ICANON | ECHO);

        // Apply new configuration
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        // Restore original terminal configuration
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
#endif
}

void StdinEventHandler::stdin_listener_thread_routine_() noexcept
{
    set_terminal_mode_(true);

    auto awake_reason = activation_times_.wait_and_decrement();
    while (awake_reason == AwakeReason::condition_met)
    {
        std::string read_str;

        while (true)
        {

#if defined(_WIN32) || defined(_WIN64)
            int c;
            c = _getch(); // Read first character
            if (c == 0 || c == 224)  // Special key prefix for arrow keys on Windows
            {
                c = _getch(); // Get next character to determine arrow key
                switch (c)
                {
                    case 72:  // Arrow up
#else
            char c;
            c = getchar(); // Read first character
            if (c == '\033')
            {
                getchar(); // Ignore next character '['
                switch (getchar())
                {
                    case 'A':
#endif
                    {
                        std::string prev_command = history_handler_.get_previous_command();
                        if (!prev_command.empty())
                        {
                            read_str = prev_command;
                            std::cout << "\r\033[K";
                            std::cout << "\033[38;5;82m>>\033[0m " << read_str << std::flush;
                        }

                        break;
                    }

#if defined(_WIN32) || defined(_WIN64)
                    case 80:  // Arrow down
#else
                    case 'B':  // Arrow down
#endif
                    {
                        std::string next_command = history_handler_.get_next_command();
                        if (!next_command.empty())
                        {
                            read_str = next_command;
                            std::cout << "\r\033[K";
                            std::cout << "\033[38;5;82m>>\033[0m " << read_str << std::flush;
                        }
                        else
                        {
                            read_str = "";
                            std::cout << "\r\033[K";
                            std::cout << "\033[1;36m>>\033[0m " << std::flush;
                        }

                        break;
                    }
                }
            }
            else if (c == '\n' || c == '\r')
            {
                std::cout << std::endl;
                event_occurred_(read_str);
                history_handler_.add_command(read_str);
                read_str = "";
                break;
            }
            else if (c == '\b' || c == 127)
            {
                if (!read_str.empty())
                {
                    read_str.pop_back();
                    std::cout << "\b \b";
                }
            }
            else
            {
                char ch = static_cast<char>(c);
                read_str += ch;
                std::cout << ch;
                std::cout.flush();
            }
        }

        awake_reason = activation_times_.wait_and_decrement();
    }

    set_terminal_mode_(false);
}

void StdinEventHandler::callback_set_nts_() noexcept
{
    activation_times_.enable();
    stdin_listener_thread_ = std::thread(&StdinEventHandler::stdin_listener_thread_routine_, this);
}

void StdinEventHandler::callback_unset_nts_() noexcept
{
    activation_times_.disable();
    stdin_listener_thread_.join();
}

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */
