#pragma once

#include <shb_core.hpp>

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace shb{


void printMonitorDetailsGUI();

inline int initGuiOpenGL3(GLFWwindow* window, std::string version){
    int res = 1;
    if(!ImGui::CreateContext()){
        printf("Failed to create ImGUI context!\n");
        res = -1;
    }
    if(!ImGui_ImplOpenGL3_Init(version.c_str())){
        printf("Failed to init ImGUI for opengl3!\n");
        res = -1;
    }
    if(!ImGui_ImplGlfw_InitForOpenGL(window, true)){
        printf("Failed to init ImGUI for glfw!\n");
        res = -1;
    }
    return res;
}

inline void guiFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Debug", nullptr);
    ImGui::SetNextWindowSize(ImVec2(500,500));


    printMonitorDetailsGUI();


    //ImGui::ShowDemoWindow();
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


inline void shutdownGUIOpenGL3(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

}//namespace shb