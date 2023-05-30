#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    /// ESC 关闭程序
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{

    // 初始化 glfw 
    if (!glfwInit())
    {
        return -1;
    }

    /// 限定 OpenGL 版本为 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /// Mac 特殊设置
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /// 创建 Window 对象
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    /// 只有当 Window 生成成功后，才可以调用，
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /// 设置窗口大小
    glViewport(0, 0, 800, 600);

    /// 监听窗口变化
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        /// 更改下背景色
        glClearColor(0.2f, 0.8f, 0.3f, 1.0f);
        /// 清除颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);

        /// 响应输入
        processInput(window);

        glfwSwapBuffers(window);
        /// 事件监听
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
