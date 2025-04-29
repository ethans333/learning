#include "camera.h"

Camera::Camera(int width, int height)
{
    lastX = width / 2.0f;
    lastY = height / 2.0f;

    view = glm::lookAt(
        position,           // World Space
        glm::vec3(0, 0, 0), // Looks at
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void Camera::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity;

    lastX = xpos;
    lastY = ypos;

    yaw += xoffset;
    pitch += yoffset;

    // Avoid Flipping
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    UpdateView();
}

void Camera::UpdateView()
{
    view = glm::lookAt(
        position,         // World Space
        position + front, // Looks at
        cameraUp          // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void Camera::MouseCallbackDispatcher(GLFWwindow *window, double xpos, double ypos)
{
    auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
    if (camera)
        camera->MouseCallback(window, xpos, ypos);
}

void Camera::ProcessInput(GLFWwindow *window, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;

    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;

    // Move left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, cameraUp)) * velocity;

    // Move right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, cameraUp)) * velocity;

    // Move up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += cameraUp * velocity;

    UpdateView();
}