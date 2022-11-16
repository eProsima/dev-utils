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
 * @file math_extension.cpp
 *
 */

#include <cpp_utils/math/random/RandomManager.hpp>

namespace eprosima {
namespace utils {

RandomManager::RandomManager(const RandomNumberType original_seed /* = 1 */ )
{
    std::srand(original_seed);
}

template <>
CPP_UTILS_DllAPI RandomNumberType RandomManager::rand<true> () noexcept
{
    return pure_random_generator_();
}

template <>
CPP_UTILS_DllAPI RandomNumberType RandomManager::rand<false> () noexcept
{
    return std::rand();
}

RandomNumberType RandomManager::pure_rand () noexcept
{
    return rand<true>();
}

void RandomManager::srand (const RandomNumberType seed /* = 1 */ ) noexcept
{
    std::srand(seed);
}

RandomNumberType RandomManager::rand (const RandomNumberType seed) noexcept
{
    seed_random_generator_.seed(seed);
    return seed_random_generator_();
}

} /* namespace utils */
} /* namespace eprosima */
