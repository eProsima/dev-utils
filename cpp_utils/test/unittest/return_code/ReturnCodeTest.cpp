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

#include <algorithm>

#include <cpp_utils/testing/gtest_aux.hpp>
#include <gtest/gtest.h>

#include <cpp_utils/ReturnCode.hpp>

using namespace eprosima::utils;

/**
 * Test \c ReturnCode serializator method
 */
TEST(ReturnCodeTest, serializator)
{
    std::map<ReturnCode, std::string> to_string_conversion =
    {
        {ReturnCode::RETCODE_OK, "{Ok}"},
        {ReturnCode::RETCODE_ERROR, "{Error}"},
        {ReturnCode::RETCODE_UNKNOWN, "{Unknown}"},
        {ReturnCode::RETCODE_NO_DATA, "{NoData}"},
        {ReturnCode::RETCODE_PRECONDITION_NOT_MET, "{PreconditionNotMet}"},
    };

    for (auto it : to_string_conversion)
    {
        std::stringstream ss;
        ss << it.first;
        ASSERT_EQ(ss.str(), it.second);
    }
}

/**
 * Test ReturnCode compares directly against ReturnCodeValue values.
 */
TEST(ReturnCodeTest, compare_against_return_code_value_rhs)
{
    // Right side of the comparation

    ReturnCode from_fastdds(eprosima::fastdds::dds::RETCODE_NO_DATA);

    ASSERT_TRUE(from_fastdds == ReturnCode::RETCODE_NO_DATA);
    ASSERT_FALSE(from_fastdds == ReturnCode::RETCODE_ERROR);
    ASSERT_TRUE(from_fastdds != ReturnCode::RETCODE_ERROR);
}

/**
 * Test ReturnCodeValue compares directly against ReturnCode from lhs.
 */
TEST(ReturnCodeTest, compare_against_return_code_value_lhs)
{
    // Left side of the comparation

    ReturnCode ret(ReturnCode::RETCODE_NOT_ENABLED);

    ASSERT_TRUE(ReturnCode::RETCODE_NOT_ENABLED == ret);
    ASSERT_TRUE(ReturnCode::RETCODE_OK != ret);
    ASSERT_FALSE(ReturnCode::RETCODE_OK == ret);
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
