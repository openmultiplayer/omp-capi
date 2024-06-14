cmake_minimum_required(VERSION 3.19)
project(CAPI LANGUAGES C CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

function(GroupSourcesByFolder target)
    set(SOURCE_GROUP_DELIMITER "/")
    set(last_dir "")
    set(files "")

    get_target_property(sources ${target} SOURCES)

    foreach(file ${sources})
        file(RELATIVE_PATH relative_file "${CMAKE_CURRENT_SOURCE_DIR}" ${file})
        get_filename_component(dir "${relative_file}" PATH)
        if(NOT "${dir}" STREQUAL "${last_dir}")
            if(files)
                source_group("${last_dir}" FILES ${files})
            endif()
            set(files "")
        endif()
        set(files ${files} ${file})
        set(last_dir "${dir}")
    endforeach()

    if(files)
        source_group("${last_dir}" FILES ${files})
    endif()
endfunction()

add_subdirectory(sdk)

file(GLOB_RECURSE CAPI_FILES
    "include/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

add_definitions(-DCAPI_COMPONENT_BUILD)
add_library(${PROJECT_NAME} SHARED ${CAPI_FILES})

GroupSourcesByFolder(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "$")
