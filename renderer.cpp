#include "renderer.h"

Renderer::Renderer(Shape *shapes)
{
    this->shapes = shapes;

    if (!glfwInit())
        fprintf(stderr, "Failed to initialize GLFW\n");

    glewExperimental = true;

    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);

    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        fprintf(stderr, "Failed to initialize GLEW\n");

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

Renderer::~Renderer()
{
    glfwTerminate();
}

void Renderer::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw Shapes
    for (int i = 0; i < sizeof(shapes) / sizeof(Shape); i++)
    {
        shapes[i].Draw(&camera);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}