#include <window.hpp>

namespace shb{

Window::Window( const std::string& title, int width, int height, int monitor) : m_Width(width), m_Height(height), m_Title(title){
    setDefaultWindowHints();
    initWindow();
}

void Window::initWindow(){
    //generate window handle
    m_Handle = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if (!m_Handle){
        printf("Window creation error\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_Handle);
    m_ContextCurrent = true;
    gladLoadGL();

    setDefaultWindowDetails();
    populateWindowInfoAttributes();
}



void Window::recreateWindow(){
    GLFWwindow* newWindow = nullptr;
    newWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if (!newWindow){
        printf("Window creation error\n");
        glfwTerminate();
    }
    if(m_Handle){
        glfwDestroyWindow(m_Handle);
        m_Handle = nullptr;
    }

    m_Handle = newWindow;
    glfwMakeContextCurrent(m_Handle);

    setDefaultWindowDetails();
}


void Window::setDefaultWindowDetails(){

    glfwGetFramebufferSize(m_Handle, &m_FrameBufferWidth, &m_FrameBufferHeight);
    glViewport( 0, 0, m_FrameBufferWidth, m_FrameBufferHeight); 

    glClearColor(0,0,0,255);
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


void Window::setDefaultWindowHints(){
    //set window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
}


void Window::populateWindowInfoAttributes(){ //https://www.glfw.org/docs/3.3/window_guide.html#window_attribs
    m_IsDecorated = glfwGetWindowAttrib(m_Handle, GLFW_DECORATED);
    m_IsResizable = glfwGetWindowAttrib(m_Handle, GLFW_RESIZABLE);
}


}//namespace shb