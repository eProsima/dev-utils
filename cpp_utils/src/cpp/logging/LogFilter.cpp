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

#include <cpp_utils/logging/LogFilter.hpp>

namespace eprosima {
namespace utils {

/**
 * @brief \c LogFilter to stream serialization
 */
CPP_UTILS_DllAPI
std::ostream& operator <<(
        std::ostream& os,
        const LogFilter& filter)
{
    os << "Log Filter: {Kind: Error, Regex: " << filter.error.get_value() << "}; "
       << "{Kind: Warning, Regex: " << filter.warning.get_value() << "}; "
       << "{Kind: Info, Regex: " << filter.info.get_value() << "}";

    return os;
}

} /* namespace utils */
} /* namespace eprosima */