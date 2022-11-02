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
 * @file LogEventHandler.hpp
 */

#pragma once

#include <atomic>
#include <functional>

#include <cpp_utils/Log.hpp>
#include <cpp_utils/types/Atomicable.hpp>
#include <cpp_utils/event/EventHandler.hpp>
#include <cpp_utils/memory/owner_ptr.hpp>
#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {
namespace event {

using LogConsumerConnectionCallbackType = std::function<void(const utils::Log::Entry&)>;

/**
 * It implements the functionality to raise callback every time a Log msg is consumed.
 *
 * @warning Fast DDS Log takes the ownership of the pointer of every new consumer (because of reasons...)
 * Thus, in order to create this kind of handler, it must be created from a pointer (new) and the ownership
 * of the pointer will be lost as soon as it is created.
 */
class LogEventHandler : public EventHandler<utils::Log::Entry>
{
public:

    // This class does not have constructor without callback.
    // This is because of the lost of the pointer once it is registered in Fast. This makes it simpler.

    CPP_UTILS_DllAPI LogEventHandler();

    /**
     * Construct a Log Event Handler with callback and enable it.
     *
     * Calls \c set_callback
     *
     * @param callback callback to call every time a log entry is consumed.
     */
    CPP_UTILS_DllAPI LogEventHandler(
            std::function<void(utils::Log::Entry)> callback);

    /**
     * @brief Destroy the LogEventHandler object
     *
     * Calls \c unset_callback
     */
    CPP_UTILS_DllAPI ~LogEventHandler();

protected:

    CPP_UTILS_DllAPI virtual void consume_(
            const utils::Log::Entry& entry);

    //! TODO
    OwnerPtr<LogConsumerConnectionCallbackType> connection_callback_;

    /**
     * @brief  Vector of Log entries consumed so far.
     *
     * Guarded by \c entries_mutex_ .
     */
    SharedAtomicable<std::vector<utils::Log::Entry>> entries_consumed_;
};

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */
