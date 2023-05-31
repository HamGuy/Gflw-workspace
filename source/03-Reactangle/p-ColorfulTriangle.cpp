#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "commonshader.h"

int createVertexShader()
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
        return -1;
    }

    return vertexShader;
}

int createFragmentShader(const char *shaderSource)
{
    unsigned int fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentShader, 1, &shaderSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    return fragmentShader;
}

int checkIfProgramLinked(unsigned int shaderProgram)
{
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }
    return 0;
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
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

    unsigned int vertexShader1 = createVertexShader();
    unsigned int vertexShader2 = createVertexShader();
    unsigned int fragmentShader1 = createFragmentShader(fragmentShaderSource);
    unsigned int fragmentShader2 = createFragmentShader(fragmentShaderSource2);

    if (vertexShader1 == -1  || vertexShader2 == -1 || fragmentShader1 == -1 || fragmentShader2 == -1)
    {
        std::cout << "Failed to create shader" << std::endl;
        return -1;
    }

    unsigned int shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader1);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    if (checkIfProgramLinked(shaderProgram1) == -1)
    {
        std::cout << "Failed to link program1" << std::endl;
        return -1;
    }

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    if (checkIfProgramLinked(shaderProgram2) == -1)
    {
        std::cout << "Failed to link program2" << std::endl;
        return -1;
    }

    glDeleteShader(vertexShader1);
    glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    float vertices1[] = {
        -0.5f, -0.5f, 0.0f,
        -0.25f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f};

    float vertices2[] = {
        0.0f, -0.5f, 0.0f,
        0.25f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};

    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    unsigned int VBO2, VAO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // unsigned int VBO1;
    // glGenBuffers(1, &VBO1);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // unsigned int VBO2;
    // glGenBuffers(1, &VBO2);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // unsigned int VAO1;
    // glGenVertexArrays(1, &VAO1);
    // glBindVertexArray(VAO1);

    // unsigned int VAO2;
    // glGenVertexArrays(1, &VAO2);
    // glBindVertexArray(VAO2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);
    glfwTerminate();
    return 0;
}
