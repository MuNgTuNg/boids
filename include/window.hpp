#pragma once
#include <includes.hpp>

#include <string>
#include <mutex>


#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000

namespace shb{

class MonitorManager;
class Monitor{
  friend MonitorManager;
  public:
    Monitor(){

    }

  private:
    GLFWmonitor* m_Handle = nullptr;
    bool m_PrimaryMonitor = false;
};


//https://www.glfw.org/docs/3.3/group__monitor.html 
//https://refactoring.guru/design-patterns/singleton/cpp/example
class MonitorManager{

  public:
    inline static MonitorManager* getInstance(){
      std::lock_guard<std::mutex> lock(m_Mutex);
      if(m_Instance == nullptr){
        m_Instance = new MonitorManager();
      }
      return m_Instance;
    }

    //get primary monitor
    //swap primary monitor

  protected:
    MonitorManager(){
      getMonitors();
    }
    ~MonitorManager(){}
  
  private:
    void getMonitors(){ 
      //get list of monitors.
      int numMonitors = 0;
      GLFWmonitor** monitorsArr = glfwGetMonitors(&numMonitors);
      GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

      for(int i = 0; i < numMonitors; ++i){

        Monitor currMonitor;
        currMonitor.m_Handle = monitorsArr[i];
        //GLFWmonitor* currentMonitor = monitorsArr[i];
        
        std::string name = std::string(glfwGetMonitorName(currMonitor.m_Handle));
        printf("Monitor name: %s\n", name.c_str());

        bool isPrimaryMonitor = false;
        currMonitor.m_Handle == primaryMonitor ? isPrimaryMonitor = true : isPrimaryMonitor = false;
        printf("Primary Monitor: %s\n", isPrimaryMonitor ? "true" : "false");

        int viewX = 0, viewY =0;
        glfwGetMonitorPos(currMonitor.m_Handle,&viewX,&viewY);
        printf("Monitor viewport position: X:%d Y:%d\n",viewX,viewY);

        int WAx = 0, WAy = 0, WAwidth = 0, WAheight = 0;
        glfwGetMonitorWorkarea(currMonitor.m_Handle,&WAx,&WAy,&WAwidth,&WAheight);
        printf("Work area: X:%d Y:%d Width:%d Height:%d\n", WAx,WAy,WAwidth,WAheight);

        int widthMM = 0, heightMM = 0;
        glfwGetMonitorPhysicalSize(currMonitor.m_Handle,&widthMM,&heightMM);
        printf("Monitor Physical Size: Width (mm):%d Height(mm):%d\n",widthMM, heightMM);

        float xScale = 0, yScale = 0;
        glfwGetMonitorContentScale(currMonitor.m_Handle,&xScale,&yScale);
        printf("Content Scale: X:%f, Y:%f\n");

        const GLFWvidmode* vidmode = glfwGetVideoMode(currMonitor.m_Handle);
        printf("Current Vidmode - Width: %d, Height: %d, Red bits: %d, Green bits: %d, Blue bits: %d, Refresh rate(Hz): %d\n", vidmode->width, vidmode->height, vidmode->redBits, vidmode->greenBits, vidmode->blueBits, vidmode->refreshRate);

        int vidmodeCount = 0;
        const GLFWvidmode* vidmodes = glfwGetVideoModes(currMonitor.m_Handle,&vidmodeCount);
        bool printAllVidmodes = false;
        if(printAllVidmodes){
            for(int i = 0; i < vidmodeCount; ++i){
                GLFWvidmode currVidmode = vidmodes[i];
                printf("Vidmode %d - Width: %d, Height: %d, Red bits: %d, Green bits: %d, Blue bits: %d, Refresh rate(Hz): %d\n",i, currVidmode.width, currVidmode.height, currVidmode.redBits, currVidmode.greenBits, currVidmode.blueBits, currVidmode.refreshRate);
            }
        }

        const GLFWgammaramp * gammaRamp = glfwGetGammaRamp(currMonitor.m_Handle);
        bool printGammaRamp = false;
        if(printGammaRamp){
          for(int i = 0; i < gammaRamp->size; ++i){
            printf("Gamma ramp %d: RGB{%d,%d,%d}\n", i, gammaRamp->red[i],gammaRamp->green[i],gammaRamp->blue[i]);
          }
        }

        float gamma = 1.f;
        glfwSetGamma(currMonitor.m_Handle,gamma);

  
        printf("\n");
      }


    }
  
  public:
    MonitorManager(MonitorManager const&) = delete;
    void operator=(MonitorManager const&) = delete;

  private:
    inline static MonitorManager* m_Instance;
    inline static std::mutex m_Mutex;
  //static vector of all monitors
};



//MonitorManager* MonitorManager::getInstance()

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