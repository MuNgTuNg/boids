#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <string>
#include <vector>
#include <mutex>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000

namespace shb{

class Window
{
  public:
    Window( const std::string& title = "No Title", int width = WIN_WIDTH, int height = WIN_HEIGHT, int monitor = 0) : m_Width(width), m_Height(height), m_Title(title) {
        
        setDefaultWindowHints();
    
        //generate window handle
        m_Handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!m_Handle){
            printf("Window creation error\n");
            glfwTerminate();
        }

        populateWindowInfo();

        glfwMakeContextCurrent(m_Handle);
        m_ContextCurrent = true;
        gladLoadGL();

        glViewport( 0, 0, width, height);
        glClearColor(0,0,0,255);
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

    void setDefaultWindowHints(){
        //set window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
        //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    }

 
    void recreateWindow(){

        GLFWwindow* newWindow = nullptr;
        newWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
        if (!newWindow){
            printf("Window creation error\n");
            glfwTerminate();
        }

        if(m_Handle){
            glfwDestroyWindow(m_Handle);
            m_Handle = nullptr;
        }

        m_Handle = newWindow;
        glfwMakeContextCurrent(m_Handle);

        glViewport( 0, 0, m_Width, m_Height);
        glClearColor(0,0,0,255);
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

  public:
    bool isDecorated = false;

  private:

     void populateWindowInfo(){
        isDecorated = glfwGetWindowAttrib(m_Handle, GLFW_DECORATED);
    }

    GLFWwindow* m_Handle = nullptr; 
    int m_Height = 0;
    int m_Width = 0;
    bool m_ContextCurrent = false;
    std::string m_Title;

    
    
};



}//namespace shb