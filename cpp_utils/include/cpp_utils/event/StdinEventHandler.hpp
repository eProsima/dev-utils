// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#pragma once

#include <atomic>
#include <functional>
#include <thread>

#include <cpp_utils/wait/CounterWaitHandler.hpp>
#include <cpp_utils/time/time_utils.hpp>
#include <cpp_utils/event/EventHandler.hpp>
#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {
namespace event {

/**
 * TODO
 */
class StdinEventHandler : public EventHandler<std::string>
{
public:

    /**
     * @brief Construct a new Periodic Event Handler with specific callback
     *
     * @param callback : callback to call when stdin_listener time comes
     * @param stdin_listener_time : stdin_listener time in milliseconds for Event to occur. Must be greater than 0.
     *
     * @throw \c InitializationException in case \c stdin_listener_time is lower than minimum time stdin_listener (1ms).
     */
    CPP_UTILS_DllAPI StdinEventHandler(
            std::function<void(std::string)> callback,
            const bool read_lines = true,
            const int lines_to_read = 0,
            std::istream& source = std::cin);

    /**
     * @brief Destroy the StdinEventHandler object
     *
     * Calls \c unset_callback
     */
    CPP_UTILS_DllAPI ~StdinEventHandler();

    CPP_UTILS_DllAPI void read_one_more_line();

protected:

    /**
     * @brief Internal thread to wait for stdin_listener and call callback
     *
     * @warning callback is called from this method, so until the
     * callback does not finish, the time will not restart again.
     */
    void stdin_listener_thread_routine_() noexcept;

    /**
     * @brief Override \c callback_set_ from \c EventHandler .
     *
     * It starts filewatcher if it has not been started.
     *
     * It is already guarded by \c event_mutex_ .
     */
    virtual void callback_set_nts_() noexcept override;

    /**
     * @brief Override \c callback_set_ from \c EventHandler .
     *
     * It stops filewatcher if it has been started.
     *
     * It is already guarded by \c event_mutex_ .
     */
    virtual void callback_unset_nts_() noexcept override;

    //! Period thread
    std::thread stdin_listener_thread_;

    CounterWaitHandler activation_times_;

    std::istream& source_;

    const bool read_lines_;
};

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */
