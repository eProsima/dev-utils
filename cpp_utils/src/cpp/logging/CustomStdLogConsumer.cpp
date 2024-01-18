// Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/**
 * @file CustomStdLogConsumer.cpp
 *
 */

#include <cpp_utils/logging/CustomStdLogConsumer.hpp>

namespace eprosima {
namespace utils {

CustomStdLogConsumer::CustomStdLogConsumer(
        const LogFilter& log_filter_map,
        const eprosima::fastdds::dds::Log::Kind& log_verbosity)
        : filter_map_(log_filter_map)
        , verbosity_(log_verbosity)
{
    // Do nothing
}

void CustomStdLogConsumer::Consume(
        const utils::Log::Entry& entry)
{
    if (accept_entry_(entry))
    {
        std::ostream& stream = get_stream_(entry);
        print_timestamp(stream, entry, true);
        print_header(stream, entry, true);
        print_message(stream, entry, true);
        print_context(stream, entry, true);
        print_new_line(stream, true);
        stream.flush();
    }
}

bool CustomStdLogConsumer::accept_entry_(
        const Log::Entry& entry)
{
    // Filter by kind
    if (entry.kind > verbosity_)
    {
        return false;
    }
    else if (entry.kind == eprosima::fastdds::dds::Log::Kind::Error &&
            entry.kind < verbosity_)
    {
        // In case it is an error message and verbosity is not error, filter does not care
        return true;
    }

    // Filter by regex
    std::regex filter_regex(filter_map_[entry.kind]);

    if (!std::regex_search(entry.context.category, filter_regex))
    {
        return false;
    }

    return true;
}

std::ostream& CustomStdLogConsumer::get_stream_(
        const Log::Entry& entry)
{
    if (entry.kind < eprosima::fastdds::dds::Log::Kind::Warning)
    {
        return std::cout;
    }
    else
    {
        return std::cerr;
    }
}

} /* namespace utils */
} /* namespace eprosima */
