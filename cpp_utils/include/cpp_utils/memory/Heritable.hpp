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
 * @file Heritable.hpp
 *
 * This file contains class Heritable definition.
 */

#pragma once

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

/**
 * TODO
 */
template <class T>
class Heritable
{
public:

    ///////////////////////
    // CONSTRUCTORS
    ///////////////////////

    Heritable(T* ptr);

    template <typename ... Args>
    Heritable(Args... args);

    Heritable(const T& copy_element);

    Heritable(T&& move_element);

    Heritable(const Heritable<T>& other);

    Heritable(Heritable<T>&& other);

    Heritable<T>& operator =(const Heritable<T>& other);

    Heritable<T>& operator =(Heritable<T>&& other);

    ~Heritable() = default;

    ///////////////////////
    // OPERATOR
    ///////////////////////

    T* operator ->() const noexcept;

    T& operator *() const noexcept;

    bool operator ==(const Heritable<T>& other);

    bool operator ==(const T& other);

    bool operator <(const Heritable<T>& other);

    bool operator <(const T& other);

    //! Check whether the internal ptr is valid (call \c is_valid )
    // operator bool() const noexcept;

    operator T&() const noexcept;

    template <typename U>
    operator U&() const noexcept;

    template <typename U>
    operator Heritable<U>() const noexcept;

    ///////////////////////
    // ACCESS DATA METHODS
    ///////////////////////

    T* get() const noexcept;

    T& get_reference() const noexcept;

    // bool is_valid() const noexcept;

    template <typename U>
    Heritable<U> dyn_cast() const noexcept;

protected:

    ////////////////////////////
    // INTERNAL VARIABLES
    ////////////////////////////

    //! Internal shared data protected while this object exists
    std::unique_ptr<T> data_reference_;

};

////////////////////////////
// EXTERNAL OPERATORS
////////////////////////////

//! Allow to compare a Heritable with nullptr
template<class T>
bool operator ==(
        const Heritable<T>& lhs,
        std::nullptr_t) noexcept;

//! Allow to compare a Heritable with nullptr in the other direction (from C++20 this is not needed)
template<class T>
bool operator ==(
        std::nullptr_t,
        const Heritable<T>& lhs) noexcept;

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/memory/impl/Heritable.ipp>
