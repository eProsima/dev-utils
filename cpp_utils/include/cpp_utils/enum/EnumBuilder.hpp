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

#include <cpp_utils/types/IniciableSingleton.hpp>

namespace eprosima {
namespace utils {

/**
 * TODO
 */
template <typename E>
class EnumBuilder
{
public:

    EnumBuilder() = default;

    EnumBuilder(
        const std::map<E, std::set<std::string>>& map_values);

    ~EnumBuilder() = default;

    bool initialize_builder(
            const std::map<E, std::set<std::string>>& map_values,
            bool force = false);

    bool string_to_enumeration(
            const std::string& enum_str,
            E& enum_value) noexcept;

    E string_to_enumeration(
            const std::string& enum_str);

protected:

    bool initialized {false};

    std::map<E, std::set<std::string>> values_ {};

};

#define eProsima_ENUMERATION_BUILDER(builder_name, enum_name, values_map) \
    typedef eprosima::utils::IniciableSingleton<eprosima::utils::EnumBuilder< enum_name >, 0> builder_name ; \
    auto __STATUS_INITIALIZATION_ ## builder_name = \
        builder_name::initialize<const std::map< enum_name , std::set<std::string>>&>( values_map )

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/enum/impl/EnumBuilder.ipp>
