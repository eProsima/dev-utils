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
        {ReturnCode::OK, "{Ok}"},
        {ReturnCode::ERROR, "{Error}"},
        {ReturnCode::UNKNOWN, "{Unknown}"},
        {ReturnCode::NO_DATA, "{NoData}"},
        {ReturnCode::PRECONDITION_NOT_MET, "{PreconditionNotMet}"},
    };

    for (auto it : to_string_conversion)
    {
        std::stringstream ss;
        ss << it.first;
        ASSERT_EQ(ss.str(), it.second);
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
