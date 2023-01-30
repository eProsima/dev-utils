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
 * @file Singleton.hpp
 *
 * This file contains class Singleton definition.
 */

#pragma once

#include <atomic>
#include <memory>
#include <mutex>

namespace eprosima {
namespace utils {

/**
 * TODO
 */
template <typename T, int Index = 0>
class IniciableSingleton
{
public:

    //! Get a reference to the instance of this Singleton
    template <typename ... Args>
    static bool initialize(Args... args);

    //! Get a reference to the instance of this Singleton
    static T* get_instance() noexcept;

    /**
     * @brief Get a shared reference to the instance of this Singleton
     *
     * This method is useful to manage the order of destruction between singletons, as holding the shared_ptr
     * of one of them force it to not be destroyed until after the holder is destroyed.
     *
     * @warning Do not create a double loop between shared references in Singletons, or it will force a memory leak.
     */
    static std::shared_ptr<T> get_shared_instance() noexcept;

protected:

    template <typename ... Args>
    static std::shared_ptr<T> initialize_(Args... args);

    static std::shared_ptr<T> the_ptr_;
    static std::mutex mtx_;

private:

    /**
     * @brief Protected default constructor specifies that none can create an instance of this class.
     *
     * @note this constructor must exist (cannot be deleted), otherwise this class could not be used.
     * However, this ctor will never be called anywhere.
     */
    IniciableSingleton() = default;
};

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/types/impl/IniciableSingleton.ipp>
