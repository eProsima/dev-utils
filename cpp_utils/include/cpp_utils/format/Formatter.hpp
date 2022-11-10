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
 * @file Formatter.hpp
 *
 * This file contains class Formatter declaration.
 */

#pragma once

#include <sstream>
#include <string>

#include <cpp_utils/library/library_dll.h>

namespace eprosima {
namespace utils {
namespace format {

/**
 * @brief Auxiliary function to concatenate inplace every kind of object with << to stream.
 *
 * The main case to use this class is in Exception creation. In order to generate an Exception message
 * using the << operator for the objects in the block, add them to Formatter() object and they will be
 * concatenated in a single string.
 *
 * @example
 * Exception(STR_ENTRY << "object1 stream: " << obj1 << " object2 stream: " << obj2);
 */
class Formatter
{
public:

    /////
    // CONSTRUCTOR
    // All ctor, dtor, copy and moves are default.

    /////
    // OPERATORS

    //! Concatenate stream values to this object.
    template<class Val>
    Formatter& operator <<(
            const Val& val);

    /////
    // TO STRING METHODS

    //! Return a string with the concatenation of this object.
    CPP_UTILS_DllAPI operator std::string () const noexcept;

    //! Return a string with the concatenation of this object.
    CPP_UTILS_DllAPI std::string to_string() const noexcept;

protected:

    /////
    // INTERNAL VARIABLES

    //! Concatenated stream where the streams are added at the end.
    std::stringstream ss_;
};

//! \c Formatter to stream serializator
CPP_UTILS_DllAPI std::ostream& operator <<(
        std::ostream& os,
        const Formatter& f);

} /* namespace format */
} /* namespace utils */
} /* namespace eprosima */

// Fast use of Formatter call, simpler to the user
#define STR_ENTRY eprosima::utils::format::Formatter()

// Include implementation template file
#include <cpp_utils/format/impl/Formatter.ipp>
