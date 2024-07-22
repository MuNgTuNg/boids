#pragma once
#include <includes.hpp>

#include <string>
#include <vector>
#include <mutex>


#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000

namespace shb{

struct Vector2Di_shb{ 
  int x = 0, y = 0;
};
struct Vector2Df_shb{ 
  float x = 0.f, y = 0.f;
};

struct Vector2Di_WH_shb{ 
  int x = 0, y = 0, width = 0, height = 0;
};

class MonitorManager;
class Monitor{
  friend MonitorManager;

  public:
    Monitor() = default;
    Monitor(GLFWmonitor* handle) : m_Handle(handle){
      m_Name = std::string(glfwGetMonitorName(m_Handle));

      if(m_Handle == glfwGetPrimaryMonitor()){
        m_IsPrimaryMonitor = true;
        m_IsRenderMonitor = true;
      }

      glfwGetMonitorPos(m_Handle,&m_ScreenCoords.x,&m_ScreenCoords.y);
      glfwGetMonitorWorkarea(m_Handle,&m_WorkArea.x,&m_WorkArea.y,&m_WorkArea.width,&m_WorkArea.height);
      glfwGetMonitorPhysicalSize(m_Handle,&m_MonitorPhysicalSizeMM.width,&m_MonitorPhysicalSizeMM.height);
      glfwGetMonitorContentScale(m_Handle,&m_MonitorContentScale.x,&m_MonitorContentScale.y);

      
      const GLFWvidmode* vidmode = glfwGetVideoMode(m_Handle);
      m_Width       = vidmode->width;
      m_Height      = vidmode->height;
      m_RedBits     = vidmode->redBits;
      m_GreenBits   = vidmode->greenBits;
      m_BlueBits    = vidmode->blueBits;
      m_RefreshRate = vidmode->refreshRate;
      
      // //get all video modes
      // int vidmodeCount = 0;
      // const GLFWvidmode* vidmodes = glfwGetVideoModes(currMonitor.m_Handle,&vidmodeCount);
      // bool printAllVidmodes = false;
      // if(printAllVidmodes){
      //     for(int i = 0; i < vidmodeCount; ++i){
      //         GLFWvidmode currVidmode = vidmodes[i];
      //         printf("Vidmode %d - Width: %d, Height: %d, Red bits: %d, Green bits: %d, Blue bits: %d, Refresh rate(Hz): %d\n",i, currVidmode.width, currVidmode.height, currVidmode.redBits, currVidmode.greenBits, currVidmode.blueBits, currVidmode.refreshRate);
      //     }
      // }

      // //get gamma Ramp
      // const GLFWgammaramp * gammaRamp = glfwGetGammaRamp(currMonitor.m_Handle);
      // bool printGammaRamp = false;
      // if(printGammaRamp){
        // for(int i = 0; i < gammaRamp->size; ++i){
          // printf("Gamma ramp %d: RGB{%d,%d,%d}\n", i, gammaRamp->red[i],gammaRamp->green[i],gammaRamp->blue[i]);
        // }
      // }
    }

    void setGamma(float gamma){
      m_Gamma = gamma;
      glfwSetGamma(m_Handle, gamma);
    }

    void printMonitorDetails(){
      printf("Monitor name: %s\n", m_Name.c_str());
      printf("Primary Monitor: %s\n", m_IsPrimaryMonitor ? "true" : "false");
      printf("Monitor viewport position: X:%d Y:%d\n",m_ScreenCoords.x,m_ScreenCoords.y);
      printf("Work area: X:%d Y:%d Width:%d Height:%d\n", m_WorkArea.x,m_WorkArea.y,m_WorkArea.width,m_WorkArea.height);
      printf("Monitor Physical Size: Width (mm):%d Height(mm):%d\n",m_MonitorPhysicalSizeMM.width, m_MonitorPhysicalSizeMM.height);
      printf("Content Scale: X:%f, Y:%f\n",m_MonitorContentScale.x,m_MonitorContentScale.y);
      printf("Current Vidmode - Width: %d, Height: %d, Red bits: %d, Green bits: %d, Blue bits: %d, Refresh rate(Hz): %d\n", m_Width, m_Height, m_RedBits, m_GreenBits, m_BlueBits, m_RefreshRate);
      printf("\n");
    }

