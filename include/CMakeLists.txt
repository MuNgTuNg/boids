add_library(include INTERFACE
   main.hpp
   gui.hpp
)

target_include_directories( include INTERFACE
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/core/external/glad/include
    ${CMAKE_SOURCE_DIR}/core/external/glfw/include
    ${CMAKE_SOURCE_DIR}/core/external/glm

    ${CMAKE_SOURCE_DIR}/core/external/imgui
    ${CMAKE_SOURCE_DIR}/core/external/imgui/backends

    ${CMAKE_SOURCE_DIR}/core/external/stb
)



