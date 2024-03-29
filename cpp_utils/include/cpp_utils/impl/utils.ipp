// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file utils.ipp
 */

#pragma once

#include <cstring>

namespace eprosima {
namespace utils {

template <typename T, bool Ptr /* = false */>
std::ostream& element_to_stream(
        std::ostream& os,
        T element)
{
    if (Ptr)
    {
        os << (*element);
    }
    else
    {
        os << element;
    }

    return os;
}

template <typename T, bool Ptr /* = false */>
std::ostream& container_to_stream(
        std::ostream& os,
        std::vector<T> list,
        std::string separator /* = ";"*/)
{
    os << "{";

    size_t size = list.size();

    for (size_t i = 0; size != 0 && i < size - 1; ++i)
    {
        element_to_stream<T, Ptr>(os, list[i]);
        os << separator;
    }

    if (size > 0)
    {
        element_to_stream<T, Ptr>(os, list[size - 1]);
    }

    os << "}";

    return os;
}

template <typename T, bool Ptr /* = false */>
std::ostream& container_to_stream(
        std::ostream& os,
        std::set<T> list,
        std::string separator /* = ";" */)
{
    return container_to_stream<T, Ptr>(os, std::vector<T>(list.begin(), list.end()), separator);
}

template <typename T>
bool set_of_ptr_contains(
        const std::set<std::shared_ptr<T>> set,
        const std::shared_ptr<T> element)
{
    // If the pointer belongs to set, it is contained
    if (set.find(element) != set.end())
    {
        return true;
    }

    // If element we are looking for is nullptr, do not search as we already know it is not in the set
    // (every nullptr is compared to equal)
    if (!element)
    {
        return false;
    }

    // If not, check if any object internally is the one we are looking for
    for (auto itr = set.begin(); itr != set.end(); itr++)
    {
        // In case the set element is nullptr, do not call == or it will crash
        if (nullptr != *itr)
        {
            if (*itr->get() == *element.get())
            {
                // If are equal, element is contained
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool are_set_of_ptr_equal(
        const std::set<std::shared_ptr<T>> set1,
        const std::set<std::shared_ptr<T>> set2)
{
    if (set1.size() != set2.size())
    {
        return false;
    }

    // Check if every element in set1 is in set2
    for (auto itr1 = set1.begin(); itr1 != set1.end(); itr1++)
    {
        if (!set_of_ptr_contains(set2, *itr1))
        {
            return false;
        }
    }

    return true;
}

template <typename Parent, typename Child>
std::set<std::shared_ptr<Parent>> convert_set_to_shared(
        std::set<Child> set)
{
    FORCE_TEMPLATE_SUBCLASS(Parent, Child);

    std::set<std::shared_ptr<Parent>> result_set;
    for (Child element : set)
    {
        result_set.insert(std::make_shared<Child>(element));
    }
    return result_set;
}

template <typename T>
std::string generic_to_string(
        const T& element)
{
    std::stringstream ss;
    ss << element;
    return ss.str();
}

template <typename T>
void* copy_to_void_ptr(
        const T* source,
        size_t size /* = sizeof(T) */)
{
    void* new_ptr = std::malloc(size);
    std::memcpy(new_ptr, source, size);
    return new_ptr;
}

template <typename Key, typename Value>
std::set<Key> get_keys(
        const std::map<Key, Value>& map)
{
    std::set<Key> ret;
    for (const auto& elem : map)
    {
        ret.insert(elem.first);
    }
    return ret;
}

template <typename Key, typename Value>
std::set<Key> get_keys(
        const std::unordered_map<Key, Value>& map)
{
    std::set<Key> ret;
    for (const auto& elem : map)
    {
        ret.insert(elem.first);
    }
    return ret;
}

} /* namespace utils */
} /* namespace eprosima */
