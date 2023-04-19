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

# Return a list of all cpp and hpp files in library
# Arguments:
# RESULT -> List of source files where new sources will be added
function(all_library_sources RESULT)

    file(GLOB_RECURSE LIBRARY_SOURCES
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.c"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.cpp"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.cxx"
        )
    set(NEW_RESULT "${RESULT};${LIBRARY_SOURCES}")
    set(RESULT ${NEW_RESULT} PARENT_SCOPE)

endfunction()

# Return a list of all hpp files in library
# set variable ALL_LIBRARY_PUBLIC_HEADERS_RESULT with the result
function(all_library_public_headers)

    file(GLOB_RECURSE LIBRARY_HEADERS
            "${PROJECT_SOURCE_DIR}/include/**/**/*.h"
            "${PROJECT_SOURCE_DIR}/include/**/**/*.hpp"
            "${PROJECT_SOURCE_DIR}/include/**/**/*.hxx"
        )

    set(ALL_LIBRARY_PUBLIC_HEADERS_RESULT_ "")
    foreach(HEADER ${LIBRARY_HEADERS})
      file(RELATIVE_PATH HEADER_RELATIVE_PATH ${PROJECT_SOURCE_DIR}/include ${HEADER})
      list(APPEND ALL_LIBRARY_PUBLIC_HEADERS_RESULT_ "${HEADER_RELATIVE_PATH}")
    endforeach()

    set(ALL_LIBRARY_PUBLIC_HEADERS_RESULT "${ALL_LIBRARY_PUBLIC_HEADERS_RESULT_}" PARENT_SCOPE)

endfunction()
