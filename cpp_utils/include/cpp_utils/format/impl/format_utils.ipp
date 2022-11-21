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
 * @file format_utils.ipp
 */

#pragma once

#include <type_traits>

namespace eprosima {
namespace utils {
namespace format {

template <typename C>
std::ostream& container_to_stream(
        std::ostream& os,
        const C& container,
        const std::string& separator /* = ";"*/)
{
    if (!container.size() == 0)
    {
        auto it = container.begin();
        os << *it;
        ++it;
        for (; it != container.end(); ++it)
        {
            os << separator;
            os << *it;
        }
    }

    return os;
}

template <typename T>
std::string generic_to_string(
        const T& element) noexcept
{
    std::ostringstream os;
    os << element;
    return os.str();
}

} /* namespace format */
} /* namespace utils */
} /* namespace eprosima */
