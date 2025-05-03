#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "camera.h"
#include "shape.h"
#include "objReader.h"
using namespace glm;

#pragma once

class Renderer
{
private:
    int width = 1920, height = 1080;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    GLFWwindow *window;

    std::vector<Shape *> shapes;

    ObjReader objReader = ObjReader();

    void DeleteShapes();

public:
    Camera camera = Camera(width, height);
    GLuint VAO;

    Renderer();
    ~Renderer();

    void Draw();
    GLFWwindow *GetWindow();
    void AddShape(Shape *shape);
    Shape *LoadShape(std::string fileName);
};