#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include "camera.h"
#include "ModelLoader.h"
#include "entity.h"

#pragma once

class Renderer
{
private:
    int width = 1920, height = 1080;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    GLFWwindow *window;
    ModelLoader loader = ModelLoader();

    std::map<std::string, Model *> models;
    std::vector<Entity *> entities;

    void DeleteModels();

public:
    Camera camera = Camera(width, height);
    GLuint VAO;

    Renderer();
    ~Renderer();

    void Draw();

    GLFWwindow *GetWindow();

    Model *LoadModel(std::string fileName);
    std::map<std::string, Model *> LoadModels(std::string fileName);

    Entity *CreateEntity(Model *model);
};