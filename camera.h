#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>

#pragma once

class Camera
{
private:
    float sensitivity = 0.1f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    bool firstMouse = true;
    float lastX;
    float lastY;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    float movementSpeed = 1;
    glm::vec3 cameraUp = glm::vec3(0, 1, 0);

public:
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::mat4 view;
    glm::mat4 projection;
    Camera(int, int);
    static void MouseCallbackDispatcher(GLFWwindow *window, double xpos, double ypos);
    void MouseCallback(GLFWwindow *window, double xpos, double ypos);
    void ProcessInput(GLFWwindow *window, float deltaTime);
    void UpdateView();
};