#pragma once
#include <includes.hpp>

#include <string>
#include <vector>
#include <mutex>

#include <glm.hpp>


#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000

namespace shb{

template <typename T>
class Vec2{  
  public: 
    T x = 0, y = 0;
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
      glfwGetMonitorWorkarea(m_Handle,&m_WorkAreaPos.x,&m_WorkAreaPos.y,&m_WorkAreaWH.x,&m_WorkAreaWH.y);
      glfwGetMonitorPhysicalSize(m_Handle,&m_PhysicalSize.x,&m_PhysicalSize.y);
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
      printf("Work area: X:%d Y:%d Width:%d Height:%d\n", m_WorkAreaPos.x,m_WorkAreaPos.y,m_WorkAreaWH.x,m_WorkAreaWH.y);
      printf("Monitor Physical Size: Width (mm):%d Height(mm):%d\n",m_PhysicalSize.x, m_PhysicalSize.y);
      printf("Content Scale: X:%f, Y:%f\n",m_MonitorContentScale.x,m_MonitorContentScale.y);
      printf("Current Vidmode - Width: %d, Height: %d, Red bits: %d, Green bits: %d, Blue bits: %d, Refresh rate(Hz): %d\n", m_Width, m_Height, m_RedBits, m_GreenBits, m_BlueBits, m_RefreshRate);
      printf("\n");
    }

    bool const isPrimaryMonitor(){
      return m_IsPrimaryMonitor;
    }
    bool const isRenderMonitor(){
      return m_IsRenderMonitor;
    }

    int width() const { return m_Width; }
    int height() const { return m_Height; }
    int physicalWidth() const { return m_PhysicalSize.x;}
    int physicalHeight() const { return m_PhysicalSize.y;}
    std::string name() const { return m_Name; } 

    int redBits() const { return m_RedBits; }
    int greenBits() const { return m_GreenBits; }
    int blueBits() const { return m_BlueBits; }
    int refreshRate() const { return m_RefreshRate; }
    int gamma() const { return m_Gamma; }
    


  private:
    GLFWmonitor* m_Handle = nullptr;
    bool m_IsPrimaryMonitor = false;
    bool m_IsRenderMonitor = false;
    std::string m_Name = "No Name";

    shb::Vec2<int> m_ScreenCoords{};
    shb::Vec2<int> m_WorkAreaPos{};
    shb::Vec2<int> m_WorkAreaWH{};
    shb::Vec2<int> m_PhysicalSize{};
    shb::Vec2<float> m_MonitorContentScale{};

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

    int numMonitors() { return m_Monitors.size(); }

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



}//namespace shb