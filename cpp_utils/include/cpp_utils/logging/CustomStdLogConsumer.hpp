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
 * @file CustomStdLogConsumer.hpp
 */

#pragma once

#include <regex>

#include <cpp_utils/Log.hpp>
#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

/**
 * TODO
 */
class CustomStdLogConsumer : public utils::LogConsumer
{
public:

    CPP_UTILS_DllAPI CustomStdLogConsumer(
            const std::string& log_filter,
            const eprosima::fastdds::dds::Log::Kind& log_verbosity);

    //! Default destructor
    CPP_UTILS_DllAPI ~CustomStdLogConsumer() noexcept = default;

    /**
     * @brief Implements \c LogConsumer \c Consume method.
     *
     * Each entry is filtered by a regex done by \c filter_ and must be equal or higher the
     * verbosity level \c verbosity_ .
     * This method will print the \c entry in std::cout with info verbosity and in std:cerr otherwise.
     *
     * @param entry entry to consume
     */
    CPP_UTILS_DllAPI void Consume(
            const Log::Entry& entry) override;

protected:

    CPP_UTILS_DllAPI virtual bool accept_entry_(
            const Log::Entry& entry);

    CPP_UTILS_DllAPI virtual std::ostream& get_stream_(
            const Log::Entry& entry);

    std::regex filter_;

    eprosima::fastdds::dds::Log::Kind verbosity_;
};

} /* namespace utils */
} /* namespace eprosima */
