#include "model.h"

#pragma once

class Entity
{
public:
    Entity(Model *model, Camera *camera);
    ~Entity();

    void Draw();

    void SetPosition(glm::vec3 position);
    void SetScale(glm::vec3 scale);
    void SetScale(glm::f32 scale);
    void SetRotation(glm::vec3 rotation);

    glm::vec3 GetPosition();
    glm::vec3 GetScale();
    glm::vec3 GetRotation();

private:
    Model *model;
    Camera *camera;

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
};