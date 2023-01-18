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
 * @file utils.cpp
 *
 */

#include <algorithm>
#include <assert.h>
#include <set>
#include <stdlib.h>

// TODO remove
#include <iostream>

// These libraries are used to execute wildcard using system functions, and depend on the OS
#if defined(_WIN32)
#include "Shlwapi.h"
#else
#include <fnmatch.h>
#endif // if defined(_WIN32)

// Includes to use access method. It checks if a file exists and it is readable
#if defined(_WIN32)
#include <io.h>         // Use _access windows method
#define access _access  // Allow using same method for UNIX and windows
#else
#include <unistd.h>
#endif // if defined(_WIN32)

#include <cpp_utils/math/math_extension.hpp>
#include <cpp_utils/utils.hpp>
#include <cpp_utils/Log.hpp>

namespace eprosima {
namespace utils {

//! Overloaded '|' operator for composing FileAccessMode values.
FileAccessMode operator |(
        FileAccessMode mode_a,
        FileAccessMode mode_b)
{
    return static_cast<FileAccessMode>(static_cast<FileAccessModeType>(mode_a) |
           static_cast<FileAccessModeType>(mode_b));
}

//! Overloaded '&' operator for matching FileAccessMode values.
FileAccessMode operator &(
        FileAccessMode mode_a,
        FileAccessMode mode_b)
{
    return static_cast<FileAccessMode>(static_cast<FileAccessModeType>(mode_a) &
           static_cast<FileAccessModeType>(mode_b));
}

bool match_pattern(
        const std::string& pattern,
        const std::string& str) noexcept
{
#if defined(_WIN32)
    // Windows implementation
    return PathMatchSpec(str.c_str(), pattern.c_str());
#else
    // Posix implementation
    return (fnmatch(pattern.c_str(), str.c_str(), FNM_NOESCAPE) == 0);
#endif // defined(_WIN32)
}

void to_lowercase(
        std::string& st) noexcept
{
    std::transform(st.begin(), st.end(), st.begin(),
            [](unsigned char c)
            {
                return std::tolower(c);
            });
}

void tsnh(
        const Formatter& formatter)
{
    logError(UTILS_TSNH, "This Should Not Have Happened: " << formatter.to_string());
    Log::Flush();

    abort();
}

bool is_file_accessible(
        const char* file_path,
        FileAccessMode access_mode) noexcept
{
#if defined(_WIN32)
    if ((FileAccessMode::exec& access_mode) == FileAccessMode::exec)
    {
        logWarning(
            DDSROUTER_UTILS,
            "Windows does not allow to check execution permission for file.");
        // Take out the FileAccessMode::exec bit
        access_mode =
                static_cast<FileAccessMode>(static_cast<FileAccessModeType>(access_mode) &
                ~static_cast<FileAccessModeType>(FileAccessMode::exec));
    }
#endif // if defined(_WIN32)
    return access(file_path, static_cast<FileAccessModeType>(access_mode)) != -1;
}

bool replace_first(
        std::string& st,
        std::string const& to_replace,
        std::string const& replace_by)
{
    std::size_t pos = st.find(to_replace);
    if (pos == std::string::npos)
    {
        return false;
    }
    else
    {
        st.replace(pos, to_replace.length(), replace_by);
        return true;
    }
}

unsigned int replace_all(
        std::string& st,
        std::string const& to_replace,
        std::string const& replace_by)
{
    unsigned int replacements = 0;
    while (replace_first(st, to_replace, replace_by))
    {
        replacements++;
    }
    return replacements;
}

unsigned int strip_str(
        std::string& to_strip,
        const std::string& replace_by /* = "" */,
        const std::set<std::string>& undesired_strings /* = {"\r"} */)
{
    unsigned int replacements = 0;
    for (const auto& undesired : undesired_strings)
    {
        replacements += replace_all(to_strip, undesired, replace_by);
    }
    return replacements;
}

} /* namespace utils */
} /* namespace eprosima */
