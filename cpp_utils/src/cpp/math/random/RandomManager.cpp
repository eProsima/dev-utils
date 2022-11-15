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

RandomManager::RandomManager(const unsigned int original_seed)
{
    std_random_generator_.seed(original_seed);
}

template <>
CPP_UTILS_DllAPI unsigned int RandomManager::rand<true> () noexcept
{
    return pure_random_generator_();
}

template <>
CPP_UTILS_DllAPI unsigned int RandomManager::rand<false> () noexcept
{
    return std_random_generator_();
}

unsigned int RandomManager::rand (const unsigned int seed) noexcept
{
    seed_random_generator_.seed(seed);
    return seed_random_generator_();
}

} /* namespace utils */
} /* namespace eprosima */
