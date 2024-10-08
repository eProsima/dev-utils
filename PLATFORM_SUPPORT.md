# Platform Support

This document reflects the level of support offered by *eprosima Dev utils* on different platforms as per the following
definitions:

## Tier 1

Tier 1 platforms are subjected to our unit test suite and other testing tools on a frequent basis including continuous
integration jobs, nightly jobs, packaging jobs, and performance testing.
Errors or bugs discovered in these platforms are prioritized for correction by the development team.
Significant errors discovered in Tier 1 platforms can impact release dates and we strive to resolve all known high
priority errors in Tier 1 platforms prior to new version releases.

## Tier 2

Tier 2 platforms are subject to periodic CI testing which runs both builds and tests with publicly accessible results.
The CI is expected to be run at least within a week of relevant changes for the current release of *Dev Utils*.
Installation instructions should be available and up-to-date in order for a platform to be listed in this category.
Package-level binary packages may not be provided but providing a downloadable archive of the built workspace is
encouraged.
Errors may be present in released product versions for Tier 2 platforms.
Known errors in Tier 2 platforms will be addressed subject to resource availability on a best effort basis and may or
may not be corrected prior to new version releases.
One or more entities should be committed to continuing support of the platform.

## Tier 3

Tier 3 platforms are those for which community reports indicate that the release is functional.
The development team does not run the unit test suite or perform any other tests on platforms in Tier 3.
Community members may provide assistance with these platforms.

## Platforms

|Architecture|Ubuntu Focal (20.04)|Ubuntu Jammy (22.04)|Ubuntu Noble (24.04)|Windows 10 (VS2019)|Windows 10 (VS2022)|Debian Buster (10)|
|------------|--------------------|--------------------|--------------------|-------------------|-------------------|------------------|
|amd64       |Tier 3              |Tier 1              |Tier 1              |Tier 1             |Tier 1             |Tier 3            |
|arm64       |Tier 3              |                    |                    |                   |                   |Tier 3            |

## Compilers

Tier 1 compilers and minimum supported versions:

* GCC 9
* Clang 12
* MSVC v142 (Visual Studio 2019)
* MSVC v143 (Visual Studio 2022)

Tier 3 compilers:

* MSVC v141 (Visual Studio 2017)
