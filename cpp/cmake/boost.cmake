
# include(FetchContent)
# FetchContent_Declare(
#   boost
#   GIT_REPOSITORY https://github.com/boostorg/boost.git
#   GIT_TAG boost-1.83.0
#   GIT_SHALLOW TRUE
# )
# FetchContent_MakeAvailable(boost)
set(BOOST_INCLUDE_LIBRARIES heap)
set(BOOST_ENABLE_CMAKE ON)
include(FetchContent)
FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.gz
  USES_TERMINAL_DOWNLOAD TRUE
  DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

