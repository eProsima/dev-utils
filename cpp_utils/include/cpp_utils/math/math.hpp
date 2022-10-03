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
 * @file math.hpp
 *
 * This file contains math generic functions
 */

#pragma once

#include <stdint.h>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

/**
 * @brief Module (%) operation with performance optimization
 *
 * This function optimizes the % operation, that executes a division, by optimizing these cases:
 * - If the dividend is smaller or equal than the divisor, the result is the dividend
 * - If the divisor is 2, the result is the dividend % 2 calculated by a logic AND operation
 * - If the divisor is a power of 2, the result is calculated by a logic AND operation
 *
 * @param dividend Dividend
 * @param divisor Divisor (must be greater than 0 so the operation make sense)
 *
 * @attention if divisor is 0, the result is \c dividend
 *
 * @return The result of the operation
 */
CPP_UTILS_DllAPI uint32_t fast_module(
        uint32_t dividend,
        uint32_t divisor) noexcept;

} /* namespace utils */
} /* namespace eprosima */


