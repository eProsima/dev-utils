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
 * @brief Test function \c convert_to_lowercase .
 *
 * CASES:
 * - Uppercase
 * - Invariant
 * - With non-letter characters
 * - Empty
 */
TEST(format_utils_tests, convert_to_lowercase)
{
    // Uppercase
    {
        std::string str = "FOO";
        convert_to_lowercase(str);
        ASSERT_EQ(str, "foo");
    }

    // Invariant
    {
        std::string str = "foo";
        convert_to_lowercase(str);
        ASSERT_EQ(str, "foo");
    }

    // With non-letter characters
    {
        std::string str = "!_-.,FoO";
        convert_to_lowercase(str);
        ASSERT_EQ(str, "!_-.,foo");
    }

    // Empty
    {
        std::string str = "";
        convert_to_lowercase(str);
        ASSERT_EQ(str, "");
    }
}

/**
 * @brief Test function \c container_to_stream .
 *
 * CASES:
 * - vector
 *   - int
 *   - std::string
 * - set (could be different order)
 *   - int
 *   - std::string
 * - different separator
 */
TEST(format_utils_tests, container_to_stream)
{
    // vector
    {
        // int
        {
            std::vector<int> container({1, 30, 500, -7000});
            std::stringstream ss;
            eprosima::utils::format::container_to_stream(ss, container);
            ASSERT_EQ(ss.str(), "1;30;500;-7000");
        }

        // std::string
        {
            std::vector<std::string> container({"my", "1", "_THEN_;"});
            std::stringstream ss;
            eprosima::utils::format::container_to_stream(ss, container);
            ASSERT_EQ(ss.str(), "my;1;_THEN_;");
        }
    }

    // set
    {
        // int
        {
            std::set<int> container({30, 1, 500, -7000});
            std::stringstream ss;
            eprosima::utils::format::container_to_stream(ss, container);
            std::string result = ss.str();

            // Check that every number exists and has a ; before or after
            for (const auto& x : container)
            {
                std::string this_value_str = eprosima::utils::format::generic_to_string(x);
                auto res = result.find(this_value_str);
                ASSERT_NE(res, std::string::npos);

                if (res != 0)
                {
                    ASSERT_EQ(result[res - 1], ';');
                }

                if (res + this_value_str.size() < result.size())
                {
                    ASSERT_EQ(result[res + this_value_str.size()], ';');
                }
            }
        }

        // string
        {
            std::vector<std::string> container({"my", "1", "_THEN_;"});
            std::stringstream ss;
            eprosima::utils::format::container_to_stream(ss, container);
            std::string result = ss.str();

            // Check that every number exists and has a ; before or after
            for (const auto& x : container)
            {
                auto res = result.find(x);
                ASSERT_NE(res, std::string::npos);

                if (res != 0)
                {
                    ASSERT_EQ(result[res - 1], ';');
                }

                if (res + x.size() < result.size())
                {
                    ASSERT_EQ(result[res + x.size()], ';');
                }
            }
        }
    }

    // different separator
    {
        std::vector<char> container({'_', '=', '_'});
        std::stringstream ss;
        eprosima::utils::format::container_to_stream(ss, container, "(*)");
        ASSERT_EQ(ss.str(), "_(*)=(*)_");
    }
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
        std::string x = "42_";
        std::string result = generic_to_string(x);
        ASSERT_EQ(result, "42_");
    }

    // formatter
    {
        Formatter x;
        x << "my42";
        std::string result = generic_to_string(x);
        ASSERT_EQ(result, "my42");
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
