#include "camera.h"

void Camera::LookAt(glm::vec3 eye, glm::vec3 center)
{
    view = glm::lookAt(eye, center, glm::vec3(0, 1, 0));
}