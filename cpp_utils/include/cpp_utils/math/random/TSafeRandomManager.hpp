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
 * @file TSafeRandomManager.hpp
 *
 * This file contains class TSafeRandomManager definition.
 */

#pragma once

#include <random>

#include <cpp_utils/library/library_dll.h>
#include <cpp_utils/math/random/RandomManager.hpp>
#include <cpp_utils/types/Atomicable.hpp>
#include <cpp_utils/types/Singleton.hpp>

namespace eprosima {
namespace utils {

/**
 * @brief Object to manage the generation of random numbers in a thread environment.
 *
 * This class use different random generators from <random> library to obtain a complete random generator
 * with multiple features:
 * 1. Generate pure random numbers (no pseudorandom).
 * 2. Generate an always equal random sequence from a seed.
 * 3. Generate pseudorandom numbers from a specific seed (map each seed with always the same pseudorandom number).
 * These 3 features are completely independent and calls between them do not affect each other.
 *
 * Motivation: Why use this class instead of a std::rand?
 * The use of only rand and srand is not recommended by std (https://en.cppreference.com/w/cpp/numeric/random/rand).
 * Also the use of rand does not allow to create pure random numbers (it must use srand with a explicit stochastic
 * value as time(NULL) (that also can be repeated if executed in same second)) neither to keep state of random
 * sequence once a seed has been used. This means that once using rand or srand in any part of the process, the
 * random sequence will not be the same.
 * Thus, this new class allow to get pure random numbers, get pseudorandom numbers from a seed and creating
 * pseudorandom sequences without affecting the normal behaviour of rand and srand.
 *
 * @note this class is similar to \c RandomManager but thread-safe implementation
 */
class TSafeRandomManager
{
public:

    /**
     * @brief Construct a new Random Manager object.
     *
     * @param original_seed initial seed for sequence number generator.
     */
    CPP_UTILS_DllAPI TSafeRandomManager(
            const RandomSeedType& original_seed = 1);

    //! Default destructor
    CPP_UTILS_DllAPI ~TSafeRandomManager() = default;

    /***********************
    * NATIVE METHODS
    ***********************/
    /**
     * @brief Generate pure random number.
     *
     * Fulfill 1.
     * This method does not affect the sequence generation numbers.
     *
     * @return Pure random number.
     */
    CPP_UTILS_DllAPI RandomNumberType pure_rand () noexcept;

    /**
     * @brief Get next random number in pseudorandom sequence.
     *
     * Fulfill 2.
     *
     * @return Pure random number.
     */
    CPP_UTILS_DllAPI RandomNumberType sequence_rand () noexcept;

    //! Set seed for the sequence random series.
    CPP_UTILS_DllAPI void seed (
            const RandomSeedType& seed) noexcept;

    /**
     * @brief Get a random number related with a seed.
     *
     * Fulfill 3.
     * This method does not affect the sequence generation numbers.
     * This always returns the same random number for the same seed.
     *
     * @param seed to get random number.
     *
     * @return random number seeded by \c seed .
     */
    CPP_UTILS_DllAPI RandomNumberType seeded_rand (
            const RandomSeedType& seed) noexcept;


    /***********************
    * DERIVED METHODS
    ***********************/
    // This methods only extend the API using the common word rand, but they only call native methods.

    //! With Pure=true returns \c pure_rand . Otherwise returns \c sequence_rand .
    template <bool Pure = false>
    RandomNumberType rand () noexcept;

    //! Return \c seeded_rand .
    CPP_UTILS_DllAPI RandomNumberType rand (
            const RandomSeedType& seed) noexcept;

protected:

    /**
     * @brief Generation of real random numbers based on stochastic values.
     *
     * @note this class is thread safe.
     */
    std::random_device pure_random_generator_;

    //! Random generator that will not use seed (except at ctor) so always produces same random sequences.
    Atomicable<std::mt19937> std_random_generator_;

    //! Random generator from a specific seed.
    Atomicable<std::mt19937> seed_random_generator_;

    //! Guard the use of \c seed_random_generator_ class.
    std::mutex seed_random_generator_mutex_;
};

//! Global singleton to use a ThreadSafeRandomManager in the whole process.
using GlobalRandomManager = Singleton<TSafeRandomManager, 42>;

} /* namespace utils */
} /* namespace eprosima */
