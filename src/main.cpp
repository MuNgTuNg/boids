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
    shb::MonitorManager manager{};

    //main loop
    while (!glfwWindowShouldClose(window.handle())){   
        glfwMakeContextCurrent(window.handle());
        glfwSwapBuffers(window.handle());
        glfwPollEvents();
    }

    //destruction of scene
    glfwTerminate();
    return 0;
}