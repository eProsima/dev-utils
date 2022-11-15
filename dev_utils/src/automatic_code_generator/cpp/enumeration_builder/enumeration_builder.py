# Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
Script to generate code for ENUMERATION_BUILDER in C++.

NOTE: This script is meant to be a standalone, without requiring any other script, file or path.
"""

import argparse
import datetime
import os

DESCRIPTION = """Script to generate code for ENUMERATION_BUILDER in C++."""
USAGE = (
    'python3 enumeration_builder.py'
    ' --enum CustomEnum'
    ' --values "value1;value2"'
    ' --output include/output.hpp'
    ' --namespaces "eprosima;utils"'
)

TEMPLATE_TEXT = """
// Copyright %year% Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file %enum_name%.hpp
 */

#pragma once

#include <array>
#include <string>
#include <stdexcept>

%start_namespace%

enum class %enum_name%
{
%values%
};

const std::array<std::string, %n_values%> NAMES_%enum_name% =
{
%quotes_values%
};

inline const std::string& to_string(
        const %enum_name%& e)
{
    return NAMES_%enum_name%[static_cast<int>(e)];
}

inline %enum_name% from_string_%enum_name%(
        const std::string& s)
{
    for (int i = 0; i < %n_values%; i++)
    {
        if (NAMES_%enum_name%[i] == s)
        {
            return static_cast<%enum_name%>(i);
        }
    }
    throw std::invalid_argument("Incorrect name for enum %enum_name%.");
}

inline std::ostream& operator <<(
        std::ostream& os,
        const %enum_name%& e)
{
    os << to_string(e);
    return os;
}

constexpr const unsigned int N_VALUES_%enum_name% = %n_values%;

%end_namespace%
"""


def parse_options():
    """
    Parse arguments.

    :return: The arguments parsed.
    """
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        add_help=True,
        description=(DESCRIPTION),
        usage=(USAGE)
    )

    required_args = parser.add_argument_group('required arguments')
    required_args.add_argument(
        '-e',
        '--enum',
        type=str,
        required=True,
        help='Name of the Enumeration.'
    )
    required_args.add_argument(
        '-v',
        '--values',
        type=str,
        required=True,
        help="Name of values separated by ';' (blank spaces would be stripped)."
    )

    parser.add_argument(
        '-o',
        '--output',
        type=str,
        default=None,
        help='Path to hpp output file. [Default: <Enumeration Name>.hpp'
    )
    parser.add_argument(
        '-n',
        '--namespaces',
        type=str,
        default='eprosima',
        help="Namespaces separated by ';' (blank spaces would be stripped)."
    )

    return parser.parse_args()


def parse_values(
        values_str: str):
    """Convert string arguments into a list of strings."""
    return [x.strip() for x in values_str.split(';')]


def replace_in_text(
        text_to_replace: str,
        original_str: str,
        replacement_str: str) -> str:
    """Replace every occurrence of %original_str% for replacement_str."""
    return text_to_replace.replace(f'%{original_str}%', replacement_str)


def get_year() -> str:
    """Return a string with the current year."""
    return str(datetime.date.today().year)


def generate_file_text(
        template_text: str,
        enumeration_name: str,
        enumeration_values,
        namespaces) -> str:
    """Generate text for file from template."""
    # Get text
    text = template_text

    # Parse year
    text = replace_in_text(text, 'year', get_year())

    # Parse start_namespace
    text = replace_in_text(
        text,
        'start_namespace',
        '\n'.join([f'namespace {x} {{' for x in namespaces]))

    # Parse end_namespace
    text = replace_in_text(
        text,
        'end_namespace',
        '\n'.join([f'}} /* namespace {x} */' for x in reversed(namespaces)]))

    # Parse enum_name
    text = replace_in_text(text, 'enum_name', enumeration_name)

    # Parse values
    text = replace_in_text(
        text,
        'values',
        ',\n'.join([f'    {x}' for x in enumeration_values]))

    # Parse between quotes values
    text = replace_in_text(
        text,
        'quotes_values',
        ',\n'.join([f'    "{x}"' for x in enumeration_values]))

    # Parse n_values
    text = replace_in_text(text, 'n_values', str(len(enumeration_values)))

    return text


def generate_file(
        output_file: str,
        text: str) -> int:
    """Write down text in target file."""
    # Check path exists and creates it
    path_without_file = os.path.dirname(os.path.abspath(output_file))
    os.makedirs(path_without_file, exist_ok=True)

    # Write down file
    with open(output_file, 'w') as f:
        f.write(text)

    return 0


def main():
    """Run main routine."""
    # Parse arguments
    args = parse_options()

    return generate_file(
        output_file=(args.output if args.output else args.enum),
        text=generate_file_text(
            template_text=TEMPLATE_TEXT,
            enumeration_name=args.enum,
            enumeration_values=parse_values(args.values),
            namespaces=parse_values(args.namespaces)))


if __name__ == '__main__':
    main()
