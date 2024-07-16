add_library(include INTERFACE
   main.hpp
   defines.hpp
   window.hpp
)

target_include_directories( include INTERFACE
    ${CMAKE_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include

    ${CMAKE_SOURCE_DIR}/external/glm

    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/imgui/backends

    ${CMAKE_SOURCE_DIR}/external/stb
)



