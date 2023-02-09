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
 * @file Builder.hpp
 *
 * This file contains class Builder definition.
 */

#pragma once

#include <map>
#include <set>

namespace eprosima {
namespace utils {

/**
 * @brief Class that converts a string to an enumeration value.
 *
 * This class has an internal map with values of an enumeration (not necessarily all) that points to set of strings
 * with the strings that each value has associated.
 * In order to retrieve an enumeration value from a string, the string is looked for in the sets until it is found.
 *
 * @note This class could be used as a Singleton associated with an enumeration.
 * Use \c eProsima_ENUMERATION_BUILDER to initialize the values in compilation time and use them in all the process.
 *
 * @example
 * enum class CustomEnumeration{ value_1, value_2 };
 * eProsima_ENUMERATION_BUILDER(CustomEnumerationBuilder, CustomEnumeration,
 *  { { CustomEnumeration::value_1 , "v1" } , { CustomEnumeration::value_2 , "v2" } );
 *
 * // Somewhere in the process
 * auto res = CustomEnumerationBuilder::get_instance()->string_to_enumeration("v2"); // res = CustomEnumeration::value_2
 */
template <typename Key, typename Value>
class Builder
{
public:

    /**
     * @brief Construct a new Enum Builder object by giving a map of values.
     *
     * The key of the map are the different enumeration values.
     * The strings in the set of each value of the map are the strings that are associated with that enum value.
     *
     * @param keys_to_values Map of values.
     */
    Builder(
        const std::map<Key, Value>& keys_to_values);

    Builder(
        const std::map<Value, std::set<Key>>& values_to_keys);

    //! Change the internal map of values for a new one.
    void refactor_values(
            const std::map<Key, Value>& keys_to_values);

    //! Change the internal map of values for a new one.
    void refactor_values(
            const std::map<Value, std::set<Key>>& values_to_keys);

    /**
     * @brief Give the enumeration value associated with the string given.
     *
     * @param [in] key string associated with a value.
     * @param [out] return_value enumeration value associated.
     * @return true if the string \c key has an associated value.
     * @return false otherwise.
     */
    bool find(
            const Key& key,
            Value& return_value) const noexcept;

    /**
     * @brief Give the enumeration value associated with the string given.
     *
     * @param [in] key string associated with a value.
     * @param [out] value enumeration value associated.
     * @return the related enumeration value for the string given.
     *
     * @throw \c ValueNotAllowedException if there is no value related with this string.
     */
    Value find(
            const Key& key) const;

protected:

    std::map<Key, Value> indexed_map_from_values_to_keys_(const std::map<Value, std::set<Key>>& values_to_keys);

    /**
     * Map with the values of enumeration and the strings associated.
     * The key of the map are the different enumeration values.
     * The strings in the set of each value of the map are the strings that are associated with that enum value.
     */
    std::map<Key, Value> values_ {};

};

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/types/impl/Builder.ipp>
