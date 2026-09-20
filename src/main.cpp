#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

float vertices1[] = {
    -0.2f, -0.2f, 0.0f,
    0.2f, -0.2f, 0.0f,
    -0.0f,  0.2f, 0.0f
};

float vertices2[] = {
    // Position             // Colors
    0.7f,   0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
    0.3f,   0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    0.5f,   0.4f, 0.0f,     0.0f, 0.0f, 1.0f
};

float vertices4[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

#define WIDTH = 800;
#define HEIGHT = 600;

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
    glViewport(0, 0, 800, 600);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    
    // Buffer arrays
    GLuint VAOs[2];
    glGenVertexArrays(2, VAOs);
    
    // Buffer objects
    GLuint VBOs[2];
    glGenBuffers(2, VBOs);    
    
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Shader
    Shader palleteshader = Shader("../../src/shaders/shader.vs", "../../src/shaders/paletteshader.fs");
    Shader pulsingshader = Shader("../../src/shaders/shader.vs", "../../src/shaders/pulsingshader.fs");
    
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1); 
    
    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        pulsingshader.use();
        float timeValue = float(glfwGetTime());
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(pulsingshader.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        int vertexOffset = glGetUniformLocation(pulsingshader.ID, "offset");
        glUniform4f(vertexOffset, -0.7f, 0, 0, 0);

        glBindVertexArray(VAOs[0]);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        palleteshader.use();
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // Swap buffers and check + call events
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
    return 0;
}