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
 * @file LogChecker.hpp
 */

#pragma once

#include <memory>
#include <functional>

#include <cpp_utils/event/LogSevereEventHandler.hpp>

namespace eprosima {
namespace utils {
namespace testing {

class LogChecker
{
public:

    CPP_UTILS_DllAPI LogChecker(
            utils::Log::Kind threshold = utils::Log::Kind::Warning,
            uint32_t expected_severe_logs = 0,
            uint32_t max_severe_logs = 0);

    CPP_UTILS_DllAPI ~LogChecker();

    CPP_UTILS_DllAPI bool check_valid();

protected:

    /**
     * @brief Pointer to the event handler log consumer
     *
     * @attention: this must be a raw pointer as Fast takes ownership of the consumer.
     */
    utils::event::LogSevereEventHandler* log_consumer_;

    uint32_t expected_severe_logs_;
    uint32_t max_severe_logs_;
};

/**
 * @brief Instantiate a LogChecker instance that assert that logs has been as expected when runs out of scope.
 *
 * This is an easy way to instantiate a LogChecker by using a unique ptr that autodestroys when exit the scope,
 * and in deletion it is checked that logs has been correct regarding the parameters, and ASSERT if not.
 *
 * @note this is just to avoid the user to write this code. It is needed because ASSERT_TRUE require gtest
 * to be installed and linked, and this could always not be the case.
 *
 * @example
 * TEST(FooTest, test_foo) {
 *   INSTANTIATE_LOG_TESTER(eprosima::utils::Log::Kind::Warning, 0, 0);
 *   // When test finishes, if any log warning has been raised, test will fail.
 * }
 */
#define INSTANTIATE_LOG_TESTER(threshold, expected, max) \
    std::unique_ptr< \
        eprosima::utils::testing::LogChecker, \
        std::function<void(eprosima::utils::testing::LogChecker*)>> \
    log_tester( \
        new eprosima::utils::testing::LogChecker(threshold, expected, max), \
        [](eprosima::utils::testing::LogChecker* t){ ASSERT_TRUE( t->check_valid()); delete t; \
        })

/**
 * This macro only calls \c INSTANTIATE_LOG_TESTER with parameters by default.
 * All positive tests cases should be able to run with this call (one day...).
 */
#define DEFAULT_LOG_TESTER INSTANTIATE_LOG_TESTER(eprosima::utils::Log::Kind::Warning, 0, 0)

} /* namespace testing */
} /* namespace utils */
} /* namespace eprosima */
