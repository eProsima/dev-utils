// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License")
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
 * @file StaticRegistry.ipp
 *
 */

#pragma once

namespace eprosima {
namespace utils {

template <typename Key, typename Value, int Index>
void StaticRegistry<Key, Value, Index>::register_value(const Key& key, const Value& value)
{
    Singleton<std::map<Key, Value>, Index>::get_instance()->emplace(key, value);
}

template <typename Key, typename Value, int Index>
bool StaticRegistry<Key, Value, Index>::get(const Key& key, Value& value_got) noexcept
{
    auto singleton_ref = Singleton<std::map<Key, Value>, Index>::get_instance();
    auto it = singleton_ref->find(key);

    if (it == singleton_ref->end())
    {
        return false;
    }
    else
    {
        value_got = it.second;
        return true;
    }
}

template <typename Key, typename Value, int Index>
std::map<Key, Value>& StaticRegistry<Key, Value, Index>::ref() noexcept
{
    return *Singleton<std::map<Key, Value>, Index>::get_instance();
}

} /* namespace utils */
} /* namespace eprosima */
