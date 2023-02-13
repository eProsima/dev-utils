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
#include <cpp_utils/Log.hpp>

namespace eprosima {
namespace utils {

///////////////////////
// CONSTRUCTORS
///////////////////////

template <typename T>
Heritable<T>::Heritable(T* ptr)
    : data_ptr_(ptr)
{
    logError(DEBUG, this << "\t CTor ptr\t " << data_ptr_);
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

    data_ptr_ = t_ptr;
    logError(DEBUG, this << "\t CTor ptr U\t " << data_ptr_);
}

template <typename T>
Heritable<T>::Heritable(const Heritable<T>& other)
    : Heritable(other.copy_internal_())
{
    logError(DEBUG, this << "\t CTor copy\t " << data_ptr_);
}

template <typename T>
Heritable<T>::Heritable(Heritable<T>&& other)
    : Heritable(other.move_internal_())
{
    logError(DEBUG, this << "\t CTor move\t " << data_ptr_);
}

template <typename T>
template <typename U>
Heritable<T>::Heritable(const Heritable<U>& other)
    : Heritable(other.copy_internal_())
{
    logError(DEBUG, this << "\t CTor copy U\t " << data_ptr_);
}

template <typename T>
template <typename U>
Heritable<T>::Heritable(Heritable<U>&& other)
    : Heritable(other.move_internal_())
{
    logError(DEBUG, this << "\t CTor move U\t " << data_ptr_);
}

template <typename T>
Heritable<T>& Heritable<T>::operator =(const Heritable<T>& other)
{
    data_ptr_ = other.copy_internal_();
    return *this;
}

template <typename T>
Heritable<T>& Heritable<T>::operator =(Heritable<T>&& other)
{
    data_ptr_ = other.move_internal_();
    return *this;
}

template <typename T>
Heritable<T>::~Heritable()
{
    logError(DEBUG, this << "\t DTor\t\t " << data_ptr_);
    if (data_ptr_)
    {
        delete data_ptr_;
    }
}

///////////////////////
// PTR OPERATOR
///////////////////////

template <typename T>
T* Heritable<T>::operator ->() const noexcept
{
    return data_ptr_;
}

template <typename T>
T& Heritable<T>::operator *() const noexcept
{
    return *data_ptr_;
}

///////////////////////
// COMPARE OPERATOR
///////////////////////

template <typename T>
bool Heritable<T>::operator ==(const Heritable<T>& other) const noexcept
{
    return (*data_ptr_) == (*other);
}

template <typename T>
bool Heritable<T>::operator ==(const T& other) const noexcept
{
    return (*data_ptr_) == other;
}

template <typename T>
bool Heritable<T>::operator <(const Heritable<T>& other) const noexcept
{
    return (*data_ptr_) < (*other);
}

///////////////////////
// ACCESS DATA METHODS
///////////////////////

template <typename T>
T& Heritable<T>::get_reference() const noexcept
{
    return this->operator*();
}

///////////////////////
// CAST OPERATORS & METHODS
///////////////////////

// template <typename T>
// template <typename U>
// bool Heritable<T>::can_cast() const noexcept
// {
//     try
//     {
//         dyn_cast<U>();
//         return true;
//     }
//     catch(const std::bad_cast& /* e */)
//     {
//         return false;
//     }
// }

// template <typename T>
// template <typename U>
// Heritable<U>& Heritable<T>::dyn_cast() const
// {
//     U& c = dynamic_cast<U&>(*data_ptr_.get());
//     return c;
// }

///////////////////////
// STATIC METHODS
///////////////////////

template <typename T>
template <typename ... Args>
Heritable<T> Heritable<T>::make_heritable(Args&&... args)
{
    return Heritable<T>(new  T(std::forward<Args>(args)...));
}

template <typename T>
T* Heritable<T>::copy_internal_() const
{
    T* switch_ptr = data_ptr_;
    data_ptr_ = new T(*data_ptr_);
    logError(DEBUG, this << "\t switch\t " << switch_ptr << " for\t " << data_ptr_);
    return switch_ptr;
}

template <typename T>
T* Heritable<T>::move_internal_() const
{
    T* switch_ptr = data_ptr_;
    data_ptr_ = nullptr;
    logError(DEBUG, this << "\t switch\t " << switch_ptr << " for\t " << data_ptr_);
    return switch_ptr;
}

} /* namespace utils */
} /* namespace eprosima */
