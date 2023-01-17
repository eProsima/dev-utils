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

/**
 * @file time_utils.hpp
 */

#pragma once

#include <chrono>
#include <string>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

//! Type of Duration in milliseconds
using Duration_ms = uint32_t;

/**
 * Type used to represent time points
 */
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;

/**
 * @brief Now time
 *
 * @return Timestamp refering to the moment it is called
 */
CPP_UTILS_DllAPI Timestamp now() noexcept;

//! Returns the maximum time available for \c Timestamp
CPP_UTILS_DllAPI Timestamp the_end_of_times() noexcept;

CPP_UTILS_DllAPI std::string to_string(
        const Timestamp& timestamp,
        const std::string& format = "%Z_%Y-%m-%d_%H-%M-%S");

CPP_UTILS_DllAPI std::chrono::milliseconds duration_to_ms(
        const Duration_ms& duration) noexcept;

CPP_UTILS_DllAPI void sleep_for(
        const Duration_ms& sleep_time) noexcept;

} /* namespace utils */
} /* namespace eprosima */
