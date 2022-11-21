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
 * @file format_utils.hpp
 *
 * This file contains util functions to format different elements into strings or streams.
 */

#pragma once

#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {
namespace format {

/////
// CONVERSION FUNCTIONS

/**
 * @brief Convert every alphabetic char in string to lower case
 *
 * @attention This function modifies the object given
 *
 * @param [in,out] st : string to modify
 */
CPP_UTILS_DllAPI void convert_to_lowercase(
        std::string& st) noexcept;

/////
// TEMPLATE FUNCTIONS FOR CONTAINERS

/**
 * @brief Concatenate serialization of elements in a vector separated by \c separator .
 *
 * @tparam C type of container, as container<T>. T This object must have an << operator
 *
 * @param os stream to store the concatenation result
 * @param container vector of elements
 * @param separator char or string separator between elements
 *
 * @return stream object with the concatenation of \c os and \c element
 */
template <typename C>
std::ostream& container_to_stream(
        std::ostream& os,
        const C& container,
        const std::string& separator = ";");

//! Return a string serialization of \c element by using \c T::operator<< .
template <typename T>
std::string generic_to_string(
        const T& element) noexcept;

} /* namespace format */
} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/format/impl/format_utils.ipp>
