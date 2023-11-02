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
 *
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
 *
 * @return Returns the name with the prefix added "prefixname"
 */
CPP_UTILS_DllAPI
std::string add_prefix(
        const std::string& name,
        const std::string& prefix);

/**
 * @param[in] name string to be suffixed with "suffix"
 * @param[in] suffix suffix to be added
 *
 * @return Returns the name with the suffix added "namesuffix"
 */
CPP_UTILS_DllAPI
std::string add_suffix(
        const std::string& name,
        const std::string& suffix);

/**
 * @param[in] topic_name The name of the topic to be processed.
 *
 * @return Returns the ROS specific prefix if present, otherwise "".
 */
CPP_UTILS_DllAPI
std::string get_ros_prefix_if_exists(
        const std::string& topic_name);

/**
 * @brief Remove the ROS specific prefix from the \c topic_name if it exists.
 *
 * @param[in] topic_name The name of the topic to be processed.
 *
 * @return Returns the topic name stripped of a ROS specific prefix if present.
 */
CPP_UTILS_DllAPI
std::string remove_ros_prefix_if_exists(
        const std::string& topic_name);

/**
 * @brief Add the ROS Topic prefix in the \c topic_name.
 *
 * @param[in] topic_name The name of the topic to be processed.
 *
 * @return Returns the topic name with the ROS Topic prefix.
 */
CPP_UTILS_DllAPI
std::string add_ros_topic_prefix(
        const std::string& topic_name);

/**
 * @brief Add the ROS Service Requester prefix in the \c topic_name.
 *
 * @param[in] topic_name The name of the topic to be processed.
 *
 * @return Returns the topic name with the ROS Requester prefix.
 */
CPP_UTILS_DllAPI
std::string add_ros_service_requester_prefix(
        const std::string& topic_name);

/**
 * @brief Add the ROS Service Response prefix in the \c topic_name.
 *
 * @param[in] topic_name The name of the topic to be processed.
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
 * @brief Obtain the ROS topic associated with the provided \c topic_name,
 * excluding the ROS prefix.
 *
 * If the topic_name begins with a ROS prefix (i.e., starts with ROS prefix + "/").
 * If the input topic name does not contain a ROS prefix + "/", it is returned unchanged.
 *
 * @param[in] topic_name The name of the topic to be processed.
 *
 * @return Returns the demangle ROS topic or the original if not a ROS topic.
 */
CPP_UTILS_DllAPI
std::string demangle_if_ros_topic(
        const std::string& topic_name);

/**
 * @brief Mangle a given \c topic_name if it starts with "/".
 *
 * If the topic name begins with "/", it adds the ROS topic prefix to the \c topic_name and then returns it.
 * If the topic name does not start with "/", it is returned unchanged.
 *
 * @param[in] topic_name The name of the topic to be processed.
 *
 * @return Returns the mangle ROS topic or the original if not a ROS topic (start with "/").
 */
CPP_UTILS_DllAPI
std::string mangle_if_ros_topic(
        const std::string& topic_name);

/**
 * @brief Demangle a DDS type string if it is a ROS type.
 *
 * This function takes a DDS type string as input and checks if it represents a ROS type.
 * If the input type string is not a ROS type, it is returned unchanged.
 * If the input type string is a ROS type, it demangles the type string by converting DDS-specific namespace
 * separators ("::") to "/", removing "dds" and returns the demangled result.
 *
 * @param[in] dds_type_string DDS type string to be processed.
 *
 * @return The demangled ROS type string or the original input if it is not a ROS type.
 */
CPP_UTILS_DllAPI
std::string demangle_if_ros_type(
        const std::string& dds_type_string);

/**
 * @brief Mangle a ROS 2 type string into a DDS type string.
 *
 * This function takes a ROS 2 type string as input and mangles it into a DDS type string.
 * If the input string does not contain a ROS 2-specific substring, it is returned unchanged.
 * If the ROS 2 substring is found, this function extracts the type namespace and type name,
 * converts namespace separators from "/" to "::", and adds the "dds_::" prefix and a trailing
 * underscore to the type name.
 *
 * @param[in] ros2_type_string The input ROS 2 type string to be mangled.
 *
 * @return The mangled DDS type string or the original input if it does not contain the ROS 2 substring.
 */
CPP_UTILS_DllAPI
std::string mangle_if_ros_type(
        const std::string& ros2_type_string);

/**
 * @brief Demangle a ROS topic name by removing the ROS topic prefix.
 *
 * This function takes a ROS topic name as input and removes the ROS topic prefix if it exists.
 *
 * @param[in] topic_name The input ROS topic name to be processed.
 *
 * @return The demangled ROS topic name with the ROS topic prefix removed, or "" if the prefix is not present.
 */
