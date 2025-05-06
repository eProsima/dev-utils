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
    #include <sys/ioctl.h>
    #include <termios.h>
    #include <unistd.h>
#endif // if defined(_WIN32) || defined(_WIN64)

#include <cpp_utils/event/StdinEventHandler.hpp>
#include <cpp_utils/exception/InitializationException.hpp>
#include <cpp_utils/Log.hpp>

namespace eprosima {
namespace utils {
namespace event {

int get_terminal_width()
{
    #if defined(_WIN32) || defined(_WIN64)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    #endif // if defined(_WIN32) || defined(_WIN64)
}

int compute_lines_needed(const std::string& prompt, const std::string& cmd, int term_width)
{
    int total_length = static_cast<int>(prompt.size() + cmd.size());
    return (total_length + term_width - 1) / term_width;
}

void clear_lines(int line_count)
{
    for (int i = 0; i < line_count; ++i)
    {
        std::cout << "\033[2K\r"; // Clear current line
        if (i < line_count - 1)
        {
            std::cout << "\033[1A"; // Move up (not after last line)
        }
    }
}

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

void StdinEventHandler::set_terminal_mode_(
        bool enable) noexcept
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
#endif // if defined(_WIN32) || defined(_WIN64)
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
#endif // if defined(_WIN32) || defined(_WIN64)
                    {
                        std::string prev_command = history_handler_.get_previous_command();
                        if (!prev_command.empty())
                        {
                            std::string prompt = ">> ";
                            int term_width = get_terminal_width();
                            int lines = compute_lines_needed(prompt, read_str, term_width);
                            clear_lines(lines);
                            read_str = prev_command;
                            //std::cout << "\r\033[K";
                            std::cout << "\033[38;5;82m" << prompt << "\033[0m" << read_str << std::flush;
                         
                            //std::cout << "\033[38;5;82m>>\033[0m " << read_str << std::flush;
                        }

                        break;
                    }

#if defined(_WIN32) || defined(_WIN64)
                    case 80:  // Arrow down
#else
                    case 'B':  // Arrow down
#endif // if defined(_WIN32) || defined(_WIN64)
                    {
                        std::string next_command = history_handler_.get_next_command();
                        if (!next_command.empty())
                        {
                            std::string prompt = ">> ";
                            int term_width = get_terminal_width();
                            int lines = compute_lines_needed(prompt, read_str, term_width);
                            clear_lines(lines);
                            read_str = next_command;
                            // std::cout << "\r\033[K";
                            // std::cout << "\033[38;5;82m>>\033[0m " << read_str << std::flush;
                            std::cout << "\033[38;5;82m" << prompt << "\033[0m" << read_str << std::flush;
                        }
                        else
                        {
                            std::string prompt = ">> ";
                            int term_width = get_terminal_width();
                            int lines = compute_lines_needed(prompt, read_str, term_width);
                            clear_lines(lines);
                                                    
                            read_str = "";
                            std::cout << "\033[38;5;82m" << prompt << "\033[0m" << std::flush;

                            // read_str = "";
                            // std::cout << "\r\033[K";
                            // std::cout << "\033[1;36m>>\033[0m " << std::flush;
                        }

                        break;
                    }
                }
            }
            else if (c == '\n' || c == '\r')
            {
                std::cout << std::endl;
                event_occurred_(read_str);

                if (!is_ignoring_input() && !read_str.empty())
                {
                    history_handler_.add_command(read_str);
                }
                
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

void StdinEventHandler::set_ignore_input(bool ignore) noexcept
{
    ignore_input_.store(ignore, std::memory_order_relaxed);
}

bool StdinEventHandler::is_ignoring_input() const noexcept
{
    return ignore_input_.load(std::memory_order_relaxed);
}

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */
