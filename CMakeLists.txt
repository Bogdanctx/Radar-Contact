cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "radar_contact")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)

###############################################################################

# external dependencies with FetchContent

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# din cauza SFML
set(WARNINGS_AS_ERRORS OFF)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:84
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
    GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.5
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

set(SOURCES
        source/main.cpp
        source/env_fixes.h
        source/Math.hpp
        source/ResourcesManager.hpp
        source/ResourcesManager.cpp
        source/LiveAPI.hpp
        source/LiveAPI.cpp
        source/utils.hpp
        source/MockAPI.hpp
        source/MockAPI.cpp
        source/Game.hpp
        source/Game.cpp
        source/Airplane.hpp
        source/Airplane.cpp
        source/Airport.hpp
        source/Airport.cpp
        source/FlightInfo.hpp
        source/FlightInfo.cpp
        source/FlightsTable.hpp
        source/FlightsTable.cpp
        source/FlyingEntity.hpp
        source/FlyingEntity.cpp
        source/Helicopter.hpp
        source/Helicopter.cpp
        source/Menu.hpp
        source/Menu.cpp
        source/StateMachine.hpp
        source/StateMachine.cpp
        source/Waypoint.hpp
        source/Waypoint.cpp
        source/Weather.hpp
        source/Weather.cpp
        source/AppWindow.hpp
        source/AppWindow.cpp
        source/Region.cpp
        source/Region.hpp
        source/RegionButton.cpp
        source/RegionButton.hpp
        source/RegionButton.cpp
)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
    ${SOURCES}
)

include(cmake/CompilerFlags.cmake)

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${json_SOURCE_DIR}/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${cpr_SOURCE_DIR}/include)

target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE SFML::System SFML::Window SFML::Graphics SFML::Audio Threads::Threads)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE cpr)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE nlohmann_json)


if(APPLE)
elseif(UNIX)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
elseif(MSVC)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE SFML::Main)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

include(cmake/CopyHelper.cmake)
copy_files(DIRECTORY resources COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})