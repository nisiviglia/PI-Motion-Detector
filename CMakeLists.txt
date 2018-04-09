cmake_minimum_required (VERSION 3.2)
set (CMAKE_CXX_STANDARD 11)

# Project name
project (pi_door_alarm)

# Set build output directories
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add header files to project
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Grab all source files
file (GLOB_RECURSE pi_door_alarm_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Check for Boost libraries
find_package(Boost REQUIRED COMPONENTS system log filesystem thread) 
include_directories( ${Boost_INCLUDE_DIRS} )

# Create project as an executable 
add_executable(pi_door_alarm src/pi_door_alarm.cpp ${pi_door_alarm_SOURCES})
target_link_libraries (pi_door_alarm ${Boost_LIBRARIES})

##################################################################
# googletest setup
# https://github.com/google/googletest/blob/master/googletest/README.md
#
##################################################################
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# Enable testing
enable_testing()

##################################################################
# Put additional tests below here.
#
##################################################################
add_executable (smtp_client_test test/smtp_client_test.cpp src/smtp_client.cpp)
target_link_libraries (smtp_client_test gtest_main ${Boost_LIBRARIES})
add_test (NAME smtp_client_test COMMAND smtp_client_test)

add_executable (config_parser_test test/config_parser_test.cpp src/config_parser.cpp)
target_link_libraries (config_parser_test gtest_main ${Boost_LIBRARIES})
add_test (NAME config_parser_test COMMAND config_parser_test)

add_executable (logger_test test/logger_test.cpp src/logger.cpp)
target_link_libraries (logger_test gtest_main ${Boost_LIBRARIES})
add_test (NAME logger_test COMMAND logger_test)

