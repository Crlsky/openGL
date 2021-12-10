//
//  main.cpp
//  GLFW OpenGL
//
//  Created by Karol on 07/12/2021.
//
// GLEW
//
#define GLEW_STATIC
#include <GL/glew.h>
 
// GLFW OPEN GL library
// IO defices
#include <GLFW/glfw3.h>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// camera position glm generate vector array
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// vertex shader
const char *vertexShaderSource = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "   color = aColor;\n"
    "}\0";

// fragment shader
const char *fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "in vec3 color;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(color, 1.0f);\n"
    "}\0";

// callback resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// callback input
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, const char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow window = glfwCreateWindow(800, 600, "****
*", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if(nullptr == window){
        std::cout << "Filed creating window" << std::endl;
    
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glewInit();
    
    float vertices[] = {
        
// FRONT CUBE WALL
    //  left bottom rectangle   //color
        -0.1f,  -0.2f, 0.0f,    1.0f, 0.0f, 0.0f, // top right
        -0.5f,  -0.2f, 0.0f,    1.0f, 0.0f, 0.0f, // top left
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,// bottom left
        
        -0.1f,  -0.2f, 0.0f,    1.0f, 0.0f, 0.0f,// top right
        -0.5f,  -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,// bottom left
        -0.1f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,// bottom right
        
    // right bottom rectangle
        0.5f,  -0.2f, 0.0f,     1.0f, 0.0f, 0.0f,// top right
        0.1f,  -0.2f, 0.0f,     1.0f, 0.0f, 0.0f,// top left
        0.1f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// bottom left

        0.5f, -0.2f, 0.0f,      1.0f, 0.0f, 0.0f,// top right
        0.1f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// bottom left
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// bottom right
    // top rectangle
        0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// top right
        -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,// top left
        -0.5f, -0.2f, 0.0f,     1.0f, 0.0f, 0.0f,// bottom left
        
        0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,// top right
        -0.5f, -0.2f, 0.0f,     1.0f, 0.0f, 0.0f,// bottom left
        0.5f, -0.2f, 0.0f,      1.0f, 0.0f, 0.0f,// bottom right
        
// LEFT CUBE WALL
        -0.5f, 0.5f, -0.5f,     1.0f, 0.0f, 0.0f,// top left
        -0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// top rigtt
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,// bottom left
        
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,// bottom left
        -0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// top rigtt
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,// bottom right
        
// RIGHT CUBE WALL
        0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,// top left
        0.5f, 0.5f, -0.5f,      1.0f, 0.0f, 0.0f,// top right
        0.5, -0.5, 0,           1.0f, 0.0f, 0.0f,// bottom left

        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// bottom left
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,// bottom right
        0.5f, 0.5f, -0.5f,      1.0f, 0.0f, 0.0f,// top right
// ROOF
        // front
        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f,// peak
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,// bottom left
        0.5f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f,// bottom rigth
        
        // left
        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f,// peak
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 0.0f,// bottom left
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,// bottom rigth
        
        // right
        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f,// peak
        0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,// bottom left
        0.5f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f,// bottom rigth
        
    };
    
    // VERTEX SHADER
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    // attach shader to obj and compile shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // FRAGMENT SHADER
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // SHADER PROGRAM
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glUseProgram(shaderProgram);
    
    // Deleting object bc it is linked into shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // VBO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color atribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // render loop
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glfwPollEvents();
        glClearColor(0.9f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 model = glm::mat4(1.0f);

        int projectionLocation = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        int viewLocation = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        int modelLocation = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
                
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    
    return 0;
}