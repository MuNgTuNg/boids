#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <string>
#include <vector>
#include <mutex>


#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000

namespace shb{

class Window
{
  public:
    Window( const std::string& title = "No Title", int width = WIN_WIDTH, int height = WIN_HEIGHT, int monitor = 0) : m_Width(width), m_Height(height){
        //set window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
        //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    
    
        //generate window handle
        m_Handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!m_Handle){
            printf("Window creation error\n");
            glfwTerminate();
        }


        //const GLFWvidmode* vidmode = glfwGetVideoMode(monitors[monitor]);
        //int windowHeight = vidmode->height;
        //int windowWidth = vidmode->width;
        //glfwSetWindowMonitor(m_Handle,NULL ,0,0,windowWidth/2,windowHeight/2,GLFW_DONT_CARE);

        glfwMakeContextCurrent(m_Handle);
        m_ContextCurrent = true;
        gladLoadGL();

        glViewport( 0, 0, width, height);
        //glEnable              ( GL_DEBUG_OUTPUT );
        //glDebugMessageCallback( MessageCallback, 0 );
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        glEnable(GL_DEPTH_TEST);

        //Window icon
        GLFWimage image[1];
        image[0].pixels = stbi_load("../resources/textures/icon.png", &image[0].width, &image[0].height, 0, 4); 
        if(image->pixels){
            glfwSetWindowIcon(m_Handle, 1, image);
            stbi_image_free(image[0].pixels); 
        }
        else{
            printf("No window icon! Add a .png titled 'icon.png' into resources/textures/\n");
        }
    }

    GLFWwindow* handle() const { return m_Handle;}

  private:
    GLFWwindow* m_Handle = nullptr; 
    int m_Height = 0;
    int m_Width = 0;
    bool m_ContextCurrent = false;
    
};



}//namespace shb