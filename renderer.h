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
using namespace glm;

class Renderer
{
private:
    int width = 1024, height = 768;
    GLFWwindow *window;
    std::vector<Shape> shapes;

public:
    Camera camera;

    Renderer();
    ~Renderer();

    void Draw();
    Shape *CreateShape(GLfloat *g_vertex_buffer_data, GLfloat *g_color_buffer_data, size_t sizeVertices, size_t sizeColors);
    GLFWwindow *GetWindow();
};