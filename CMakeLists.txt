cmake_minimum_required(VERSION 3.2)
project(Boids)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} src/main.cpp)


add_subdirectory(core)
add_subdirectory(include)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glad
    imgui
    glfw
    glm 
    shb_core
    include
    src
    stb
)