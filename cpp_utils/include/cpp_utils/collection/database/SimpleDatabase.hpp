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

#include <cstddef>
#include <iterator>
#include <map>
#include <new>
#include <type_traits>
#include <shared_mutex>

#include <cpp_utils/collection/database/IModificableDatabase.hpp>

namespace eprosima {
namespace utils {

template <typename Key, typename Value>
class SimpleDatabaseIterator : public std::map<Key, Value>::const_iterator
{
public:

    SimpleDatabaseIterator(
            typename std::map<Key, Value>::const_iterator it,
            std::shared_mutex& mutex)
        : std::map<Key, Value>::const_iterator(it)
        , mutex_(mutex)
    { mutex_.lock_shared(); }

    ~SimpleDatabaseIterator()
    { mutex_.unlock_shared(); }

private:

    std::shared_mutex& mutex_;
};

/**
 * TODO
 */
template <typename Key, typename Value>
class SimpleDatabase : public IModificableDatabase<Key, Value, SimpleDatabaseIterator<Key, Value>>
{
public:

    bool add(
            Key&& key,
            Value&& value) override;

    bool modify(
            const Key& key,
            Value&& value) override;

    bool erase(
            const Key& key) override;

    bool is(
            const Key& key) const override;

    SimpleDatabaseIterator<Key, Value> find(
            const Key& key) const override;

    SimpleDatabaseIterator<Key, Value> begin() const override;
    SimpleDatabaseIterator<Key, Value> end() const override;

    template<typename V = Value>
    typename std::enable_if<std::is_copy_constructible<V>::value, Value>::type
    at(
            const Key& key) const;

    unsigned int size() const noexcept;

protected:

    std::map<Key, Value> internal_db_;

    mutable std::shared_mutex mutex_;
};

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/collection/database/impl/SimpleDatabase.ipp>
