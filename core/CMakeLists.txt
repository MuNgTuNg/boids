
add_library( shb_core
    include/shb_core.hpp
    include/monitor.hpp
    include/platform.hpp
    include/window.hpp
    src/window.cpp
)

message(STATUS "Directory of current CMakeLists.txt file: ${CMAKE_CURRENT_LIST_DIR}")

target_include_directories(shb_core PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/external/glad/include
    ${CMAKE_CURRENT_LIST_DIR}/external/glad/include/glad
    ${CMAKE_CURRENT_LIST_DIR}/external/glfw/include
    ${CMAKE_CURRENT_LIST_DIR}/external/stb
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
)
add_subdirectory(external)