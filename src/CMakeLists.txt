add_library(src 
    main.cpp
)

target_include_directories( src PUBLIC 
    ${CMAKE_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glad/src
    ${CMAKE_SOURCE_DIR}/external/glfw/include

    ${CMAKE_SOURCE_DIR}/external/glm

    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/imgui/backends

    ${CMAKE_SOURCE_DIR}/external/stb
)



