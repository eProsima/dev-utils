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
 * @file LogConfiguration.cpp
 *
 */

#include <cpp_utils/logging/LogConfiguration.hpp>
#include <cpp_utils/utils.hpp>

namespace eprosima {
namespace utils {


LogConfiguration::LogConfiguration()
    : verbosity{VerbosityKind::Warning, FuzzyLevelValues::fuzzy_level_default}
{
    filter[VerbosityKind::Info].set_value("", FuzzyLevelValues::fuzzy_level_default);
    filter[VerbosityKind::Warning].set_value("", FuzzyLevelValues::fuzzy_level_default);
    filter[VerbosityKind::Error].set_value("", FuzzyLevelValues::fuzzy_level_default);
}

bool LogConfiguration::is_valid(
        Formatter& error_msg) const noexcept
{
    return true;
}

std::ostream& operator <<(
        std::ostream& os,
        const Fuzzy<VerbosityKind>& kind)
{
    os << "Fuzzy{Level(" << kind.get_level_as_str() << ") " << kind.get_reference() << "}";
    return os;
}

std::ostream& operator <<(
        std::ostream& os,
        const LogFilter& filter)
{
    for (const auto& entry : filter)
    {
        os << "Kind: " << entry.first <<
            ", Regex: " << entry.second.get_value() << std::endl;
    }

    return os;
}

} /* namespace utils */
} /* namespace eprosima */

