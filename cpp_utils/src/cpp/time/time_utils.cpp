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

#include <cpp_utils/time/time_utils.hpp>
#include <cpp_utils/exception/PreconditionNotMet.hpp>

namespace eprosima {
namespace utils {

Timestamp now() noexcept
{
    return std::chrono::system_clock::now();
}

Timestamp the_end_of_times() noexcept
{
    return std::chrono::time_point<std::chrono::system_clock>::max();
}

std::string to_string(
        const Timestamp& timestamp,
        const std::string& format /* = "%Z_%Y-%m-%d_%H-%M-%S" */)
{
	std::ostringstream ss;
    const std::chrono::high_resolution_clock::time_point::duration duration = timestamp.time_since_epoch();
	const time_t duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    const std::tm *tm = std::localtime(&duration_seconds);

	if (tm) {
		ss << std::put_time(tm, format.c_str());
	}
	else {
	    // gmtime/localtime() returned null
		throw PreconditionNotMet(STR_ENTRY << "Format <" << format << "> to convert Timestamp to string is incorrect.");
	}
	return ss.str();
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

} /* namespace utils */
} /* namespace eprosima */
