// Copyright 2024 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file qos_utils.hpp
 */

#pragma once

#include <string>

#include <fastdds/dds/core/policy/QosPolicies.hpp>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

/**
 * @brief Converts a \c QosPolicyId_t to a string.
 *
 * @param qos_policy_id The \c QosPolicyId_t to convert.
 * @return The string representation of the \c QosPolicyId_t.
 */
CPP_UTILS_DllAPI std::string qos_policy_id_to_string(
        const fastdds::dds::QosPolicyId_t& qos_policy_id);

/**
 * @brief Converts a \c PolicyMask to a string.
 *
 * @param qos_policy_mask The \c PolicyMask to convert.
 * @return The string representation of the \c PolicyMask.
 */
CPP_UTILS_DllAPI std::string qos_policy_mask_to_string(
        const fastdds::dds::PolicyMask& qos_policy_mask);

} /* namespace utils */
} /* namespace eprosima */
