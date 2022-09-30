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
 * @file TestLogHandler.hpp
 */

#pragma once

#include <memory>

#include <cpp_utils/event/LogSevereEventHandler.hpp>

namespace eprosima {

namespace test {

class TestLogHandler
{
public:

    TestLogHandler(
            utils::Log::Kind threshold = utils::Log::Kind::Warning,
            uint32_t expected_severe_logs = 0,
            uint32_t max_severe_logs = 0);

    ~TestLogHandler();

    void check_valid();

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

} /* namespace test */

} /* namespace eprosima */


