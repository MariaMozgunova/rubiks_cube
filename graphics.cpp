#include "graphics.h"


void vis::error_callback(int error, const char* description)
{
    throw std::runtime_error(description);
}

void vis::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, width);
}

glm::vec3 vis::choose_rotation(uint8_t cmd) {
    glm::vec3 rotation;

    if (cmd == 5 || cmd == 13 || cmd == 6) {
        rotation = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else if (cmd == 4 || cmd == 12 || cmd == 7) {
        rotation = glm::vec3(-1.0f, 0.0f, 0.0f);
    }
    else if (cmd == 1 || cmd == 2 || cmd == 15) {
        rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    else if (cmd == 0 || cmd == 3 || cmd == 14) {
        rotation = glm::vec3(0.0f, -1.0f, 0.0f);
    }
    else if (cmd == 9 || cmd == 10 || cmd == 17) {
        rotation = glm::vec3(0.0f, 0.0f, 1.0f);
    }
    else {
        rotation = glm::vec3(0.0f, 0.0f, -1.0f);
    }

    return rotation;
}

void vis::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubik's Cube Solver", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }


    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    vertexTransformShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexTransformShader, 1, &vertexTransformShaderSource, NULL);
    glCompileShader(vertexTransformShader);

    fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderBlue, 1, &fragmentShaderSourceBlue, NULL);
    glCompileShader(fragmentShaderBlue);

    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    glCompileShader(fragmentShaderOrange);

    fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderGreen, 1, &fragmentShaderSourceGreen, NULL);
    glCompileShader(fragmentShaderGreen);

    fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderRed, 1, &fragmentShaderSourceRed, NULL);
    glCompileShader(fragmentShaderRed);

    fragmentShaderWhite = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderWhite, 1, &fragmentShaderSourceWhite, NULL);
    glCompileShader(fragmentShaderWhite);

    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);

    shaderProgramBlue = glCreateProgram();
    glAttachShader(shaderProgramBlue, vertexShader);
    glAttachShader(shaderProgramBlue, fragmentShaderBlue);
    glLinkProgram(shaderProgramBlue);

    shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    shaderProgramGreen = glCreateProgram();
    glAttachShader(shaderProgramGreen, vertexShader);
    glAttachShader(shaderProgramGreen, fragmentShaderGreen);
    glLinkProgram(shaderProgramGreen);

    shaderProgramRed = glCreateProgram();
    glAttachShader(shaderProgramRed, vertexShader);
    glAttachShader(shaderProgramRed, fragmentShaderRed);
    glLinkProgram(shaderProgramRed);

    shaderProgramWhite = glCreateProgram();
    glAttachShader(shaderProgramWhite, vertexShader);
    glAttachShader(shaderProgramWhite, fragmentShaderWhite);
    glLinkProgram(shaderProgramWhite);

    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    shaderProgramTransformBlue = glCreateProgram();
    glAttachShader(shaderProgramTransformBlue, vertexTransformShader);
    glAttachShader(shaderProgramTransformBlue, fragmentShaderBlue);
    glLinkProgram(shaderProgramTransformBlue);

    shaderProgramTransformOrange = glCreateProgram();
    glAttachShader(shaderProgramTransformOrange, vertexTransformShader);
    glAttachShader(shaderProgramTransformOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramTransformOrange);

    shaderProgramTransformGreen = glCreateProgram();
    glAttachShader(shaderProgramTransformGreen, vertexTransformShader);
    glAttachShader(shaderProgramTransformGreen, fragmentShaderGreen);
    glLinkProgram(shaderProgramTransformGreen);

    shaderProgramTransformRed = glCreateProgram();
    glAttachShader(shaderProgramTransformRed, vertexTransformShader);
    glAttachShader(shaderProgramTransformRed, fragmentShaderRed);
    glLinkProgram(shaderProgramTransformRed);

    shaderProgramTransformWhite = glCreateProgram();
    glAttachShader(shaderProgramTransformWhite, vertexTransformShader);
    glAttachShader(shaderProgramTransformWhite, fragmentShaderWhite);
    glLinkProgram(shaderProgramTransformWhite);

    shaderProgramTransformYellow = glCreateProgram();
    glAttachShader(shaderProgramTransformYellow, vertexTransformShader);
    glAttachShader(shaderProgramTransformYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramTransformYellow);

    glDeleteShader(vertexShader);
    glDeleteShader(vertexTransformShader);
    glDeleteShader(fragmentShaderBlue);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderGreen);
    glDeleteShader(fragmentShaderRed);
    glDeleteShader(fragmentShaderWhite);
    glDeleteShader(fragmentShaderYellow);


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

    projection = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glEnable(GL_DEPTH_TEST);
}

void vis::visualize_rotation(uint8_t cmd, RubiksCube& cube) {
    glm::vec3 rotation = choose_rotation(cmd);

    for (int a = 0; a <= 90; ++a)
    {
        glClearColor(0.741f, 0.705f, 0.952f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians((float)a), rotation);
        Sleep(DELAY);

        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 9; ++j) {
                unsigned int shader;

                if (cube.need_to_rotate(cmd, i, j)) {
                    switch (cube.name_color(i, j)) {
                    case 0:
                        shader = shaderProgramTransformBlue;
                        break;
                    case 1:
                        shader = shaderProgramTransformOrange;
                        break;
                    case 2:
                        shader = shaderProgramTransformGreen;
                        break;
                    case 3:
                        shader = shaderProgramTransformRed;
                        break;
                    case 4:
                        shader = shaderProgramTransformWhite;
                        break;
                    case 5:
                        shader = shaderProgramTransformYellow;
                        break;
                    };

                    glUseProgram(shader);

                    int transformLoc = glGetUniformLocation(shader, "transform");
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
                }
                else {
                    switch (cube.name_color(i, j)) {
                    case 0:
                        shader = shaderProgramBlue;
                        break;
                    case 1:
                        shader = shaderProgramOrange;
                        break;
                    case 2:
                        shader = shaderProgramGreen;
                        break;
                    case 3:
                        shader = shaderProgramRed;
                        break;
                    case 4:
                        shader = shaderProgramWhite;
                        break;
                    case 5:
                        shader = shaderProgramYellow;
                        break;
                    };

                    glUseProgram(shader);
                }

                int modelLoc = glGetUniformLocation(shader, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

                int projectionLoc = glGetUniformLocation(shader, "projection");
                glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

                int viewLoc = glGetUniformLocation(shader, "view");
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 6 * (9 * i + j), 6);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void vis::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgramBlue);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramGreen);
    glDeleteProgram(shaderProgramRed);
    glDeleteProgram(shaderProgramWhite);
    glDeleteProgram(shaderProgramYellow);
    glDeleteProgram(shaderProgramTransformBlue);
    glDeleteProgram(shaderProgramTransformOrange);
    glDeleteProgram(shaderProgramTransformGreen);
    glDeleteProgram(shaderProgramTransformRed);
    glDeleteProgram(shaderProgramTransformWhite);
    glDeleteProgram(shaderProgramTransformYellow);

    glfwTerminate();
}
