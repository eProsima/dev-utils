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

###############################################################################
# Set settings for project cpp_utils
###############################################################################

set(MODULE_NAME
    cpp_utils)

set(MODULE_SUMMARY
    "C++ library for generic useful methods and classes for Developers.")

set(MODULE_FIND_PACKAGES
        fastcdr
        fastrtps
    )

set(MODULE_DEPENDENCIES
        $<$<BOOL:${WIN32}>:iphlpapi$<SEMICOLON>Shlwapi>
        ${MODULE_FIND_PACKAGES}
    )

###################################################################################
# NOTE: workaround for https://bugs.launchpad.net/ubuntu/+source/gcc-9/+bug/2029910
# Better be done with FindThreads.cmake as in Fast-DDS, but it's just a workaround
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
###################################################################################

set(MODULE_THIRDPARTY_HEADERONLY
    filewatch)
