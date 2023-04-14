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

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {
namespace testing {

/**
 * TODO remove
 */
class TmpApi
{
public:

    CPP_UTILS_DllAPI
    // This should fail in windows due to not linkage (0x000c35)
    TmpApi ();

};

/**
 * TODO remove
 */
class TmpApi2
{
public:

    // This should not fail
    CPP_UTILS_DllAPI
    TmpApi2 ();

};

template <typename T>
void print_something(
        const T& value);

// This should fail
template <>
void print_something(
        const int& value);

// This should not fail
template <>
CPP_UTILS_DllAPI
void print_something(
        const std::string& value);

} /* namespace testing */
} /* namespace utils */
} /* namespace eprosima */
