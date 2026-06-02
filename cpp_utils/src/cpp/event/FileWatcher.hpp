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
 * @file FileWatcher.hpp
 */

#pragma once

#include <string>

#if !defined(__APPLE__)
#include <FileWatch.hpp>
#endif // if !defined(__APPLE__)

namespace eprosima {
namespace utils {
namespace event {

#if defined(__APPLE__)

enum class FileWatchEvent
{
    added,
    removed,
    modified,
    renamed_old,
    renamed_new
};

class FileWatcher
{
public:

    template<typename Callback>
    FileWatcher(
            std::string,
            Callback&&)
    {
    }

};

#else

class FileWatcher : public filewatch::FileWatch<std::string>
{
    using filewatch::FileWatch<std::string>::FileWatch;
};

using FileWatchEvent = filewatch::Event;

#endif // defined(__APPLE__)

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */

