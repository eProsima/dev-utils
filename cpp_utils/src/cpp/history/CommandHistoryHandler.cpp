// Copyright 2024 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <cpp_utils/history/CommandHistoryHandler.hpp>

namespace eprosima {
namespace utils {
namespace history {

CommandHistoryHandler::CommandHistoryHandler()
    : current_index_(-1)
{
}

void CommandHistoryHandler::add_command(
        const std::string& command)
{
    if (!command.empty())
    {
        command_history_.push_back(command);
        current_index_ = command_history_.size();
    }
}

std::string CommandHistoryHandler::get_previous_command()
{
    if (!command_history_.empty() && current_index_ > 0)
    {
        --current_index_;
        return command_history_[current_index_];
    }
    return "";
}

std::string CommandHistoryHandler::get_next_command()
{
    if (current_index_ < command_history_.size() - 1)
    {
        ++current_index_;
        return command_history_[current_index_];
    }
    else if (current_index_ == command_history_.size() - 1)
    {
        ++current_index_;
        return "";
    }
    return "";
}

} /* namespace history */
} /* namespace utils */
} /* namespace eprosima */