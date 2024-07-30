#include <main.hpp>

#include <glad.c>

#include <string>




int initOpenGL(){
    int err = 0;
    err = glfwInit();
    if (err == GLFW_FALSE){
        printf("GLFW init error\n");
        if(err == GLFW_PLATFORM_ERROR){
            printf("Error type: GLFW platform error\n");
        }
        return -1;
    }
    
    return 1;
}



int main()
{

    //creation of scene
    initOpenGL();
    stbi_set_flip_vertically_on_load(true);

    shb::MonitorManager* monitorManager = shb::MonitorManager::getInstance();
    
    shb::Window window{"Boids"};

    //gui()
    shb::initGuiOpenGL3(window.handle(),"#version 330");

    
    //main loop
    bool running = true;
    //glfwWindowShouldClose(window.handle());
    while (running){ 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //gui.guiFrame()
        GLFWwindow* prevWindow = window.handle();
        shb::guiFrame(&window);
   
        if(glfwWindowShouldClose(window.handle())){
            running = false;
        }
        glfwSwapBuffers(window.handle());
        glfwPollEvents();
    }
    
    //destruction of scene
    glfwTerminate();

    //~gui()
    shb::shutdownGUIOpenGL3();

    return 0;
}