CPP_UTILS_DllAPI
std::string demangle_ros_topic_prefix_from_topic(
        const std::string& topic_name);

/**
 * @brief Demangle a ROS service topic name by identifying its type and extracting the appropriate service name.
 *
 * This function takes a ROS service topic name as input and attempts to demangle it by identifying its type
 * (whether it's a reply or request service topic).
 * If neither function successfully demangles the input, an empty string is returned.
 *
 * @param[in] topic_name The input ROS service topic name to be processed.
 *
 * @return The demangled service name if successfully extracted, or an empty string if demangling fails.
 */
CPP_UTILS_DllAPI
std::string demangle_ros_service_prefix_from_topic(
        const std::string& topic_name);
/**
 * @brief Demangle a ROS service request topic name by removing the requester prefix.
 *
 * This function takes a ROS service request topic name as input and removes the specified requester prefix and the common "Request" suffix.
 * If the input topic name does not contain both the requester prefix
 * and the "Request" suffix, an empty string is returned.
 *
 * @param[in] topic_name The input ROS service request topic name to be processed.
 *
 * @return The demangled service name with the requester prefix and "Request" suffix removed, or an empty string
 * if the necessary prefixes and suffixes are not present.
 */
CPP_UTILS_DllAPI
std::string demangle_ros_service_request_prefix_from_topic(
        const std::string& topic_name);

/**
 * @brief Mangle a ROS service request topic name by adding the requester prefix and "Request" suffix.
 *
 * This function takes a ROS service request topic name as input and mangles it by adding the specified
 * requester prefix and the common "Request" suffix. If the input topic name starts with "/", indicating
 * it is part of a service request, the mangled service name is returned. Otherwise, an empty string is returned.
 *
 * @param[in] topic_name The input ROS service request topic name to be processed.
 *
 * @return The mangled service name with the requester prefix and "Request" suffix added if
 * it is part of a service request (start with "/"), otherwise an empty string ("").
 */
CPP_UTILS_DllAPI
std::string mangle_ros_service_request_prefix_in_topic(
        const std::string& topic_name);

/**
 * @brief Demangle a ROS service reply topic name by removing the response prefix and "Reply" suffix.
 *
 * This function takes a ROS service reply topic name as input and demangles it by removing the specified
 * response prefix and the common "Reply" suffix.
 * If the input topic name does not contain both the response prefix and the "Reply" suffix, an empty string is returned.
 *
 * @param[in] topic_name The input ROS service reply topic name to be processed.
 *
 * @return The demangled service name with the response prefix and "Reply" suffix removed, or an empty string
 * if the necessary prefixes and suffixes are not present.
 */
CPP_UTILS_DllAPI
std::string demangle_ros_service_reply_prefix_from_topic(
        const std::string& topic_name);

/**
 * @brief Mangle a ROS service reply topic name by adding the response prefix and "Reply" suffix.
 *
 * This function takes a ROS service reply topic name as input and mangles it by adding the specified
 * response prefix and the common "Reply" suffix. If the input topic name does not start with "/", indicating
 * it is part of a service response, an empty string is returned.
 *
 * @param[in] topic_name The input ROS service reply topic name to be processed.
 *
 * @return The mangled service name with the response prefix and "Reply" suffix added if it is part of
 * a service response (starts with "/"), otherwise an empty string ("").
 */
CPP_UTILS_DllAPI
std::string mangle_ros_service_reply_prefix_in_topic(
        const std::string& topic_name);

/**
 * @brief Demangle a ROS service type name to extract the core type in ROS 2 format.
 *
 * This function takes a ROS service type name in DDS format as input and demangles it to the ROS 2 format,
 * extracting the core type. If the input type name does not match the expected ROS service type format,
 * an empty string is returned.
 *
 * @param[in] dds_type_name The input ROS service type name in DDS format to be processed.
 *
 * @return The demangled core service type name in ROS 2 format, or an empty string if the input
 * does not conform to the expected format.
 */
CPP_UTILS_DllAPI
std::string demangle_service_type_only(
        const std::string& dds_type_name);

/**
 * @brief Mangle a ROS 2 service type name to DDS format.
 *
 * This function takes a ROS 2 service type name as input and mangles it to DDS format by adding necessary
 * prefixes and separators. It identifies whether it's a service request or response type and handles the
 * conversion accordingly. If the input type name is not in the expected ROS 2 service type format, an empty
 * string is returned.
 *
 * @param[in] ros2_type_name The input ROS 2 service type name to be processed.
 *
 * @return The mangled ROS 2 service type name in DDS format, or an empty string if the input does not
 * conform to the expected format.
 */
CPP_UTILS_DllAPI
std::string mangle_service_type_only(
        const std::string& ros2_type_name);

} /* namespace utils */
} /* namespace eprosima */
