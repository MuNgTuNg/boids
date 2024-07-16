#pragma once
#include <includes.hpp>

#include <string>


#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000

namespace shb{

class Monitor{
  public:
    Monitor(){

    }

  private:
    GLFWmonitor* m_Handle = nullptr;
    bool m_PrimaryMonitor = false;
};

class MonitorManager{
  public:
    MonitorManager(){
        //get list of monitors.
        int numMonitors = 0;
        GLFWmonitor** monitorsArr = glfwGetMonitors(&numMonitors);

        for(int i = 0; i < numMonitors; ++i){
            GLFWmonitor* currentMonitor = monitorsArr[i];

            const char* name = glfwGetMonitorName(currentMonitor);
            printf("Monitor name: %s\n", name);

            int viewX = 0, viewY =0;
            glfwGetMonitorPos(currentMonitor,&viewX,&viewY);
            printf("Monitor viewport position: X:%d Y:%d\n",viewX,viewY);

            int WAx = 0, WAy = 0, WAwidth = 0, WAheight = 0;
            glfwGetMonitorWorkarea(currentMonitor,&WAx,&WAy,&WAwidth,&WAheight);
            printf("Work area: X:%d Y:%d Width:%d Height:%d\n", WAx,WAy,WAwidth,WAheight);

            int widthMM = 0, heightMM = 0;
            glfwGetMonitorPhysicalSize(currentMonitor,&widthMM,&heightMM);
            printf("Monitor Physical Size: Width (mm):%d Height(mm):%d\n",widthMM, heightMM);

            float xScale = 0, yScale = 0;
            glfwGetMonitorContentScale(currentMonitor,&xScale,&yScale);
            printf("Content Scale: X:%f, Y:%f\n");

            const GLFWvidmode* vidmode = glfwGetVideoMode(currentMonitor);
            printf("Current Vidmode - Width: %d, Height: %d, Red bits: %d, Green bits: %d, Blue bits: %d, Refresh rate(Hz): %d\n", vidmode->width, vidmode->height, vidmode->redBits, vidmode->greenBits, vidmode->blueBits, vidmode->refreshRate);

            int vidmodeCount = 0;
            const GLFWvidmode* vidmodes = glfwGetVideoModes(currentMonitor,&vidmodeCount);
            bool printAllVidmodes = false;

            if(printAllVidmodes){
                for(int i = 0; i < vidmodeCount; ++i){
                    GLFWvidmode currVidmode = vidmodes[i];
                    printf("Vidmode %d - Width: %d, Height: %d, Red bits: %d, Green bits: %d, Blue bits: %d, Refresh rate(Hz): %d\n",i, currVidmode.width, currVidmode.height, currVidmode.redBits, currVidmode.greenBits, currVidmode.blueBits, currVidmode.refreshRate);
                }
            }

            printf("\n");

        }


    }

    //get vidmodes
    //get available vidmodes
    //get primary monitor
    //get position of monitors viewpoint
    //get work area
    //get physical size
    //get content scale
    //set config callback?
    //get gamma ramp
    //

  private:
    //int m_NumMonitors = 0;
    //GLFWmonitor** m_MonitorsArr;
};

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