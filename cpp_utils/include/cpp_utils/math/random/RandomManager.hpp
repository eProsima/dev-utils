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
 * @file RandomManager.hpp
 *
 * This file contains class RandomManager definition.
 */

#pragma once

#include <random>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

using RandomNumberType = unsigned int;

/**
 * @brief TODO
 */
class RandomManager
{
public:

    RandomManager(const RandomNumberType original_seed = 1);

    virtual ~RandomManager() = default;

    template <bool Pure = false>
    RandomNumberType rand () noexcept;

    CPP_UTILS_DllAPI RandomNumberType pure_rand () noexcept;

    CPP_UTILS_DllAPI void srand (const RandomNumberType seed = 1) noexcept;

    CPP_UTILS_DllAPI RandomNumberType rand (const RandomNumberType seed) noexcept;

protected:

    std::random_device pure_random_generator_;

    /**
     * @brief
     *
     * @note using \c minstd_rand heads to seed 0 producing same value as seed 1.
     */
    std::mt19937 seed_random_generator_;
};

} /* namespace utils */
} /* namespace eprosima */
