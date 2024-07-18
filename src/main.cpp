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
    shb::Window window{"Boids"};
    glfwMakeContextCurrent(window.handle());
    shb::MonitorManager* monitorManager = shb::MonitorManager::getInstance();

    //main loop
    while (!glfwWindowShouldClose(window.handle())){ 
        glClearColor(0,0,0,255);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        glfwSwapBuffers(window.handle());
        glfwPollEvents();
    }

    //destruction of scene
    glfwTerminate();
    return 0;
}