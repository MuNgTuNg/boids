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
    Window( const std::string& title = "No Title", int width = WIN_WIDTH, int height = WIN_HEIGHT, int monitor = 0) ;
        
    void setDefaultWindowHints();
    void setDefaultWindowDetails();
    void recreateWindow();
    void initWindow();

    GLFWwindow* handle() const { return m_Handle;}
    std::string const title() { return m_Title; }

    int height() { 
        glfwGetWindowSize(m_Handle, &m_Width, &m_Height);
        return m_Height; 
    }
    int width() { 
        glfwGetWindowSize(m_Handle, &m_Width, &m_Height);
        return m_Width; 
    }

  public:
    bool isDecorated = true;
    bool isResizable = true;

  private:

    void populateWindowInfoAttributes();

    GLFWwindow* m_Handle = nullptr; 
    int m_Height = 0;
    int m_Width = 0;
    bool m_ContextCurrent = false;
    std::string m_Title;

};



}//namespace shb