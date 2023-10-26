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

namespace eprosima {
namespace utils {

/**
 * @param[in] name string that will be stripped from prefix
 * @param[in] prefix prefix to be stripped
 * @return name stripped of prefix, or
 * @return "" if name doesn't start with prefix
 */
std::string remove_prefix(
        const std::string& name,
        const std::string& prefix);

/**
 * @param[in] name string to be prefixed with "prefix"
 * @param[in] prefix prefix to be added
 * @return Returns the name with the prefix added "prefixname"
 */
std::string add_prefix(
        const std::string& name,
        const std::string& prefix);

/**
 * @todo
 */
std::string add_suffix(
        const std::string& name,
        const std::string& suffix);

/**
 * @return Returns the ROS specific prefix if present, otherwise "".
 */
std::string get_ros_prefix_if_exists(
        const std::string& topic_name);

/**
 * @brief Remove the ROS specific prefix from the topic name if it exists.
 *
 * @return Returns the topic name stripped of a ROS specific prefix if present.
 */
std::string remove_ros_prefix_if_exists(
        const std::string& topic_name);

/**
 * @todo
 */
std::string add_ros_topic_prefix(
        const std::string& topic_name);

/**
 * @todo
 */
std::string add_ros_service_requester_prefix(
        const std::string& topic_name);

/**
 * @todo
 */
std::string add_ros_service_response_prefix(
        const std::string& topic_name);

/**
 * @return Returns \c ros_prefixes_.
 */
const std::vector<std::string>& get_all_ros_prefixes();

/**
 * @return Returns the demangle ROS topic or the original if not a ROS topic.
 */
std::string demangle_if_ros_topic(
        const std::string& topic_name);

/**
 * @todo
 */
std::string mangle_if_ros_topic(
        const std::string& topic_name);

/**
 * @return Returns the demangled ROS type or the original if not a ROS type.
 */
std::string demangle_if_ros_type(
        const std::string& dds_type_string);

/**
 * @todo
 */
std::string mangle_if_ros_type(
        const std::string& ros2_type_string);

/**
 * @return Returns the topic name for a given topic if it is part of a ROS topic, otherwise "".
 */
std::string demangle_ros_topic_prefix_from_topic(
        const std::string& topic_name);

/**
 * @return Returns the service name for a given topic if it is part of a ROS service, otherwise "".
 */
std::string demangle_ros_service_prefix_from_topic(
        const std::string& topic_name);
/**
 * @return Returns the service name for a given topic if it is part of a ROS service request, otherwise "".
 */
std::string demangle_ros_service_request_prefix_from_topic(
        const std::string& topic_name);

/**
 * @todo
 */
std::string mangle_ros_service_request_prefix_in_topic(
        const std::string& topic_name);

/**
 * @return Returns the service name for a given topic if it is part of a service response, otherwise "".
 */
std::string demangle_ros_service_reply_prefix_from_topic(
        const std::string& topic_name);

/**
 * @todo
 */
std::string mangle_ros_service_reply_prefix_in_topic(
        const std::string& topic_name);

/**
 * @return Returns the demangled service type if it is an ROS srv type, otherwise "".
 */
std::string demangle_service_type_only(
        const std::string& dds_type_name);

/**
 * @todo
 */
std::string mangle_service_type_only(
        const std::string& ros2_type_name);

} /* namespace utils */
} /* namespace eprosima */
