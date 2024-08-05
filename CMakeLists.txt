cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(radar_contact)

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
    GIT_TAG        2.6.1
    # GIT_TAG        69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
    # GIT_TAG        origin/master
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
        source/DataFetcher.hpp
        source/DataFetcher.cpp
        source/LiveAPI.hpp
        source/LiveAPI.cpp
        source/utils.hpp
        source/utils.cpp
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
)

if(MSVC)
    # NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else()
    # NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()


include(cmake/CompilerFlags.cmake)

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${cpr_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${json_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)

if(MSVC OR WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main sfml-graphics sfml-window sfml-system sfml-network sfml-audio Threads::Threads)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio Threads::Threads X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# copy dependent DLLs to build dir
# see https://en.sfml-dev.org/forums/index.php?topic=28580.0
# remove this if not using audio or if using SFML 3
if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
         ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
         $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()


file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
