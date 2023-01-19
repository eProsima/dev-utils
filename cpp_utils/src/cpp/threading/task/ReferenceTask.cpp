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
 * @file ReferenceTask.cpp
 *
 */

#include <cpp_utils/exception/InitializationException.hpp>
#include <cpp_utils/threading/task/ReferenceTask.hpp>

namespace eprosima {
namespace utils {
namespace threading {

ReferenceTask::ReferenceTask(const std::function<void()>* callback_ptr)
    : callback_ptr(callback_ptr)
{
    if (!callback_ptr)
    {
        throw InitializationException(STR_ENTRY << "ReferenceTask must be initialized with a valid ptr.");
    }
}

void ReferenceTask::operator()() noexcept
{
    callback_ptr->operator()();
}

} /* namespace threading */
} /* namespace utils */
} /* namespace eprosima */