    bool isPrimaryMonitor(){
      return m_IsPrimaryMonitor;
    }

    int width() const { return m_Width; }
    int height() const { return m_Height; }
    std::string name() const { return m_Name; } 



  private:
    GLFWmonitor* m_Handle = nullptr;
    bool m_IsPrimaryMonitor = false;
    bool m_IsRenderMonitor = false;
    std::string m_Name = "No Name";

    Vector2Di_shb m_ScreenCoords{};
    Vector2Di_WH_shb m_WorkArea{};
    Vector2Di_WH_shb m_MonitorPhysicalSizeMM{};
    Vector2Df_shb m_MonitorContentScale{};

    int m_Width = 0;
    int m_Height = 0;
    int m_RedBits = 0;
    int m_GreenBits = 0;
    int m_BlueBits = 0;
    int m_RefreshRate = 0;

    float m_Gamma = 1.f;
};


inline void monitorCallback(GLFWmonitor* monitor, int event);

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
    const Monitor getPrimaryMonitor(){
      for(int i = 0; i < m_Monitors.size(); ++i){
        if(m_Monitors[i].isPrimaryMonitor()){
          return m_Monitors[i];
        }
      }
      printf("No monitors plugged in\n");
      return Monitor();
    }
    
    //set the monitor we want to render to
    void setRenderMonitor(int index){
      if(index >= m_Monitors.size()){
        index = m_Monitors.size() -1;
      }
      if(index <= 0){
        index = 0;
      }

      for(int i = 0; i < m_Monitors.size(); ++i){
        m_Monitors[i].m_IsRenderMonitor = false;
      }
      m_Monitors[index].m_IsRenderMonitor = true;

      m_RenderMonitorIndex = index;
    }

    //get the monitor we are currently rendering to 
    int getRenderMonitor(){
      for(int i = 0; i < m_Monitors.size(); ++i){
        if(m_Monitors[i].m_IsRenderMonitor){
          return i;
        }
      }
    }

    const Monitor getMonitor(int index){
      if(index >= m_Monitors.size()){
        index = m_Monitors.size() -1;
      }
      if(index <= 0){
        index = 0;
      }
      return m_Monitors[index];
    }

    void printMonitors(){
      for(int i = 0; i < m_Monitors.size(); ++i){
        m_Monitors[i].printMonitorDetails();
      }
    }

    void refreshList(){
      getMonitors();
    }

  protected:

    MonitorManager(){
      glfwSetMonitorCallback(monitorCallback);
      getMonitors();
    }

    ~MonitorManager(){
      if(m_Instance != nullptr){
        delete m_Instance;
      }
    }
  
  private:
    void getMonitors(){ 
      //get list of all monitors.
      m_Monitors.clear();
      int numMonitors = 0;
      GLFWmonitor** monitorsArr = glfwGetMonitors(&numMonitors);

      for(int i = 0; i < numMonitors; ++i){
        Monitor currMonitor{monitorsArr[i]};
        m_Monitors.push_back(currMonitor);
      }
    }
  
  public:
    MonitorManager(MonitorManager const&) = delete;
    void operator=(MonitorManager const&) = delete;

  private:
    std::vector<Monitor> m_Monitors;
    int m_RenderMonitorIndex = 0;
    inline static MonitorManager* m_Instance;
    inline static std::mutex m_Mutex;
};


inline void monitorCallback(GLFWmonitor* monitor, int event){
  if(event == GLFW_CONNECTED || event == GLFW_DISCONNECTED){
    MonitorManager* monitorManager = MonitorManager::getInstance();
    monitorManager->refreshList();
  }
}



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