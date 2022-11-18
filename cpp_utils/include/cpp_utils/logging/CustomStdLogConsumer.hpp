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
 * Custom Log Consumer with Standard (logical) behaviour.
 *
 * Registering this consumer in Fast DDS Log prints every log entry that has a higher kind than the threshold
 * given. In case messages are not of Error kind, they are filtered by category to match a regex.
 * Info messages are printed in std::cout while others are sent to std::cerr .
 *
 * @attention This consumer filters the entries that receives, but some other entries could be filtered beforehand
 * by Fast DDS Log. To avoid these, set Log verbosity to Info and do not use Category Filter.
 */
class CustomStdLogConsumer : public utils::LogConsumer
{
public:

    //! Create new CustomStdLogConsumer with regex filter generated from a string and with maximum verbosity kind.
    CPP_UTILS_DllAPI CustomStdLogConsumer(
            const std::string& log_filter,
            const eprosima::fastdds::dds::Log::Kind& log_verbosity);

    //! Default destructor
    CPP_UTILS_DllAPI ~CustomStdLogConsumer() noexcept = default;

    /**
     * @brief Implements \c LogConsumer \c Consume method.
     *
     * Each entry must be equal or higher the verbosity level \c verbosity_ .
     * Each entry category must match with regex stored in \c filter_ , except
     * those entries that are Error will be always printed if \c verbosity_ is not Error.
     *
     * This method will print the \c entry in \c std::cout with info verbosity and in \c std:cerr otherwise.
     *
     * @param entry entry to consume
     */
    CPP_UTILS_DllAPI void Consume(
            const Log::Entry& entry) override;

protected:

    //! Whether the entry must be accepted depending on kind and category
    CPP_UTILS_DllAPI virtual bool accept_entry_(
            const Log::Entry& entry);

    /**
     * @brief Get which stream must be used depending on the entry
     *
     * @param entry to decide the output stream
     *
     * @return \c std::out if entry is Info, \c std::cerr otherwise.
     */
    CPP_UTILS_DllAPI virtual std::ostream& get_stream_(
            const Log::Entry& entry);

    //! Regex filter for entry category
    std::regex filter_;

    //! Maximum Log Kind that will be printed.
    eprosima::fastdds::dds::Log::Kind verbosity_;
};

} /* namespace utils */
} /* namespace eprosima */
