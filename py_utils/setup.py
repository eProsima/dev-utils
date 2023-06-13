"""Setup file to create py_utils library."""

import os
from setuptools import setup

package_name = 'py_utils'

description = 'Developer Python utils'
long_description = description

# Get all python files in any directory with an __init__.py file in it (except __init__.py files)
file_packages = [
    root
    for root, _, files
    in os.walk(package_name)
    if '__init__.py' in files]

setup(
    name=package_name,
    version='0.0.0',
    packages=file_packages,
    long_description=long_description,
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='eprosima',
    maintainer_email='javierparis@eprosima.com',
    description=description,
    license='Apache License, Version 2.0',
    tests_require=['pytest'],
    test_suite='test',
    entry_points={},
)
