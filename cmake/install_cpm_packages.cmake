CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 11.0.1
)

CPMAddPackage(
        NAME Boost
        VERSION 1.86.0
        GITHUB_REPOSITORY boostorg/boost
        OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_INCLUDE_LIBRARIES ;iostreams" # Note the escapes!
        GIT_TAG "boost-1.86.0"
)