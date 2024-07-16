cmake_minimum_required(VERSION 3.2)
project(Boids)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories( ${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include

    ${CMAKE_SOURCE_DIR}/external/glm

    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/imgui/backends

    ${CMAKE_SOURCE_DIR}/external/stb
)


add_subdirectory(external)
add_subdirectory(include)
add_subdirectory(src)


target_link_libraries(${PROJECT_NAME} PUBLIC
    glad
    imgui
    glfw
    glm 
    include
    src
    stb
)