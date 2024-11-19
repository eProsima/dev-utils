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
// limitations under the License\.

#pragma once

#include <ostream>
#include <string>

#include <cpp_utils/library/library_dll.h>
#include <cpp_utils/types/Fuzzy.hpp>


namespace eprosima {
namespace utils {

/**
 * @brief The LogFilter struct provides filtering options for log entries based on their severity levels.
 */
struct LogFilter
{
    CPP_UTILS_DllAPI
    LogFilter() = default;

    /////////////////////////
    // VARIABLES
    /////////////////////////

    Fuzzy<std::string> info;
    Fuzzy<std::string> warning;
    Fuzzy<std::string> error;
};

/**
 * @brief \c LogFilter to stream serialization
 */
CPP_UTILS_DllAPI
std::ostream& operator <<(
        std::ostream& os,
        const LogFilter& filter);

} /* namespace utils */
} /* namespace eprosima */