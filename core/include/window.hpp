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

#include <glm.hpp>


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

    glm::ivec2 pos(){
      glfwGetWindowPos(m_Handle, &m_Pos.x, &m_Pos.y);
      return m_Pos;
    }

    int frameBufferHeight(){
      glfwGetFramebufferSize(m_Handle, &m_FrameBufferWidth, &m_FrameBufferHeight);
      return m_FrameBufferHeight;
    }
    int frameBufferWidth(){
      glfwGetFramebufferSize(m_Handle, &m_FrameBufferWidth, &m_FrameBufferHeight);
      return m_FrameBufferWidth;
    }

    void setSize(int x, int y){
      if(x <=0 || y <=0){
        printf("Cannot set size lower than 0\n");
        return;
      }
      glfwSetWindowSize(m_Handle,x,y);
      m_Width = x;
      m_Height = y;
    }

    void setPos(int x, int y){
      glfwSetWindowPos(m_Handle, x, y);
      m_Pos.x = x; 
      m_Pos.y = y;
    }

    void limitSize(int minX, int minY, int maxX, int maxY){
      if(minX < 0 || minY < 0 || maxX <= 0 || maxY <= 0){
        printf("All values must be above 0\n");
        return;
      }
      glfwSetWindowSizeLimits(m_Handle, minX, minY, maxX, maxY);
    }


    //bool decorated() { return m_IsDecorated; }
    //bool resizable() { return m_IsResizable; }
    bool m_IsDecorated = true; //move to private asap
    bool m_IsResizable = true;

  private:

    void populateWindowInfoAttributes();

    GLFWwindow* m_Handle = nullptr; 

    int m_Height = 0;
    int m_Width = 0;
    int m_FrameBufferHeight = 0;
    int m_FrameBufferWidth = 0;
    glm::ivec2 m_Pos{0,0};

    bool m_ContextCurrent = false;
    std::string m_Title;

    

};



}//namespace shb