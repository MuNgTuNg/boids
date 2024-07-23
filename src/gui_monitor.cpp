#include <gui.hpp>
namespace shb{
void printMonitorDetailsGUI(){
    MonitorManager* monitorManager = MonitorManager::getInstance(); //temporary
    
    if (ImGui::CollapsingHeader("Monitors")){
        for( int i = 0; i < monitorManager->numMonitors(); ++i){
            Monitor currentMonitor = monitorManager->getMonitor(i);
            ImGui::Text("Monitor name: %s\n", currentMonitor.name().c_str());
            ImGui::Text("Monitor index: %d",i);
            ImGui::Text("Resolution: %dx%d\n", currentMonitor.width(), currentMonitor.height());
            ImGui::Text("Primary monitor? %s", currentMonitor.isPrimaryMonitor() ? "True" : "False");
            ImGui::Text("Render monitor? %s", currentMonitor.isRenderMonitor() ? "True" : "False");
            ImGui::Text("Physical Size (mm): {%d,%d}", currentMonitor.physicalWidth(), currentMonitor.physicalHeight());
            ImGui::Text("Current Vidmode:\n  Width: %d\n  Height: %d\n  Red bits: %d\n  Green bits: %d\n  Blue bits: %d\n  Refresh rate: %dHz\n", currentMonitor.width(), currentMonitor.height(), currentMonitor.redBits(), currentMonitor.greenBits(), currentMonitor.blueBits(), currentMonitor.refreshRate());
            ImGui::Separator();
        }
    }
    monitorManager = nullptr;
}
}//namespace shb