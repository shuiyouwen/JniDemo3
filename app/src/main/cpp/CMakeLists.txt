cmake_minimum_required(VERSION 3.4.1)

set(var hello)
message(${var})
set(var 111)
message(${var})
message(${CMAKE_CURRENT_LIST_FILE})
message(${CMAKE_CURRENT_LIST_DIR})
if (true)
    message("this is true")
endif ()

add_library(
        native-lib
        SHARED
        native-lib.cpp)
add_library(
        people-lib
        SHARED
        people/People.cpp
)
add_library(
        dynamic-lib
        SHARED
        jni/jni_dynamic_load.cpp
)

include_directories(people/)
include_directories(jni/)

find_library(
        log-lib
        log)

target_link_libraries(
        native-lib
        people-lib
        dynamic-lib
        ${log-lib})