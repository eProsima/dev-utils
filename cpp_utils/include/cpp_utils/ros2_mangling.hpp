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

#include <string>
#include <vector>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

/**
 * @param[in] name string that will be stripped from prefix
 * @param[in] prefix prefix to be stripped
 * @return name stripped of prefix, or
 * @return "" if name doesn't start with prefix
 */
CPP_UTILS_DllAPI
std::string remove_prefix(
        const std::string& name,
        const std::string& prefix);

/**
 * @param[in] name string to be prefixed with "prefix"
 * @param[in] prefix prefix to be added
 * @return Returns the name with the prefix added "prefixname"
 */
CPP_UTILS_DllAPI
std::string add_prefix(
        const std::string& name,
        const std::string& prefix);

/**
 * @param[in] name string to be suffixed with "suffix"
 * @param[in] suffix suffix to be added
 * @return Returns the name with the suffix added "namesuffix"
 */
CPP_UTILS_DllAPI
std::string add_suffix(
        const std::string& name,
        const std::string& suffix);

/**
 * @param[in] topic_name name of the topic
 * @return Returns the ROS specific prefix if present, otherwise "".
 */
CPP_UTILS_DllAPI
std::string get_ros_prefix_if_exists(
        const std::string& topic_name);

/**
 * @brief Remove the ROS specific prefix from the \c topic_name if it exists.
 * @param[in] topic_name name of the topic
 *
 * @return Returns the topic name stripped of a ROS specific prefix if present.
 */
CPP_UTILS_DllAPI
std::string remove_ros_prefix_if_exists(
        const std::string& topic_name);

/**
 * @brief Add the ROS Topic prefix in the \c topic_name.
 * @param[in] topic_name name of the topic
 *
 * @return Returns the topic name with the ROS Topic prefix.
 */
CPP_UTILS_DllAPI
std::string add_ros_topic_prefix(
        const std::string& topic_name);

/**
 * @brief Add the ROS Service Requester prefix in the \c topic_name.
 * @param[in] topic_name name of the topic
 *
 * @return Returns the topic name with the ROS Requester prefix.
 */
CPP_UTILS_DllAPI
std::string add_ros_service_requester_prefix(
        const std::string& topic_name);

/**
 * @brief Add the ROS Service Response prefix in the \c topic_name.
 * @param[in] topic_name name of the topic
 *
 * @return Returns the topic name with the ROS Response prefix.
 */
CPP_UTILS_DllAPI
std::string add_ros_service_response_prefix(
        const std::string& topic_name);

/**
 * @return Returns \c ros_prefixes_.
 */
CPP_UTILS_DllAPI
const std::vector<std::string>& get_all_ros_prefixes();

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the demangle ROS topic or the original if not a ROS topic.
 */
CPP_UTILS_DllAPI
std::string demangle_if_ros_topic(
        const std::string& topic_name);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the mangle ROS topic or the original if not a ROS topic (start with "/").
 */
CPP_UTILS_DllAPI
std::string mangle_if_ros_topic(
        const std::string& topic_name);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the demangled ROS type or the original if not a ROS type.
 */
CPP_UTILS_DllAPI
std::string demangle_if_ros_type(
        const std::string& dds_type_string);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the DDS type or the original if not a ROS type.
 */
CPP_UTILS_DllAPI
std::string mangle_if_ros_type(
        const std::string& ros2_type_string);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the topic name for a given topic if it is part of a ROS topic, otherwise "".
 */
CPP_UTILS_DllAPI
std::string demangle_ros_topic_prefix_from_topic(
        const std::string& topic_name);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the service name for a given topic if it is part of a ROS service, otherwise "".
 */
CPP_UTILS_DllAPI
std::string demangle_ros_service_prefix_from_topic(
        const std::string& topic_name);
/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the service name for a given topic if it is part of a ROS service request, otherwise "".
 */
CPP_UTILS_DllAPI
std::string demangle_ros_service_request_prefix_from_topic(
        const std::string& topic_name);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the service name for a given topic with the ros service requester prefix
 * if it is part of a service request (start with "/"), otherwise "".
 */
CPP_UTILS_DllAPI
std::string mangle_ros_service_request_prefix_in_topic(
        const std::string& topic_name);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the service name for a given topic if it is part of a service response, otherwise "".
 */
CPP_UTILS_DllAPI
std::string demangle_ros_service_reply_prefix_from_topic(
        const std::string& topic_name);

/**
 * @param[in] topic_name name of the topic
 *
 * @return Returns the service name for a given topic with the ros service response prefix if
 * it is part of a service response (start with "/"), otherwise "".
 */
CPP_UTILS_DllAPI
std::string mangle_ros_service_reply_prefix_in_topic(
        const std::string& topic_name);

/**
 * @param[in] dds_type_name name of the topic
 *
 * @return Returns the demangled service type if it is an DDS srv type, otherwise "".
 */
CPP_UTILS_DllAPI
std::string demangle_service_type_only(
        const std::string& dds_type_name);

/**
 * @param[in] ros2_type_name name of the topic
 *
 * @return Returns the mangled service type if it is an ROS srv type, otherwise "".
 */
CPP_UTILS_DllAPI
std::string mangle_service_type_only(
        const std::string& ros2_type_name);

} /* namespace utils */
} /* namespace eprosima */
