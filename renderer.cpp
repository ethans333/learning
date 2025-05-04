#include "renderer.h"

Renderer::Renderer()
{
    if (!glfwInit())
        fprintf(stderr, "Failed to initialize GLFW\n");

    glewExperimental = true;

    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Tutorial 01", NULL, NULL);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

    if (glewInit() != GLEW_OK)
        fprintf(stderr, "Failed to initialize GLEW\n");

    // V-Sync ON
    glfwSwapInterval(1);

    // Input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetWindowUserPointer(window, &camera);
    glfwSetCursorPosCallback(window, Camera::MouseCallbackDispatcher);

    // Create VAO
    glGenVertexArrays(1, &VAO);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
}

void Renderer::Draw()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind VAO
    glBindVertexArray(VAO);

    // Set Delta Time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Draw Entities
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->Draw();
    }

    // Process Keyboard Input
    camera.ProcessInput(window, deltaTime);

    // Unbind VAO
    glBindVertexArray(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

GLFWwindow *Renderer::GetWindow()
{
    return window;
}

void Renderer::DeleteModels()
{
    for (auto it = models.begin(); it != models.end(); ++it)
    {
        delete it->second;
        models.erase(it);
    }
}

Model *Renderer::LoadModel(std::string fileName)
{
    Model *model = loader.LoadModel(fileName, &VAO);
    models[model->name] = model;

    return model;
}

std::map<std::string, Model *> Renderer::LoadModels(std::string fileName)
{
    std::map<std::string, Model *> models = loader.LoadModels(fileName, &VAO);

    for (const auto &[name, model] : models)
    {
        this->models[name] = model;
        std::cout << name << std::endl;
    }

    return models;
}

Entity *Renderer::CreateEntity(Model *model)
{
    Entity *entity = new Entity(model, &camera);

    entities.push_back(entity);
    return entity;
}