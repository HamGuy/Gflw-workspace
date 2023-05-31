#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "commonshader.h"

int main()
{
    if (!glfwInit())
    {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    /// 编译顶点着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    /// 片段着色器 - 计算像素最后的颜色输出
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    /// 着色器程序 - 将多个着色器链接起来
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    /// 激活之后用不到了，删除
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /// 矩形顶点
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    /// 顶点索引，定义绘制顺序(从0开始)
    ///  3-------0
    ///  |       |
    //// 2-------1
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3};

    /// 创建顶点缓冲对象
    unsigned int VBO;
    /// 顶点数组对象
    unsigned int VAO;
    /// 元素缓冲对象
    unsigned int EBO;

    
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&EBO);


    // 绑定顶点数组对象
    glBindVertexArray(VAO); 

    /// 绑定缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /// 跟顶点数据绑定
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /// 绑定元素缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    /// 跟元素缓冲对象数据绑定
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /// ???
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // ???
    glBindVertexArray(0);

    // glViewport(0, 0, 800, 600);

    /// 使用线框图模式绘制
    /// 默认为填充模式 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    /// 绘制过程中可以通过 glPolygonMode 进行切换
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClearColor(0.4f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /// 激活着色器 - 绘制时调用
        glUseProgram(shaderProgram);
        /// 绑定顶点数组对象
        glBindVertexArray(VAO);
        /// 绘制矩形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /// 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}