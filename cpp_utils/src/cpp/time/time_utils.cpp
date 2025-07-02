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
 * @file time_utils.cpp
 *
 */

#include <iomanip>
#include <thread>
#include <sstream>

#include <cpp_utils/macros/macros.hpp>
#include <cpp_utils/time/time_utils.hpp>
#include <cpp_utils/exception/PreconditionNotMet.hpp>
#include <cpp_utils/exception/ValueNotAllowedException.hpp>
#include <cpp_utils/Log.hpp>

// These functions has different names in windows
#if _EPROSIMA_WINDOWS_PLATFORM
#define timegm _mkgmtime
#endif // if _EPROSIMA_WINDOWS_PLATFORM

namespace eprosima {
namespace utils {

Timestamp now() noexcept
{
    return Timeclock::now();
}

Timestamp the_end_of_time() noexcept
{
    return Timestamp::max();
}

Timestamp the_beginning_of_time() noexcept
{
    return Timestamp::min();
}

Timestamp date_to_timestamp(
        unsigned int year,
        unsigned int month,
        unsigned int day,
        unsigned int hour /* = 0 */,
        unsigned int minute /* = 0 */,
        unsigned int second /* = 0 */)
{
    std::tm tm;

    tm.tm_sec = static_cast<int>(second);
    tm.tm_min = static_cast<int>(minute);
    tm.tm_hour = static_cast<int>(hour);
    tm.tm_mday = static_cast<int>(day);
    tm.tm_mon = static_cast<int>(month) - 1;
    tm.tm_year = static_cast<int>(year) - 1900;

    return Timeclock::from_time_t(normalize(timegm(&tm)));
}

Timestamp time_to_timestamp(
        unsigned int hour /* = 0 */,
        unsigned int minute /* = 0 */,
        unsigned int second /* = 0 */)
{
    std::tm tm;

    // Initialise with current timestamp to set date
    time_t duration_seconds = normalize(Timeclock::to_time_t(now()));
    tm = *std::gmtime(&duration_seconds);

    tm.tm_sec = static_cast<int>(second);
    tm.tm_min = static_cast<int>(minute);
    tm.tm_hour = static_cast<int>(hour);

    return Timeclock::from_time_t(timegm(&tm));
}

std::string timestamp_to_string(
        const Timestamp& timestamp,
        const std::string& format /* = "%Z_%Y-%m-%d_%H-%M-%S" */,
        bool local_time /* = false */)
{
    std::ostringstream ss;
    time_t duration_seconds = normalize(Timeclock::to_time_t(timestamp));

    std::tm* tm = nullptr;
    if (local_time)
    {
        tm = std::localtime(&duration_seconds);
    }
    else
    {
        tm = std::gmtime(&duration_seconds);
    }

    if (tm)
    {
        ss << std::put_time(tm, format.c_str());
    }
    else
    {
        // gmtime/localtime() returned null
        throw PreconditionNotMet(STR_ENTRY << "Format <" << format << "> to convert Timestamp to string is incorrect.");
    }
    return ss.str();
}

Timestamp string_to_timestamp(
        const std::string& timestamp,
        const std::string& format /* = "%Z_%Y-%m-%d_%H-%M-%S" */,
        bool local_time /* = false */)
{
    std::istringstream ss(timestamp);
    std::tm tm{};
    ss >> std::get_time(&tm, format.c_str());
    if (ss.fail())
    {
        throw PreconditionNotMet(
                  STR_ENTRY << "Format <" << format << "> to convert string to Timestamp is not valid for timestamp " << timestamp <<
                      ".");
    }

    std::time_t utc_time;
    if (local_time)
    {
        // Attempt to automatically determine if DST in effect
        tm.tm_isdst = -1;
        // WARNING: might not be available in all systems, mktime sets this value to 0/1 if succesfully found this info
        utc_time = std::mktime(&tm);
        if (tm.tm_isdst < 0)
        {
            logWarning(
                UTILS_TIME,
                "DST information could not be found in the system, converted timestamp might be an hour off.");
        }
    }
    else
    {
        utc_time = timegm(&tm);
    }

    if ((time_t)-1 == utc_time)
    {
        throw ValueNotAllowedException(
            STR_ENTRY << "Failed to convert string to timestamp");
    }

    return Timeclock::from_time_t(utc_time);
}

std::chrono::milliseconds duration_to_ms(
        const Duration_ms& duration) noexcept
{
    return std::chrono::milliseconds(duration);
}

void sleep_for(
        const Duration_ms& sleep_time) noexcept
{
    std::this_thread::sleep_for(duration_to_ms(sleep_time));
}

time_t normalize(
        const time_t& time) noexcept
{
    time_t normalized_time = time;
#if _EPROSIMA_WINDOWS_PLATFORM // In Windows std::gmtime does not support negative values
    time_t max_value;

#if _PLATFORM_64BIT
    max_value = 32535215999; // In WIN64, max value is 3000-12-31_23-59-59
#else
    max_value = std::numeric_limits<int32_t>::max(); // In WIN32, values greater than 2^32 are not supported
#endif // if PLATFORM_64BIT

    if (0 > time || time > max_value)
    {
        EPROSIMA_LOG_WARNING(TIME_UTILS,
                "Timestamp value: " << time << " is out of range for Windows, clamping to 0 and " <<
                max_value);
        normalized_time = std::max((time_t) 0, std::min(max_value, time));
    }
#endif // if _EPROSIMA_WINDOWS_PLATFORM
    return normalized_time;
}

} /* namespace utils */
} /* namespace eprosima */
