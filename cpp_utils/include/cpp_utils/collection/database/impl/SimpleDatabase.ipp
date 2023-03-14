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
    std::unique_lock<std::shared_mutex> _(mutex_);

    auto res = internal_db_.insert(std::move(std::pair<Key, Value>(std::move(key), std::move(value))));

    return res.second;
}

template <typename Key, typename Value>
bool SimpleDatabase<Key, Value>::modify(
        const Key& key,
        Value&& value)
{
    std::unique_lock<std::shared_mutex> _(mutex_);

    auto it = internal_db_.find(key);
    if (it == internal_db_.end())
    {
        return false;
    }

    it->second = std::move(value);

    return true;
}

template <typename Key, typename Value>
bool SimpleDatabase<Key, Value>::erase(
        const Key& key)
{
    std::unique_lock<std::shared_mutex> _(mutex_);

    return internal_db_.erase(key) != 0;
}

template <typename Key, typename Value>
bool SimpleDatabase<Key, Value>::is(
        const Key& key) const
{
    std::shared_lock<std::shared_mutex> _(mutex_);

    return internal_db_.find(key) != internal_db_.end();
}

template <typename Key, typename Value>
SimpleDatabaseIterator<Key, Value> SimpleDatabase<Key, Value>::find(
        const Key& key) const
{
    std::shared_lock<std::shared_mutex> _(mutex_);

    return SimpleDatabaseIterator<Key, Value>(internal_db_.find(key), mutex_);
}

template <typename Key, typename Value>
SimpleDatabaseIterator<Key, Value> SimpleDatabase<Key, Value>::begin() const
{
    return SimpleDatabaseIterator<Key, Value>(internal_db_.begin(), mutex_);
}

template <typename Key, typename Value>
SimpleDatabaseIterator<Key, Value> SimpleDatabase<Key, Value>::end() const
{
    return SimpleDatabaseIterator<Key, Value>(internal_db_.end(), mutex_);
}

template <typename Key, typename Value>
template<typename V>
typename std::enable_if<std::is_copy_constructible<V>::value, Value>::type
SimpleDatabase<Key, Value>::at(
        const Key& key) const
{
    std::shared_lock<std::shared_mutex> _(mutex_);

    return internal_db_.at(key);
}

template <typename Key, typename Value>
unsigned int SimpleDatabase<Key, Value>::size() const noexcept
{
    std::shared_lock<std::shared_mutex> _(mutex_);

    return internal_db_.size();
}

} /* namespace utils */
} /* namespace eprosima */
