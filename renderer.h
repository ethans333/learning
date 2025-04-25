#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "shape.h"
using namespace glm;

class Renderer
{
private:
    GLFWwindow *window;
    Camera camera;
    Shape *shapes;

public:
    Renderer(Shape *shapes);
    ~Renderer();
    void Draw();
};