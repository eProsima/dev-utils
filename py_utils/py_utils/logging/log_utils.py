# Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
This file contains utils to use native python Log.

Implement a Custom Logger class and creates a global object of such class.
In order to use this log handler, import logger object from this module and use it
as any other Logger:
- logger.info(...)
- logger.debug(...)
- logger.log(logging.DEBUG, ...)

In order to set a different log level, use setLevel or activate_debug logger methods.
"""

import logging


def getCustomLogger(log_level: int = logging.INFO,
                    logger_name: str = 'GLOBAL_LOG'):
    """
    Return a custom logger set with eProsima default configurations.

    It gets a Logger object.
    If it exists, return it as it have been configured,
    if it does not, create it and set default format and level.
    """

    alreadyExist = logger_name in logging.root.manager.loggerDict.keys()
    logger = logging.getLogger(logger_name)

    # If Logger already existed, use it as it was configured
    if alreadyExist:
        return logger

    # Otherwise, use default values for it
    l_format = logging.Formatter(
      '[%(asctime)s][%(name)s][%(levelname)s][%(filename)s:%(lineno)s - %(funcName)s] %(message)s')
    l_handler = logging.StreamHandler()
    l_handler.setFormatter(l_format)
    logger.addHandler(l_handler)

    logger.setLevel(log_level)

    return logger


def activate_debug(logger_name: str = 'GLOBAL_LOG'):
    logger = getCustomLogger(logger_name=logger_name)
    logger.setLevel(logging.DEBUG)


"""Global instance of logger using CustomLogger class."""
logger = getCustomLogger()
