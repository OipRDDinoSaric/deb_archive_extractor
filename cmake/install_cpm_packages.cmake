include(${CMAKE_CURRENT_LIST_DIR}/utility.cmake)

CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 11.0.1
)

if (false)
    CPMAddPackage(
            NAME Boost
            VERSION 1.86.0
            GITHUB_REPOSITORY boostorg/boost
            # Included libraries separators must be escaped, e.g., iostreams\\\;asio
            OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_INCLUDE_LIBRARIES iostreams"
            GIT_TAG "boost-1.86.0"
    )

    CPMAddPackage(
            NAME zlib
            VERSION 1.3.1
            GITHUB_REPOSITORY madler/zlib
    )

    CPMAddPackage(
            NAME libarchive
            VERSION 3.7.4
            GITHUB_REPOSITORY libarchive/libarchive
    )
endif ()

declare_system_library(fmt::fmt)
