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
 * @file ReturnCode.hpp
 */

#pragma once

#include <cstdint>
#include <map>
#include <string>

#include <fastdds/dds/core/ReturnCode.hpp>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {

/**
 * @brief Return Code enumeration for different method return statements
 *
 * It uses the fastdds ReturnCode_t
 */
class ReturnCode
{
public:

    enum ReturnCodeValue
    {
        OK = 0,
        ERROR = 1,
        UNKNOWN = 2,
        NO_DATA = 3,
        NOT_ENABLED = 4,
        PRECONDITION_NOT_MET = 5,
    };

    CPP_UTILS_DllAPI
    ReturnCode()
        : value_(OK)
    {
    }

    CPP_UTILS_DllAPI
    ReturnCode(
            const fastdds::dds::ReturnCode_t& value);

    CPP_UTILS_DllAPI
    std::uint32_t operator ()() const noexcept;

    CPP_UTILS_DllAPI
    bool operator ==(
            const ReturnCode& c) const noexcept;

    CPP_UTILS_DllAPI
    bool operator !=(
            const ReturnCode& c) const noexcept;

    CPP_UTILS_DllAPI
    bool operator <(
            const ReturnCode& other) const noexcept;

    CPP_UTILS_DllAPI
    bool operator !() const noexcept;

    CPP_UTILS_DllAPI
    explicit operator bool() = delete;

protected:

    //! Link every ReturnCode available with a string to deserialize
    static const std::map<ReturnCode, std::string> to_string_conversion_;

    //! \c ReturnCode value
    std::uint32_t value_;


    // operator << needs access to the object
    CPP_UTILS_DllAPI
    friend std::ostream& operator <<(
            std::ostream& os,
            const ReturnCode& code);

};

//! \c ReturnCode to stream serializator
CPP_UTILS_DllAPI
std::ostream& operator <<(
        std::ostream& os,
        const ReturnCode& code);

} /* namespace utils */
} /* namespace eprosima */
