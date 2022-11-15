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

/**
 * @brief TODO
 */
class RandomManager
{
public:

    RandomManager() = default;

    RandomManager(const unsigned int original_seed);

    virtual ~RandomManager() = default;

    template <bool Pure = false>
    unsigned int rand () noexcept;

    CPP_UTILS_DllAPI unsigned int rand (const unsigned int seed) noexcept;

protected:

    std::random_device pure_random_generator_;
    std::minstd_rand seed_random_generator_;
    std::minstd_rand std_random_generator_;
};

} /* namespace utils */
} /* namespace eprosima */
