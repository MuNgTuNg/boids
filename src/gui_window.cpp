#include <gui.hpp>
namespace shb{
//variables for window
int windowXY[2] = {0,0};
int windowXYLimit[4] = {0,0,0,0};
int windowXYPos[2] = {0,0};

void windowControlsGUI(shb::Window* window){
    assert(window != nullptr && "Passed null window to gui windowControls\n");
    if (ImGui::CollapsingHeader("Window")){
        //info
        ImGui::Text("Width: %d\nHeight: %d", window->width(), window->height());
        ImGui::Text("Pos X: %d\nPosY: %d", window->pos().x, window->pos().y);
        ImGui::Text("FrameBuffer Width: %d\nFrameBuffer Height: %d", window->frameBufferWidth(), window->frameBufferHeight());

        //flags?
        bool isResizablePrev = window->m_IsResizable;
        ImGui::Checkbox("Resizable?",&window->m_IsResizable);
        if(isResizablePrev != window->m_IsResizable){
            glfwSetWindowAttrib(window->handle(), GLFW_RESIZABLE, window->m_IsResizable);
        }

        bool isDecoratedPrev = window->m_IsDecorated;
        ImGui::Checkbox("Decorate Window?",&window->m_IsDecorated);
        if(isDecoratedPrev != window->m_IsDecorated){
           glfwWindowHint(GLFW_DECORATED, window->m_IsDecorated);
           recreateWindow = true;
        }

        
        if (ImGui::CollapsingHeader("Sizing")){

            ImGui::DragInt2("Resize XY", windowXY);
            if(ImGui::Button("Press to set size")){
                window->setSize(windowXY[0],windowXY[1]);
            }
            ImGui::Separator();

            ImGui::DragInt4("Size limit XY min, XY max", windowXYLimit);
            
            if(ImGui::Button("Press to set limit")){
                window->limitSize(windowXYLimit[0],windowXYLimit[1],windowXYLimit[2],windowXYLimit[3]);
            }
            ImGui::Separator();
        }


        if (ImGui::CollapsingHeader("Position")){
            ImGui::DragInt2("Pos XY", windowXYPos);
            if(ImGui::Button("Press to set pos")){
                window->setPos(windowXYPos[0],windowXYPos[1]);
            }
            ImGui::Separator();
        }
           
        //set to be recreated at end of gui frame
        if(ImGui::Button("Reload Window")){
           recreateWindow = true;
        }
        
    }
}
}//namespace shb