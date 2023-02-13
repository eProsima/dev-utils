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

template <typename T>
Heritable<T>::Heritable(T* ptr)
    : data_reference_(ptr)
{
}

template <typename T>
template <typename U>
Heritable<T>::Heritable(U* ptr)
{
    T* t_ptr = dynamic_cast<T*>(ptr);
    if (!t_ptr)
    {
        throw std::bad_cast();
    }

    data_reference_.reset(t_ptr);
}

template <typename T>
template <typename ... Args>
Heritable<T>::Heritable(Args... args)
    : Heritable(new T(std::forward<Args>(args)...))
{
}

template <typename T>
Heritable<T>::Heritable(const T& copy_element)
    : Heritable(new T(copy_element))
{
}

template <typename T>
Heritable<T>::Heritable(T&& move_element)
    : Heritable(new T(std::move(move_element)))
{
}

template <typename T>
Heritable<T>::Heritable(const Heritable<T>& other)
    : Heritable(new T(other.get_reference()))
{
}

template <typename T>
Heritable<T>::Heritable(Heritable<T>&& other)
    : Heritable(new T(std::move(other.get_reference())))
{
}

template <typename T>
Heritable<T>& Heritable<T>::operator =(const Heritable<T>& other)
{
    data_reference_.reset(new T(other.get_reference()));
    return *this;
}

template <typename T>
Heritable<T>& Heritable<T>::operator =(Heritable<T>&& other)
{
    data_reference_.reset(new T(std::move(other.get_reference())));
    return *this;
}

///////////////////////
// PTR OPERATOR
///////////////////////

template <typename T>
T* Heritable<T>::operator ->() const noexcept
{
    return data_reference_.operator->();
}

template <typename T>
T& Heritable<T>::operator *() const noexcept
{
    return data_reference_.operator*();
}

///////////////////////
// COMPARE OPERATOR
///////////////////////

template <typename T>
bool Heritable<T>::operator ==(const Heritable<T>& other) const noexcept
{
    return (*data_reference_) == (*other);
}

template <typename T>
bool Heritable<T>::operator ==(const T& other) const noexcept
{
    return (*data_reference_) == other;
}

template <typename T>
bool Heritable<T>::operator <(const Heritable<T>& other) const noexcept
{
    return (*data_reference_) < (*other);
}

template <typename T>
bool Heritable<T>::operator <(const T& other) const noexcept
{
    return (*data_reference_) < other;
}

///////////////////////
// CAST OPERATOR
///////////////////////

template <typename T>
Heritable<T>::operator T&() const noexcept
{
    return get_reference();
}

template <typename T>
template <typename U>
Heritable<T>::operator U&() const noexcept
{
    return dyn_cast<U>();
}

///////////////////////
// ACCESS DATA METHODS
///////////////////////

template <typename T>
T* Heritable<T>::get() const noexcept
{
    return data_reference_.get();
}

template <typename T>
T& Heritable<T>::get_reference() const noexcept
{
    return this->operator*();
}

template <typename T>
template <typename U>
bool Heritable<T>::can_cast() const noexcept
{
    try
    {
        dyn_cast<U>();
        return true;
    }
    catch(const std::bad_cast& /* e */)
    {
        return false;
    }
}

template <typename T>
template <typename U>
U& Heritable<T>::dyn_cast() const
{
    U& c = dynamic_cast<U&>(*data_reference_.get());
    return c;
}

} /* namespace utils */
} /* namespace eprosima */
