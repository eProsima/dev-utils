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

#include <map>

#include <cpp_utils/collection/database/IModificableDatabase.hpp>
#include <cpp_utils/types/Atomicable.hpp>

namespace eprosima {
namespace utils {

/**
 * Class that represents a generic database of values indexed by key.
 */
template <typename Key, typename Value>
class SimpleDatabase : public IModificableDatabase<Key, Value, typename std::map<Key, Value>::const_iterator>
{
public:

    bool add(
            Key&& key,
            Value&& value) override;

    bool modify(
            const Key& key,
            Value&& value) override;

    bool remove(
            const Key& key) override;

    bool is(
            const Key& key) const override;

    Value* get(
            const Key& key) const override;


    typename std::map<Key, Value>::const_iterator begin() const override;
    typename std::map<Key, Value>::const_iterator end() const override;

protected:

    using DbType = SharedAtomicable<std::map<Key, Value>>;

    DbType internal_db_;
};

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/collection/database/impl/SimpleDatabase.ipp>
