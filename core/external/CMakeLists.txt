add_subdirectory(glm)
add_subdirectory(glfw)

add_library(glad 
    glad/include/glad/glad.h
    glad/include/KHR/khrplatform.h
    glad/src/glad.c
)

target_include_directories( glad PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/glad/include
    ${CMAKE_CURRENT_LIST_DIR}/glad/src
)

add_library(stb INTERFACE
    stb/stb_image.h
    stb/stb_image_write.h
)


add_library(imgui
    #actual imgui lib
    imgui/imconfig.h
    imgui/imgui_demo.cpp 
    imgui/imgui_draw.cpp 
    imgui/imgui_internal.h 
    imgui/imgui_tables.cpp 
    imgui/imgui_widgets.cpp 
    imgui/imgui.cpp 
    imgui/imgui.h  
    imgui/imstb_rectpack.h  
    imgui/imstb_textedit.h 
    imgui/imstb_truetype.h 

    #backends    
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp

    imgui/imgui_impl_opengl3.h
    imgui/imgui_impl_opengl3_loader.h

)

target_include_directories( imgui PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/glfw/include
    ${CMAKE_CURRENT_LIST_DIR}/imgui
)