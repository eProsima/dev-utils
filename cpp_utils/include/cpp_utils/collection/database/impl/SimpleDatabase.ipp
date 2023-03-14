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

#pragma once

namespace eprosima {
namespace utils {

template <typename Key, typename Value>
bool SimpleDatabase<Key, Value>::add(
        Key&& key,
        Value&& value)
{
    // TODO
    return false;
}

template <typename Key, typename Value>
bool SimpleDatabase<Key, Value>::modify(
        const Key& key,
        Value&& value)
{
    // TODO
    return false;
}

template <typename Key, typename Value>
bool SimpleDatabase<Key, Value>::remove(
        const Key& key)
{
    // TODO
    return false;
}

template <typename Key, typename Value>
bool SimpleDatabase<Key, Value>::is(
        const Key& key) const
{
    // TODO
    return false;
}

template <typename Key, typename Value>
Value* SimpleDatabase<Key, Value>::get(
        const Key& key) const
{
    // TODO
    return nullptr;
}

template <typename Key, typename Value>
typename std::map<Key, Value>::const_iterator SimpleDatabase<Key, Value>::begin() const
{
    return internal_db_.begin();
}

template <typename Key, typename Value>
typename std::map<Key, Value>::const_iterator SimpleDatabase<Key, Value>::end() const
{
    return internal_db_.end();
}

} /* namespace utils */
} /* namespace eprosima */
