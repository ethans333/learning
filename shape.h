#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "camera.h"

#pragma once

class Shape
{
private:
    size_t nVertices;
    size_t nColors;

    GLuint *VAO;
    GLuint modelBuffer;
    GLuint shaderProgram;

public:
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::f32 scale = 1.0f;

    Shape(GLuint *VAO, std::vector<GLfloat> vertices);
    ~Shape();

    void Draw(Camera *camera);
    void SetPosition(glm::vec3 position);
    void SetScale(glm::f32 scale);
};