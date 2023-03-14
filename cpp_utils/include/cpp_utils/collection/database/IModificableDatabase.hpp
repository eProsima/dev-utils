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

#include <cpp_utils/collection/database/IDatabase.hpp>

namespace eprosima {
namespace utils {

template <typename Key, typename Value, typename Iterator>
class IModificableDatabase : public IDatabase<Key, Value, Iterator>
{
public:

    virtual bool modify(
            const Key& key,
            Value&& value) = 0;

    virtual bool erase(
            const Key& key) = 0;
};

} /* namespace utils */
} /* namespace eprosima */
