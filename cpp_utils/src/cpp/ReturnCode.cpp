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
 * @file ReturnCode.cpp
 *
 */

#include <cassert>
#include <map>
#include <string>
#include <iostream>

#include <cpp_utils/ReturnCode.hpp>

namespace eprosima {
namespace utils {

ReturnCode::ReturnCode(
        const fastdds::dds::ReturnCode_t& value)
{
    switch (value)
    {
        case fastdds::dds::RETCODE_OK:
            value_ = ReturnCode::OK;
            break;
        case fastdds::dds::RETCODE_ERROR:
        case fastdds::dds::RETCODE_UNSUPPORTED:
        case fastdds::dds::RETCODE_BAD_PARAMETER:
        case fastdds::dds::RETCODE_OUT_OF_RESOURCES:
        case fastdds::dds::RETCODE_IMMUTABLE_POLICY:
        case fastdds::dds::RETCODE_INCONSISTENT_POLICY:
        case fastdds::dds::RETCODE_ALREADY_DELETED:
        case fastdds::dds::RETCODE_TIMEOUT:
        case fastdds::dds::RETCODE_ILLEGAL_OPERATION:
            value_ = ReturnCode::ERROR;
            break;
        case fastdds::dds::RETCODE_NO_DATA:
            value_ = ReturnCode::NO_DATA;
            break;
        case fastdds::dds::RETCODE_NOT_ENABLED:
            value_ = ReturnCode::NOT_ENABLED;
            break;
        case fastdds::dds::RETCODE_PRECONDITION_NOT_MET:
            value_ = ReturnCode::PRECONDITION_NOT_MET;
            break;
        default:
            value_ = ReturnCode::UNKNOWN;
            break;
    }
}

std::uint32_t ReturnCode::operator ()() const noexcept
{
    return value_;
}

bool ReturnCode::operator ==(
        const ReturnCode& c) const noexcept
{
    return value_ == c.value_;
}

bool ReturnCode::operator !=(
        const ReturnCode& c) const noexcept
{
    return value_ != c.value_;
}

bool ReturnCode::operator <(
        const ReturnCode& other) const noexcept
{
    return (*this)() < other();
}

bool ReturnCode::operator !() const noexcept
{
    return value_ != ReturnCode::OK;
}

const std::map<ReturnCode, std::string> ReturnCode::to_string_conversion_ =
{
    {ReturnCode::OK, "Ok"},
    {ReturnCode::ERROR, "Error"},
    {ReturnCode::UNKNOWN, "Unknown"},
    {ReturnCode::NO_DATA, "NoData"},
    {ReturnCode::PRECONDITION_NOT_MET, "PreconditionNotMet"},
};

std::ostream& operator <<(
        std::ostream& os,
        const ReturnCode& code)
{
    auto it = ReturnCode::to_string_conversion_.find(code);
    assert(it != ReturnCode::to_string_conversion_.end());
    os << "{" << it->second << "}";
    return os;
}

} /* namespace utils */
} /* namespace eprosima */
