cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXE_LINKER_FLAGS "/FORCE")

project(lcd-opencv)

find_package(OpenCV REQUIRED PATHS "${CMAKE_SOURCE_DIR}/lib/opencv/build")

file(GLOB SRC_FILES
    "src/*.cpp"
)

add_executable(lcd-opencv ${SRC_FILES})
target_link_libraries(lcd-opencv LINK_PRIVATE ${OpenCV_LIBS})
target_include_directories(lcd-opencv PRIVATE ${OpenCV_INCLUDE_DIRS})

file(GLOB DLL_FILES
    "${CMAKE_SOURCE_DIR}/lib/opencv/build/x64/vc15/bin/*.dll"
)

add_custom_command(
    TARGET lcd-opencv
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL_FILES}
        $<TARGET_FILE_DIR:lcd-opencv>
)
