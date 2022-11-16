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

#include <algorithm>
#include <cstdlib>

#include <gtest_aux.hpp>
#include <gtest/gtest.h>

#include <cpp_utils/math/random/RandomManager.hpp>

using namespace eprosima::utils;

namespace test {

constexpr const unsigned int TEST_ITERATIONS = 100;

} /* namespace test */

/**
 * Test the generation of std random numbers from a default seed.
 *
 * This will use the \c std::rand method to know the N first values that are expected.
 *
 * STEPS:
 * - calculates the N first numbers from rand()
 * - create N Random Manager and generate N values that are equal the rand() N ones
 *
 * NOTE: this test could also be done by seeding rand to 1.
 */
TEST(randomTest, get_random_number)
{
    // calculates the N first numbers from rand()
    std::array<RandomNumberType, test::TEST_ITERATIONS> rand_numbers;
    for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
    {
        rand_numbers[i] = rand();
    }

    // create N Random Manager and generate N values that are equal the rand() N ones
    for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
    {
        RandomManager manager;
        for (unsigned int j=0; j<test::TEST_ITERATIONS; ++j)
        {
            ASSERT_EQ(manager.rand(), rand_numbers[j]) << "Manager " << i << " in iteration " << j;
        }
    }
}

/**
 * Test that the N first pure random numbers are not included in the first N values generated
 * by std::rand .
 *
 * STEPS:
 * - calculates the N first numbers from rand()
 * - create Random Manager and generate N values with method rand<true> that should not be in N first generated
 * - create Random Manager and generate N values with method pure_rand that should not be in N first generated
 */
TEST(randomTest, get_pure_random_number)
{
    // calculates the N first numbers from rand()
    std::array<RandomNumberType, test::TEST_ITERATIONS> rand_numbers;
    for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
    {
        rand_numbers[i] = rand();
    }

    // create Random Manager and generate N values with method rand<true> that should not be in N first generated
    {
        RandomManager manager;
        for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
        {
            // Generate new value
            auto new_value = manager.rand<true>();

            // Check that new value is not in array
            ASSERT_EQ(
                std::find(std::begin(rand_numbers), std::end(rand_numbers), new_value),
                std::end(rand_numbers));
        }
    }

    // create Random Manager and generate N values with method pure_rand that should not be in N first generated
    {
        RandomManager manager;
        for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
        {
            // Generate new value
            auto new_value = manager.pure_rand();

            // Check that new value is not in array
            ASSERT_EQ(
                std::find(std::begin(rand_numbers), std::end(rand_numbers), new_value),
                std::end(rand_numbers));
        }
    }
}

/**
 * Check that getting seed numbers are obtain different numbers for each seed, but the same for same seed.
 *
 * STEPS:
 * - Call rand(seed) N times, twice per seed to check value is the same, and store each unique value.
 * - Call rand(seed) N times, and check that only occurrence of value in previous array is in the same seed.
 */
TEST(randomTest, get_seed_random_number)
{
    std::array<RandomNumberType, test::TEST_ITERATIONS> seed_numbers;
    RandomManager manager;

    // Call rand(seed) N times, twice per seed to check value is the same, and store each unique value.
    for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
    {
        // Get new seeded value
        auto new_seed_value = manager.rand(i);

        // Check it always gives same value
        ASSERT_EQ(manager.rand(i), new_seed_value);

        // Store value
        seed_numbers[i] = new_seed_value;
    }

    // Call rand(seed) N times, and check that only occurrence of value in previous array is in the same seed.
    for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
    {
        // Get new seeded value
        auto new_seed_value = manager.rand(i);

        // Check that is the same as the stored value
        ASSERT_EQ(new_seed_value, seed_numbers[i]);

        // Check that any other value is different
        for (unsigned int j=0; j<test::TEST_ITERATIONS; ++j)
        {
            if (i != j)
            {
                ASSERT_NE(new_seed_value, seed_numbers[j]) <<
                    "Value " << seed_numbers[j] << " seeded with " << j <<
                    " sames as " << new_seed_value << " seeded with " << i;
            }
            else
            {
                ASSERT_EQ(new_seed_value, seed_numbers[j]);
            }
        }
    }
}

/**
 * Set seed of a Random Manager and check that values generated are the same as setting srand.
 *
 * CASES:
 * - set it from RandomManager::srand
 * - set it from RandomManager::RandomManager
 */
TEST(randomTest, set_seed)
{
    for (unsigned int i=0; i<test::TEST_ITERATIONS; ++i)
    {
        // Set rand seed in srand
        std::srand(i);

        // calculates the N first numbers from rand()
        std::array<RandomNumberType, test::TEST_ITERATIONS> rand_numbers;
        for (unsigned int j=0; j<test::TEST_ITERATIONS; ++j)
        {
            rand_numbers[j] = rand();
        }

        // set it from RandomManager::srand
        {
            RandomManager manager;
            manager.srand(i);
            for (unsigned int j=0; j<test::TEST_ITERATIONS; ++j)
            {
                ASSERT_EQ(manager.rand(), rand_numbers[j]) <<
                    "srand set Manager Iteration " << i << " in number " << j;
            }
        }

        // set it from RandomManager::RandomManager
        {
            RandomManager manager(i);
            for (unsigned int j=0; j<test::TEST_ITERATIONS; ++j)
            {
                ASSERT_EQ(manager.rand(), rand_numbers[j]) <<
                    "ctor set Manager Iteration " << i << " in number " << j;
            }
        }
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
