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

// The bundled FileWatch backend is only usable on Windows and Unix. It is disabled
// on QNX (where it compiles but throws at runtime) and on any other platform.
#if (defined(_WIN32) || defined(__unix__)) && !defined(__QNX__)
#define FILEWATCH_ENABLED 1
#else
#define FILEWATCH_ENABLED 0
#endif // FileWatch backend availability

#if FILEWATCH_ENABLED
#include <FileWatch.hpp>
#endif // FILEWATCH_ENABLED

namespace eprosima {
namespace utils {
namespace event {

#if FILEWATCH_ENABLED

class FileWatcher : public filewatch::FileWatch<std::string>
{
    using filewatch::FileWatch<std::string>::FileWatch;
};

using FileWatchEvent = filewatch::Event;

#else

class FileWatcher
{
};

#endif // FILEWATCH_ENABLED

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */
