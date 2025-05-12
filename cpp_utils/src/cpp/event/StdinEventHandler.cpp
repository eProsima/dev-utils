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

void update_line(
    const std::string& prompt,
    std::string& line,
    size_t& cursor_index,
    std::function<void(std::string&, size_t&)> line_modifier)
{
    int term_width = get_terminal_width();
    if (term_width <= 0) term_width = 80;

    // Save the old line and cursor index before modifying 
    std::string old_line = line;
    size_t old_cursor_index = cursor_index;

    // Apply the line modifier function
    line_modifier(line, cursor_index);

    // If the content does not change, only move the cursor
    if (line == old_line)
    {
        int old_abs_cursor = static_cast<int>(prompt.size() + old_cursor_index);
        int new_abs_cursor = static_cast<int>(prompt.size() + cursor_index);

        int old_cursor_line = old_abs_cursor / term_width;
        int new_cursor_line = new_abs_cursor / term_width;

        int line_diff = new_cursor_line - old_cursor_line;

        if (line_diff > 0)
        {
            for (int i = 0; i < line_diff; ++i)
                std::cout << "\033[1B"; // move down
        }
        else if (line_diff < 0)
        {
            for (int i = 0; i < -line_diff; ++i)
                std::cout << "\033[1A"; // move up
        }

        std::cout << "\r";
        int new_cursor_col = new_abs_cursor % term_width;
        if (new_cursor_col > 0)
            std::cout << "\033[" << new_cursor_col << "C";

        std::cout.flush();
        return;
    }

    // Remove the old line
    std::string full_line_before = prompt + old_line;
    int old_lines = (static_cast<int>(full_line_before.size()) + term_width - 1) / term_width;

    // Move to the line where the cursor was
    // Calculate the absolute cursor position
    // and the line number where it was 
    int old_abs_cursor = static_cast<int>(prompt.size() + old_cursor_index);
    int old_cursor_line = old_abs_cursor / term_width;
    int lines_to_go_down = old_lines - 1 - old_cursor_line;
    for (int i = 0; i < lines_to_go_down; ++i)
        std::cout << "\033[1B";

    for (int i = 0; i < old_lines; ++i)
    {
        std::cout << "\033[2K\r";
        if (i < old_lines - 1)
            std::cout << "\033[1A";
    }

    // Print the new line
    std::cout << "\033[38;5;82m" << prompt << "\033[0m" << line << std::flush;

    // Position the cursor
    int abs_cursor = static_cast<int>(prompt.size() + cursor_index);
    int total_lines = (static_cast<int>(prompt.size() + line.size()) + term_width - 1) / term_width;
    int cursor_line = abs_cursor / term_width;
    int cursor_col = abs_cursor % term_width;

    int lines_to_move_up = total_lines - 1 - cursor_line;
    for (int i = 0; i < lines_to_move_up; ++i)
        std::cout << "\033[1A";

    std::cout << "\r";
    if (cursor_col > 0)
        std::cout << "\033[" << cursor_col << "C";

    std::cout.flush();
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
        size_t cursor_index = 0;

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
                            cursor_index = read_str.size();
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
                            cursor_index = read_str.size();
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
                            cursor_index = 0;
                            std::cout << "\033[38;5;82m" << prompt << "\033[0m" << std::flush;

                            // read_str = "";
                            // std::cout << "\r\033[K";
                            // std::cout << "\033[1;36m>>\033[0m " << std::flush;
                        }

                        break;
                    }

#if defined(_WIN32) || defined(_WIN64)
                    case 75:  // Arrow LEFT
#else
                    case 'D':  // Arrow LEFT
#endif
                    {
                        if (cursor_index > 0)
                        {
                            update_line(">> ", read_str, cursor_index,
                                [](std::string&, size_t& index)
                                {
                                    if (index > 0)
                                    {
                                        --index;
                                    }
                                });   
                        }
                        break;
                    }

#if defined(_WIN32) || defined(_WIN64)
                    case 77:  // Arrow RIGHT
#else
                    case 'C':  // Arrow RIGHT
#endif
                    {
                        update_line(">> ", read_str, cursor_index,
                            [](std::string& line, size_t& index)
                            {
                                if (index < line.size())
                                {
                                    ++index;
                                }
                            });                        
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
                cursor_index = 0;
                break;
            }
            else if (c == '\b' || c == 127)
            {
                if (cursor_index > 0)
                {
                    update_line(">> ", read_str, cursor_index,
                        [](std::string& line, size_t& index)
                        {
                            if (index > 0)
                            {
                                line.erase(line.begin() + index - 1);
                                --index;
                            }
                        });
                    
                }
            }
            else
            {
                char ch = static_cast<char>(c);
                update_line(">> ", read_str, cursor_index,
                    [ch](std::string& line, size_t& index)
                    {
                        line.insert(line.begin() + index, ch);
                        ++index;
                    });
                
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
