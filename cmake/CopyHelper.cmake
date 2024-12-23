# helper function to copy files to build directory and install directory without duplicating file names across commands
function(copy_files)
    set(options COPY_TO_DESTINATION)
    set(oneValueArgs TARGET_NAME)
    set(multiValueArgs FILES DIRECTORY)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${oneValueArgs}" "${multiValueArgs}")

    # copy files to build dir
    foreach(file ${ARG_FILES})
        add_custom_command(
            TARGET ${ARG_TARGET_NAME} POST_BUILD
            COMMENT "Copying ${file}..."
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/${file} $<TARGET_FILE_DIR:${ARG_TARGET_NAME}>)
            # ${CMAKE_CURRENT_BINARY_DIR})
    endforeach()

    # copy folders to build dir
    foreach(dir ${ARG_DIRECTORY})
        add_custom_command(
            TARGET ${ARG_TARGET_NAME} POST_BUILD
            COMMENT "Copying directory ${dir}..."
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            ${CMAKE_SOURCE_DIR}/${dir} $<TARGET_FILE_DIR:${ARG_TARGET_NAME}>/${dir})
            # ${CMAKE_CURRENT_BINARY_DIR}/${dir})
    endforeach()

    if(ARG_COPY_TO_DESTINATION)
        # copy files and folders to install dir
        install(FILES ${ARG_FILES} DESTINATION ${DESTINATION_DIR})
        install(DIRECTORY ${ARG_DIRECTORY} DESTINATION ${DESTINATION_DIR})
    endif()
endfunction()
