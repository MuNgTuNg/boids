add_library(src 
    main.cpp
    gui_monitor.cpp
    gui_window.cpp
)


target_include_directories( src PUBLIC 

    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/core/external/glfw/include

    ${CMAKE_SOURCE_DIR}/core/external/stb

    ${CMAKE_SOURCE_DIR}/core/external/glm

    ${CMAKE_SOURCE_DIR}/core/external/imgui
    
    ${CMAKE_SOURCE_DIR}/core/external/glad/include
    ${CMAKE_SOURCE_DIR}/core/external/glad/src
)



