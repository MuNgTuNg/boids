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


void shb_main(){

    shb::Window window{"Boids"};
   // shb::MonitorManager* monitorManager = shb::MonitorManager::getInstance();

    //gui()
    shb::initGuiOpenGL3(window.handle(),"#version 330");
    
    //main loop
    bool running = true;
    while (running){ 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //gui.guiFrame()
        shb::guiFrame(&window);
   

        if(glfwWindowShouldClose(window.handle())){
            running = false;
        }
        glfwSwapBuffers(window.handle());
        glfwPollEvents();
    }
    

    //~gui()
    shb::shutdownGUIOpenGL3();
    glfwTerminate();
}



int main()
{
    initOpenGL();
    stbi_set_flip_vertically_on_load(true);

    shb_main();

    return 0;
}