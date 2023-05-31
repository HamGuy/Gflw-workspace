#include <glad/glad.h>
#include <iostream>
#include "commonshader.h"

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

    unsigned int vertexShader = createVertexShader();
    unsigned int fragmentShader = createFragmentShader(fragmentShaderSource);
    unsigned int fragmentShader2 = createFragmentShader(fragmentShaderSource2);

    unsigned int shaderProgram = createProgram(vertexShader, fragmentShader);
    unsigned int shaderProgram2 = createProgram(vertexShader, fragmentShader2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);

    float vertices1[] = {
        0.0f, -0.5f, 0.0f,  // left
        -0.25f, 0.5f, 0.0f, // right
        -0.5f, -0.5f, 0.0f, // top
    };

    float vertices2[] = {
        0.0f, -0.5f, 0.0f,
        0.25f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};

    float *vertices[] = {
        vertices1, vertices2};

    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    //     int count = sizeof(vertices)/sizeof(float*);
    // for (int i = 0; i < count; i++)
    // {
    //     glBindVertexArray(VAO[i]);
    //     glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices[i], GL_STATIC_DRAW);
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //     glEnableVertexAttribArray(0);
    // }

    unsigned long verticesSize = sizeof(vertices1);
    int count = sizeof(vertices) / sizeof(float *);
    for (int i = 0; i < count; i++)
    {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices[i], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }
    // glBindVertexArray(VAO[0]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    // unsigned long  verticesSize = sizeof(vertices1);
    // glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices1, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // glBindVertexArray(VAO[1]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(2, VBO);
    glDeleteVertexArrays(2, VAO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);
    glfwTerminate();
    return 0;
}
