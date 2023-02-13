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

    template <typename U>
    Heritable(U* ptr);

    Heritable(const Heritable<T>& other);

    Heritable(Heritable<T>&& other);

    template <typename U>
    Heritable(const Heritable<U>& other);

    template <typename U>
    Heritable(Heritable<U>&& other);

    Heritable<T>& operator =(const Heritable<T>& other);

    Heritable<T>& operator =(Heritable<T>&& other);

    ~Heritable();

    ///////////////////////
    // PTR OPERATORS
    ///////////////////////

    T* operator ->() const noexcept;

    T& operator *() const noexcept;

    ///////////////////////
    // COMPARE OPERATORS
    ///////////////////////

    bool operator ==(const Heritable<T>& other) const noexcept;

    bool operator ==(const T& other) const noexcept;

    bool operator <(const Heritable<T>& other) const noexcept;

    ///////////////////////
    // ACCESS DATA METHODS
    ///////////////////////

    T& get_reference() const noexcept;

    ///////////////////////
    // CAST OPERATORS & METHODS
    ///////////////////////

    // template <typename U>
    // operator Heritable<U>&() const;

    // template <typename U>
    // bool can_cast() const noexcept;

    // template <typename U>
    // Heritable<U>& dyn_cast() const;

    ///////////////////////
    // STATIC METHODS
    ///////////////////////

    template <typename ... Args>
    static Heritable<T> make_heritable(Args&&... args);

protected:

    ///////////////////////
    // INTERNAL METHODS
    ///////////////////////

    T* copy_internal_() const;

    T* move_internal_() const;

    ////////////////////////////
    // INTERNAL VARIABLES
    ////////////////////////////

    //! Internal shared data protected while this object exists
    mutable T* data_ptr_ = nullptr;

    template <typename U>
    friend class Heritable;
};

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/memory/impl/Heritable.ipp>
