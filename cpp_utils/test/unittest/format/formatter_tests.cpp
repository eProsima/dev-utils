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

#include <cpp_utils/exception/Exception.hpp>
#include <cpp_utils/format/Formatter.hpp>

using namespace eprosima::utils::format;

/**
 * Test \c Formatter object use.
 *
 * STEPS:
 * - create Formatter
 * - add text
 * - check text inside
 * - add text from string
 * - check text inside is concatenated
 * - create other Formatter
 * - add text from int
 * - concatenate
 * - check text inside is concatenated from both
 */
TEST(formatter_tests, object_use)
{
    // create Formatter
    Formatter formatter;

    // add text
    formatter << "Some text";

    // check text inside
    ASSERT_EQ(formatter.to_string(), "Some text");

    // add text from string
    std::string aux_str(" other text ");
    formatter << aux_str;

    // check text inside is concatenated
    ASSERT_EQ(formatter.to_string(), "Some text other text ");

    // create other Formatter
    Formatter formatter_2;

    // add text from int
    formatter_2 << 42;

    // concatenate
    formatter << formatter_2;

    // check text inside is concatenated from both
    ASSERT_EQ(formatter.to_string(), "Some text other text 42");
}

/**
 * Test \c Formatter cast to string method.
 *
 * CASES:
 * - empty string
 * - some string
 */
TEST(formatter_tests, cast_string)
{
    // empty string
    {
        Formatter formatter;
        std::string str = formatter;
        ASSERT_TRUE(str.empty());
    }

    // some string
    {
        Formatter formatter;
        formatter << "Some text";
        std::string str = formatter;
        ASSERT_EQ(str, "Some text");
    }
}

/**
 * Test \c Formatter::to_string method.
 *
 * CASES:
 * - empty string
 * - some string
 */
TEST(formatter_tests, to_string)
{
    // empty string
    {
        Formatter formatter;
        ASSERT_TRUE(formatter.to_string().empty());
    }

    // some string
    {
        Formatter formatter;
        formatter << "Some text";
        std::string str = formatter.to_string();
        ASSERT_EQ(str, "Some text");
    }
}

/**
 * Test \c Formatter:: serialization operator.
 *
 * CASES:
 * - empty string
 * - some string
 */
TEST(formatter_tests, serialization_operator_string)
{
    // empty string
    {
        Formatter formatter;
        std::stringstream ss;
        ss << formatter;
        ASSERT_TRUE(ss.str().empty());
    }

    // some string
    {
        Formatter formatter;
        formatter << "Some text";
        std::stringstream ss;
        ss << formatter;
        ASSERT_EQ(ss.str(), "Some text");
    }
}

/**
 * Test \c Formatter use in exception.
 */
TEST(formatter_tests, use_in_exception)
{
    bool exception_occured = false;
    try
    {
        throw eprosima::utils::Exception(STR_ENTRY << "Some text " << 42);
    }
    catch(const std::exception& e)
    {
        exception_occured = true;
        ASSERT_EQ(strcmp(e.what(), "Some text 42"), 0);
    }
    ASSERT_TRUE(exception_occured);
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
