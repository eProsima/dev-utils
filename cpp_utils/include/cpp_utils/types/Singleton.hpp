// Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <memory>
#include <mutex>

namespace eprosima {
namespace utils {

template <typename T, int Index = 0>
class Singleton
{
public:

    /**
     * @brief
     *
     */
    static T* get_instance() noexcept;

    static std::shared_ptr<T> get_shared_instance() noexcept;

protected:

    Singleton() = default;
 };

} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/types/impl/Singleton.ipp>
