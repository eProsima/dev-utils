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
 * @file Heritable.ipp
 */

#pragma once

#include <cpp_utils/exception/InitializationException.hpp>
#include <cpp_utils/exception/ValueAccessException.hpp>

namespace eprosima {
namespace utils {

///////////////////////
// CONSTRUCTORS
///////////////////////

template <class T>
Heritable<T>::Heritable(T* ptr)
    : data_reference_(ptr)
{
}

template <class T>
template <typename ... Args>
Heritable<T>::Heritable(Args... args)
    : Heritable(new T(std::forward<Args>(args)...))
{
}

template <class T>
Heritable<T>::Heritable(const T& copy_element)
    : Heritable(new T(copy_element))
{
}

template <class T>
Heritable<T>::Heritable(T&& move_element)
    : Heritable(new T(std::move(move_element)))
{
}

template <class T>
Heritable<T>::Heritable(const Heritable<T>& other)
    : Heritable(new T(other.get_reference()))
{
}

template <class T>
Heritable<T>::Heritable(Heritable<T>&& other)
    : Heritable(new T(std::move(other.get_reference())))
{
}

template <class T>
Heritable<T>& Heritable<T>::operator =(const Heritable<T>& other)
{
    data_reference_.reset(new T(other.get_reference()));
    return *this;
}

template <class T>
Heritable<T>& Heritable<T>::operator =(Heritable<T>&& other)
{
    data_reference_.reset(new T(std::move(other.get_reference())));
    return *this;
}

///////////////////////
// OPERATOR
///////////////////////

template <class T>
T& Heritable<T>::operator *() const noexcept
{
    return data_reference_.operator*();
}

///////////////////////
// ACCESS DATA METHODS
///////////////////////

template <class T>
T& Heritable<T>::get_reference() const noexcept
{
    return this->operator*();
}


} /* namespace utils */
} /* namespace eprosima */
