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

/**
 * @file EnumBuilder.ipp
 *
 * This file contains class EnumBuilder implementation.
 */

#pragma once

#include <cpp_utils/exception/ValueNotAllowedException.hpp>

namespace eprosima {
namespace utils {

template<typename E>
EnumBuilder<E>::EnumBuilder(
        const std::map<E, std::set<std::string>>& map_values)
    : values_(map_values)
{
    // Do nothing
}

template<typename E>
void EnumBuilder<E>::refactor_values(
        const std::map<E, std::set<std::string>>& map_values)
{
    values_ = map_values;
}

template<typename E>
bool EnumBuilder<E>::string_to_enumeration(
        const std::string& enum_str,
        E& enum_value) const noexcept
{
    for (const auto& aliases : values_)
    {
        if (std::find_if(std::cbegin(aliases.second), std::cend(aliases.second),
                [enum_str](std::string str)
                {
                    return enum_str == str;
                }) != std::cend(aliases.second))
        {
            // Alias match, since std::find returned iterator before end
            enum_value = aliases.first;
            return true;
        }
    }
    return false;
}

template<typename E>
E EnumBuilder<E>::string_to_enumeration(
        const std::string& enum_str) const
{
    E value;
    if (string_to_enumeration(enum_str, value))
    {
        return value;
    }
    else
    {
        throw ValueNotAllowedException(
            STR_ENTRY <<
                "Value " << enum_str << " is not valid for enumeration " << TYPE_NAME(this) << "."
        );
    }
}

} /* namespace utils */
} /* namespace eprosima */
