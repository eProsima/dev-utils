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
 * @file StaticRegistry.hpp
 *
 * This file contains class StaticRegistry definition.
 */

#pragma once

#include <map>

#include <cpp_utils/types/Singleton.hpp>

namespace eprosima {
namespace utils {

/**
 * TODO
 */
template <typename Key, typename Value, int Index = 0>
class StaticRegistry : public Singleton<std::map<Key, Value>, Index>
{
public:

    static void register_value(const Key& key, const Value& value);

    static bool get(const Key& key, Value& value_got) noexcept;

    static Value& get(const Key& key);

protected:

    static std::map<Key, Value>& ref() noexcept;

private:

    StaticRegistry() = default;
};

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/types/impl/StaticRegistry.ipp>
