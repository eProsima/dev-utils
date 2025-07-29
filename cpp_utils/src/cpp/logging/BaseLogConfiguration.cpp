// Copyright 2024 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file BaseLogConfiguration.cpp
 *
 */

#include <cpp_utils/logging/BaseLogConfiguration.hpp>
#include <cpp_utils/utils.hpp>

namespace eprosima {
namespace utils {


BaseLogConfiguration::BaseLogConfiguration()
    : verbosity{VerbosityKind::Warning, FuzzyLevelValues::fuzzy_level_default}
{
}

bool BaseLogConfiguration::is_valid(
        Formatter& error_msg) const noexcept
{
    return true;
}

void BaseLogConfiguration::set(
        const utils::Fuzzy<VerbosityKind>& log_verbosity) noexcept
{
    if (verbosity.get_level() <= log_verbosity.get_level())
    {
        verbosity = log_verbosity;
    }
}

void BaseLogConfiguration::set(
        const LogFilter& log_filter)
{
    if (filter.error.get_level() <= log_filter.error.get_level())
    {
        filter.error.set_value(log_filter.error.get_value());
    }

    if (filter.warning.get_level() <= log_filter.warning.get_level())
    {
        filter.warning.set_value(log_filter.warning.get_value());
    }

    if (filter.info.get_level() <= log_filter.info.get_level())
    {
        filter.info.set_value(log_filter.info.get_value());
    }
}

std::ostream& operator <<(
        std::ostream& os,
        const Fuzzy<VerbosityKind>& kind)
{
    os << "Fuzzy{Level(" << kind.get_level_as_str() << ") " << kind.get_reference() << "}";
    return os;
}

} /* namespace utils */
} /* namespace eprosima */
