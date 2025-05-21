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

#pragma once

#include <string>
#include <vector>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {
namespace history {

class CommandHistoryHandler
{
public:

    /**
     * @brief This constructor initializes a CommandHistoryHandler instance,
     * setting current_index_ to -1 to indicate that no command in the history is currently selected.
     * This is used to manage user input history.
     */
    CPP_UTILS_DllAPI
    CommandHistoryHandler();

    CPP_UTILS_DllAPI
    void add_command(
            const std::string& command);

    CPP_UTILS_DllAPI
    std::string get_previous_command();

    CPP_UTILS_DllAPI
    std::string get_next_command();

private:

    std::vector<std::string> command_history_;

    size_t current_index_;
};

} /* namespace history */
} /* namespace utils */
} /* namespace eprosima */