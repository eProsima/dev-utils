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
 * @file EnumBuilder.hpp
 *
 * This file contains class EnumBuilder definition.
 */

#pragma once

#include <map>
#include <vector>
#include <string>

#include <cpp_utils/types/Singleton.hpp>

namespace eprosima {
namespace utils {

/**
 * TODO
 */
template <typename E, int Index = 0>
class EnumBuilder : public Singleton<std::map<E, std::set<std::string>>, Index>
{
public:

    static bool initialize_builder(
            const std::map<E, std::set<std::string>>& map_values,
            bool force = false);

    static bool string_to_enumeration(
            const std::string& enum_str,
            E& enum_value) noexcept;

    static E string_to_enumeration(
            const std::string& enum_str);

protected:

    static bool initialized;

private:

    EnumBuilder() = default;
};

#define eProsima_ENUMERATION_BUILDER(enum_name, values_map) \
    bool __INITIALIZE_STATUS_ ## enum_name = eprosima::utils::EnumBuilder< enum_name >::initialize_builder( values_map )

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/enum/impl/EnumBuilder.ipp>
