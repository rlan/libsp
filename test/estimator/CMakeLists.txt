cmake_minimum_required (VERSION 3.1)
project (test_misc CXX)

set (CMAKE_CXX_STANDARD 11)
#set(SOURCE_FILES )

find_package (Boost 1.48.0 COMPONENTS system unit_test_framework REQUIRED)
if (Boost_FOUND)
  include_directories ("../../src" "${Boost_INCLUDE_DIRS}")

  add_executable (test_misc main.cc)
  target_link_libraries (test_misc ${Boost_LIBRARIES})
endif()
