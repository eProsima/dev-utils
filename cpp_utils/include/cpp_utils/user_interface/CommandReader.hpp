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

#pragma once

#include <cpp_utils/event/StdinEventHandler.hpp>
#include <cpp_utils/enum/EnumBuilder.hpp>
#include <cpp_utils/wait/DBQueueWaitHandler.hpp>

namespace eprosima {
namespace utils {

template <typename CommandEnum>
struct Command
{
    CommandEnum command;
    std::vector<std::string> arguments;
};

/**
 * TODO
 */
template <typename CommandEnum>
class CommandReader
{
public:

    CommandReader(
            const EnumBuilder<CommandEnum>& builder,
            std::istream& source = std::cin);

    bool read_next_command(Command<CommandEnum>& command);

protected:

    void read_command_callback_(std::string command_read);

    EnumBuilder<CommandEnum> builder_;

    event::StdinEventHandler stdin_handler_;

    event::DBQueueWaitHandler<std::string> commands_read_;
};

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/user_interface/impl/CommandReader.ipp>
