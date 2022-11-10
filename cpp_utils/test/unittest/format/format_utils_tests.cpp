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

#include <cpp_utils/testing/gtest_aux.hpp>
#include <gtest/gtest.h>

#include <cpp_utils/format/format_utils.hpp>
#include <cpp_utils/format/Formatter.hpp>

using namespace eprosima::utils::format;

/**
 * @brief Test function \c to_lowercase .
 *
 * CASES:
 * - Uppercase
 * - Invariant
 * - With non-letter characters
 * - Empty
 */
TEST(format_utils_tests, to_lowercase)
{
    // Uppercase
    {
        std::string str = "FOO";
        to_lowercase(str);
        ASSERT_EQ(str, "foo");
    }

    // Invariant
    {
        std::string str = "foo";
        to_lowercase(str);
        ASSERT_EQ(str, "foo");
    }

    // With non-letter characters
    {
        std::string str = "!_-.,FoO";
        to_lowercase(str);
        ASSERT_EQ(str, "!_-.,foo");
    }

    // Empty
    {
        std::string str = "";
        to_lowercase(str);
        ASSERT_EQ(str, "");
    }
}

/**
 * @brief Test function \c container_to_stream_vector .
 *
 * CASES:
 * - int
 */
TEST(format_utils_tests, container_to_stream_vector)
{
    // int
    {
        std::vector<int> v({1, 30, 500, -7000});
    }
}

/**
 * @brief Test function \c container_to_stream_set .
 */
TEST(format_utils_tests, container_to_stream_set)
{
    // TODO
}

/**
 * @brief Test function \c generic_to_string .
 *
 * CASES:
 * - int
 * - string
 * - formatter
 */
TEST(format_utils_tests, generic_to_string)
{
    // int
    {
        int x = 42;
        std::string result = generic_to_string(x);
        ASSERT_EQ(result, "42");
    }

    // string
    {
        std::string x = "42";
        std::string result = generic_to_string(x);
        ASSERT_EQ(result, "42");
    }

    // formatter
    {
        Formatter x;
        x << "42";
        std::string result = generic_to_string(x);
        ASSERT_EQ(result, "42");
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
