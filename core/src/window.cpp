#include <window.hpp>

namespace shb{
// Window::Window( const std::string& title = "No Title", int width = WIN_WIDTH, int height = WIN_HEIGHT, int monitor = 0) : m_Width(width), m_Height(height), m_Title(title) {
        
//     setDefaultWindowHints();
    
//     //generate window handle
//     m_Handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
//     if (!m_Handle){
//         printf("Window creation error\n");
//         glfwTerminate();
//     }

//     populateWindowInfo();

//     glfwMakeContextCurrent(m_Handle);
//     m_ContextCurrent = true;
//     gladLoadGL();

//     glViewport( 0, 0, width, height);
//     glClearColor(0,0,0,255);
//     //glEnable              ( GL_DEBUG_OUTPUT );
//     //glDebugMessageCallback( MessageCallback, 0 );
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
//     glEnable(GL_DEPTH_TEST);

//     //Window icon
//     GLFWimage image[1];
//     image[0].pixels = stbi_load("../resources/textures/icon.png", &image[0].width, &image[0].height, 0, 4); 
//     if(image->pixels){
//         glfwSetWindowIcon(m_Handle, 1, image);
//         stbi_image_free(image[0].pixels); 
//     }
//     else{
//         printf("No window icon! Add a .png titled 'icon.png' into resources/textures/\n");
//     }
// }
}//namespace shb