#pragma once
#define GL_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>
#include <iostream>
#include "cube.h"


static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 800;
static const unsigned int DELAY = 20;

static const char* vertexTransformShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * transform * vec4(aPos, 1.0);\n"
"}\0";
static const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\0";

static const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.141f, 0.568f, 0.921f, 1.0f);\n"
"}\n\0";

static const char* fragmentShaderSourceBlue = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.337f, 0.741f, 0.901f, 1.0f);\n"
"}\n\0";
static const char* fragmentShaderSourceOrange = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.96f, 0.576f, 0.098f, 1.0f);\n"
"}\n\0";
static const char* fragmentShaderSourceGreen = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.431f, 0.850f, 0.407f, 1.0f);\n"
"}\n\0";
static const char* fragmentShaderSourceRed = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.929f, 0.270f, 0.368f, 1.0f);\n"
"}\n\0";
static const char* fragmentShaderSourceWhite = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.996f, 0.949f, 0.905f, 1.0f);\n"
"}\n\0";
static const char* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.984f, 0.964f, 0.439f, 1.0f);\n"
"}\n\0";

static const float vertices[] = {
    // F facelet
    // 0
    -0.6f, 0.6f, 0.6f,
    -0.2f, 0.6f, 0.6f,
    -0.2f, 0.2f, 0.6f,
    -0.6f, 0.6f, 0.6f,
    -0.2f, 0.2f, 0.6f,
    -0.6f, 0.2f, 0.6f,
    // 1
    -0.2f, 0.6f, 0.6f,
    0.2f, 0.6f, 0.6f,
    0.2f, 0.2f, 0.6f,
    -0.2f, 0.6f, 0.6f,
    0.2f, 0.2f, 0.6f,
    -0.2f, 0.2f, 0.6f,
    // 2
    0.2f, 0.6f, 0.6f,
    0.6f, 0.6f, 0.6f,
    0.6f, 0.2f, 0.6f,
    0.2f, 0.6f, 0.6f,
    0.6f, 0.2f, 0.6f,
    0.2f, 0.2f, 0.6f,
    // 3
    0.2f, 0.2f, 0.6f,
    0.6f, 0.2f, 0.6f,
    0.6f, -0.2f, 0.6f,
    0.2f, 0.2f, 0.6f,
    0.6f, -0.2f, 0.6f,
    0.2f, -0.2f, 0.6f,
    // 4
    0.6f, -0.6f, 0.6f,
    0.2f, -0.6f, 0.6f,
    0.2f, -0.2f, 0.6f,
    0.6f, -0.6f, 0.6f,
    0.2f, -0.2f, 0.6f,
    0.6f, -0.2f, 0.6f,
    // 5
    0.2f, -0.6f, 0.6f,
    -0.2f, -0.6f, 0.6f,
    -0.2f, -0.2f, 0.6f,
    0.2f, -0.6f, 0.6f,
    -0.2f, -0.2f, 0.6f,
    0.2f, -0.2f, 0.6f,
    // 6
    -0.2f, -0.6f, 0.6f,
    -0.6f, -0.6f, 0.6f,
    -0.6f, -0.2f, 0.6f,
    -0.2f, -0.6f, 0.6f,
    -0.6f, -0.2f, 0.6f,
    -0.2f, -0.2f, 0.6f,
    // 7
    -0.6f, 0.2f, 0.6f,
    -0.2f, 0.2f, 0.6f,
    -0.2f, -0.2f, 0.6f,
    -0.6f, 0.2f, 0.6f,
    -0.2f, -0.2f, 0.6f,
    -0.6f, -0.2f, 0.6f,
    // 8
    -0.2f, 0.2f, 0.6f,
    0.2f, 0.2f, 0.6f,
    0.2f, -0.2f, 0.6f,
    -0.2f, 0.2f, 0.6f,
    0.2f, -0.2f, 0.6f,
    -0.2f, -0.2f, 0.6f,


    // R facelet
    //0
    0.6f, 0.6f, 0.6f,
    0.6f, 0.6f, 0.2f,
    0.6f, 0.2f, 0.2f,
    0.6f, 0.6f, 0.6f,
    0.6f, 0.2f, 0.2f,
    0.6f, 0.2f, 0.6f,
    // 1
    0.6f, 0.6f, 0.2f,
    0.6f, 0.6f, -0.2f,
    0.6f, 0.2f, -0.2f,
    0.6f, 0.6f, 0.2f,
    0.6f, 0.2f, -0.2f,
    0.6f, 0.2f, 0.2f,
    // 2
    0.6f, 0.6f, -0.2f,
    0.6f, 0.6f, -0.6f,
    0.6f, 0.2f, -0.6f,
    0.6f, 0.6f, -0.2f,
    0.6f, 0.2f, -0.6f,
    0.6f, 0.2f, -0.2f,
    // 3
    0.6f, 0.2f, -0.2f,
    0.6f, 0.2f, -0.6f,
    0.6f, -0.2f, -0.6f,
    0.6f, 0.2f, -0.2f,
    0.6f, -0.2f, -0.6f,
    0.6f, -0.2f, -0.2f,
    // 4
    0.6f, -0.6f, -0.6f,
    0.6f, -0.6f, -0.2f,
    0.6f, -0.2f, -0.2f,
    0.6f, -0.6f, -0.6f,
    0.6f, -0.2f, -0.2f,
    0.6f, -0.2f, -0.6f,
    // 5
    0.6f, -0.6f, -0.2f,
    0.6f, -0.6f, 0.2f,
    0.6f, -0.2f, 0.2f,
    0.6f, -0.6f, -0.2f,
    0.6f, -0.2f, 0.2f,
    0.6f, -0.2f, -0.2f,
    // 6
    0.6f, -0.6f, 0.2f,
    0.6f, -0.6f, 0.6f,
    0.6f, -0.2f, 0.6f,
    0.6f, -0.6f, 0.2f,
    0.6f, -0.2f, 0.6f,
    0.6f, -0.2f, 0.2f,
    // 7
    0.6f, -0.2f, 0.2f,
    0.6f, -0.2f, 0.6f,
    0.6f, 0.2f, 0.6f,
    0.6f, -0.2f, 0.2f,
    0.6f, 0.2f, 0.6f,
    0.6f, 0.2f, 0.2f,
    // 8
    0.6f, 0.2f, 0.2f,
    0.6f, 0.2f, -0.2f,
    0.6f, -0.2f, -0.2f,
    0.6f, 0.2f, 0.2f,
    0.6f, -0.2f, -0.2f,
    0.6f, -0.2f, 0.2f,


    // B facelet
    // 0
    0.2f, 0.6f, -0.6f,
    0.6f, 0.6f, -0.6f,
    0.6f, 0.2f, -0.6f,
    0.2f, 0.6f, -0.6f,
    0.6f, 0.2f, -0.6f,
    0.2f, 0.2f, -0.6f,
    // 1
    -0.2f, 0.6f, -0.6f,
    0.2f, 0.6f, -0.6f,
    0.2f, 0.2f, -0.6f,
    -0.2f, 0.6f, -0.6f,
    0.2f, 0.2f, -0.6f,
    -0.2f, 0.2f, -0.6f,
    // 2
    -0.6f, 0.6f, -0.6f,
    -0.2f, 0.6f, -0.6f,
    -0.2f, 0.2f, -0.6f,
    -0.6f, 0.6f, -0.6f,
    -0.2f, 0.2f, -0.6f,
    -0.6f, 0.2f, -0.6f,
    // 3
    -0.6f, 0.2f, -0.6f,
    -0.2f, 0.2f, -0.6f,
    -0.2f, -0.2f, -0.6f,
    -0.6f, 0.2f, -0.6f,
    -0.2f, -0.2f, -0.6f,
    -0.6f, -0.2f, -0.6f,
    // 4
    -0.2f, -0.6f, -0.6f,
    -0.6f, -0.6f, -0.6f,
    -0.6f, -0.2f, -0.6f,
    -0.2f, -0.6f, -0.6f,
    -0.6f, -0.2f, -0.6f,
    -0.2f, -0.2f, -0.6f,
    // 5
    0.2f, -0.6f, -0.6f,
    -0.2f, -0.6f, -0.6f,
    -0.2f, -0.2f, -0.6f,
    0.2f, -0.6f, -0.6f,
    -0.2f, -0.2f, -0.6f,
    0.2f, -0.2f, -0.6f,
    // 6
    0.6f, -0.6f, -0.6f,
    0.2f, -0.6f, -0.6f,
    0.2f, -0.2f, -0.6f,
    0.6f, -0.6f, -0.6f,
    0.2f, -0.2f, -0.6f,
    0.6f, -0.2f, -0.6f,
    // 7
    0.2f, 0.2f, -0.6f,
    0.6f, 0.2f, -0.6f,
    0.6f, -0.2f, -0.6f,
    0.2f, 0.2f, -0.6f,
    0.6f, -0.2f, -0.6f,
    0.2f, -0.2f, -0.6f,
    // 8
    -0.2f, 0.2f, -0.6f,
    0.2f, 0.2f, -0.6f,
    0.2f, -0.2f, -0.6f,
    -0.2f, 0.2f, -0.6f,
    0.2f, -0.2f, -0.6f,
    -0.2f, -0.2f, -0.6f,


    // L facelet
    // 0
    -0.6f, 0.6f, -0.2f,
    -0.6f, 0.6f, -0.6f,
    -0.6f, 0.2f, -0.6f,
    -0.6f, 0.6f, -0.2f,
    -0.6f, 0.2f, -0.6f,
    -0.6f, 0.2f, -0.2f,
    // 1
    -0.6f, 0.6f, 0.2f,
    -0.6f, 0.6f, -0.2f,
    -0.6f, 0.2f, -0.2f,
    -0.6f, 0.6f, 0.2f,
    -0.6f, 0.2f, -0.2f,
    -0.6f, 0.2f, 0.2f,
    // 2
    -0.6f, 0.6f, 0.6f,
    -0.6f, 0.6f, 0.2f,
    -0.6f, 0.2f, 0.2f,
    -0.6f, 0.6f, 0.6f,
    -0.6f, 0.2f, 0.2f,
    -0.6f, 0.2f, 0.6f,
    // 3
    -0.6f, -0.2f, 0.2f,
    -0.6f, -0.2f, 0.6f,
    -0.6f, 0.2f, 0.6f,
    -0.6f, -0.2f, 0.2f,
    -0.6f, 0.2f, 0.6f,
    -0.6f, 0.2f, 0.2f,
    // 4
    -0.6f, -0.6f, 0.2f,
    -0.6f, -0.6f, 0.6f,
    -0.6f, -0.2f, 0.6f,
    -0.6f, -0.6f, 0.2f,
    -0.6f, -0.2f, 0.6f,
    -0.6f, -0.2f, 0.2f,
    // 5
    -0.6f, -0.6f, -0.2f,
    -0.6f, -0.6f, 0.2f,
    -0.6f, -0.2f, 0.2f,
    -0.6f, -0.6f, -0.2f,
    -0.6f, -0.2f, 0.2f,
    -0.6f, -0.2f, -0.2f,
    // 6
    -0.6f, -0.6f, -0.6f,
    -0.6f, -0.6f, -0.2f,
    -0.6f, -0.2f, -0.2f,
    -0.6f, -0.6f, -0.6f,
    -0.6f, -0.2f, -0.2f,
    -0.6f, -0.2f, -0.6f,
    // 7
    -0.6f, 0.2f, -0.2f,
    -0.6f, 0.2f, -0.6f,
    -0.6f, -0.2f, -0.6f,
    -0.6f, 0.2f, -0.2f,
    -0.6f, -0.2f, -0.6f,
    -0.6f, -0.2f, -0.2f,
    // 8
    -0.6f, 0.2f, 0.2f,
    -0.6f, 0.2f, -0.2f,
    -0.6f, -0.2f, -0.2f,
    -0.6f, 0.2f, 0.2f,
    -0.6f, -0.2f, -0.2f,
    -0.6f, -0.2f, 0.2f,


    // U facelet
    // 0
    -0.6f, 0.6f, -0.6f,
    -0.2f, 0.6f, -0.6f,
    -0.2f, 0.6f, -0.2f,
    -0.6f, 0.6f, -0.6f,
    -0.2f, 0.6f, -0.2f,
    -0.6f, 0.6f, -0.2f,
    // 1
    -0.2f, 0.6f, -0.6f,
    0.2f, 0.6f, -0.6f,
    0.2f, 0.6f, -0.2f,
    -0.2f, 0.6f, -0.6f,
    0.2f, 0.6f, -0.2f,
    -0.2f, 0.6f, -0.2f,
    // 2
    0.6f, 0.6f, -0.6f,
    0.6f, 0.6f, -0.2f,
    0.2f, 0.6f, -0.2f,
    0.6f, 0.6f, -0.6f,
    0.2f, 0.6f, -0.2f,
    0.2f, 0.6f, -0.6f,
    // 3
    0.2f, 0.6f, -0.2f,
    0.6f, 0.6f, -0.2f,
    0.6f, 0.6f, 0.2f,
    0.2f, 0.6f, -0.2f,
    0.6f, 0.6f, 0.2f,
    0.2f, 0.6f, 0.2f,
    // 4
    0.6f, 0.6f, 0.6f,
    0.2f, 0.6f, 0.6f,
    0.2f, 0.6f, 0.2f,
    0.6f, 0.6f, 0.6f,
    0.2f, 0.6f, 0.2f,
    0.6f, 0.6f, 0.2f,
    // 5
    0.2f, 0.6f, 0.6f,
    -0.2f, 0.6f, 0.6f,
    -0.2f, 0.6f, 0.2f,
    0.2f, 0.6f, 0.6f,
    -0.2f, 0.6f, 0.2f,
    0.2f, 0.6f, 0.2f,
    // 6
    -0.6f, 0.6f, 0.6f,
    -0.6f, 0.6f, 0.2f,
    -0.2f, 0.6f, 0.2f,
    -0.6f, 0.6f, 0.6f,
    -0.2f, 0.6f, 0.2f,
    -0.2f, 0.6f, 0.6f,
    // 7
    -0.2f, 0.6f, 0.2f,
    -0.6f, 0.6f, 0.2f,
    -0.6f, 0.6f, -0.2f,
    -0.2f, 0.6f, 0.2f,
    -0.6f, 0.6f, -0.2f,
    -0.2f, 0.6f, -0.2f,
    // 8
    -0.2f, 0.6f, -0.2f,
    0.2f, 0.6f, -0.2f,
    0.2f, 0.6f, 0.2f,
    -0.2f, 0.6f, -0.2f,
    0.2f, 0.6f, 0.2f,
    -0.2f, 0.6f, 0.2f,


    // D facelet
    // 0
    -0.6f, -0.6f, 0.6f,
    -0.6f, -0.6f, 0.2f,
    -0.2f, -0.6f, 0.2f,
    -0.6f, -0.6f, 0.6f,
    -0.2f, -0.6f, 0.2f,
    -0.2f, -0.6f, 0.6f,
    // 1
    0.2f, -0.6f, 0.6f,
    -0.2f, -0.6f, 0.6f,
    -0.2f, -0.6f, 0.2f,
    0.2f, -0.6f, 0.6f,
    -0.2f, -0.6f, 0.2f,
    0.2f, -0.6f, 0.2f,
    // 2
    0.6f, -0.6f, 0.6f,
    0.2f, -0.6f, 0.6f,
    0.2f, -0.6f, 0.2f,
    0.6f, -0.6f, 0.6f,
    0.2f, -0.6f, 0.2f,
    0.6f, -0.6f, 0.2f,
    // 3
    0.2f, -0.6f, -0.2f,
    0.6f, -0.6f, -0.2f,
    0.6f, -0.6f, 0.2f,
    0.2f, -0.6f, -0.2f,
    0.6f, -0.6f, 0.2f,
    0.2f, -0.6f, 0.2f,
    // 4
    0.6f, -0.6f, -0.6f,
    0.6f, -0.6f, -0.2f,
    0.2f, -0.6f, -0.2f,
    0.6f, -0.6f, -0.6f,
    0.2f, -0.6f, -0.2f,
    0.2f, -0.6f, -0.6f,
    // 5
    -0.2f, -0.6f, -0.6f,
    0.2f, -0.6f, -0.6f,
    0.2f, -0.6f, -0.2f,
    -0.2f, -0.6f, -0.6f,
    0.2f, -0.6f, -0.2f,
    -0.2f, -0.6f, -0.2f,
    // 6
    -0.6f, -0.6f, -0.6f,
    -0.2f, -0.6f, -0.6f,
    -0.2f, -0.6f, -0.2f,
    -0.6f, -0.6f, -0.6f,
    -0.2f, -0.6f, -0.2f,
    -0.6f, -0.6f, -0.2f,
    // 7
    -0.2f, -0.6f, 0.2f,
    -0.6f, -0.6f, 0.2f,
    -0.6f, -0.6f, -0.2f,
    -0.2f, -0.6f, 0.2f,
    -0.6f, -0.6f, -0.2f,
    -0.2f, -0.6f, -0.2f,
    // 8
    -0.2f, -0.6f, -0.2f,
    0.2f, -0.6f, -0.2f,
    0.2f, -0.6f, 0.2f,
    -0.2f, -0.6f, -0.2f,
    0.2f, -0.6f, 0.2f,
    -0.2f, -0.6f, 0.2f,
};

static GLFWwindow* window;
static unsigned int vertexShader, vertexTransformShader, fragmentShaderBlue,
fragmentShaderOrange, fragmentShaderGreen, fragmentShaderRed, fragmentShaderWhite,
fragmentShaderYellow, shaderProgramBlue, shaderProgramOrange, shaderProgramGreen,
shaderProgramRed, shaderProgramWhite, shaderProgramYellow, shaderProgramTransformBlue,
shaderProgramTransformOrange, shaderProgramTransformGreen, shaderProgramTransformRed,
shaderProgramTransformWhite, shaderProgramTransformYellow;

static unsigned int VBO, VAO;

static glm::mat4 view, projection, model;

namespace vis {
    void error_callback(int error, const char* description);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    glm::vec3 choose_rotation(uint8_t cmd);
    void init();
    void visualize_rotation(uint8_t cmd, RubiksCube& cube);
    void destroy();
}