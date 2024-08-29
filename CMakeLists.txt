cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(radar_contact)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
    set(CMAKE_INSTALL_RPATH "${PROJECT_BINARY_DIR}/_deps/sfml-src/extlibs/libs-osx/Frameworks")
endif()

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

if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main sfml-graphics sfml-window sfml-audio sfml-system Threads::Threads)
elseif(LINUX)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-audio sfml-system Threads::Threads X11)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-audio sfml-system Threads::Threads)
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

include(cmake/CopyHelper.cmake)

copy_files(DIRECTORY resources)