#include "entity.h"

Entity::Entity(Model *model, Camera *camera)
{
    this->model = model;
    this->camera = camera;
}

Entity::~Entity()
{
    delete model;
}

void Entity::Draw()
{
    model->UseShader(modelMatrix, camera);
    model->Draw();
}

void Entity::SetPosition(glm::vec3 position)
{
    this->position = position;
    modelMatrix = glm::translate(modelMatrix, position);
}

void Entity::SetScale(glm::vec3 scale)
{
    this->scale = scale;
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Entity::SetScale(glm::f32 scale)
{
    this->scale = glm::vec3(scale, scale, scale);
    modelMatrix = glm::scale(modelMatrix, this->scale);
}

void Entity::SetRotation(glm::vec3 rotation)
{
    this->rotation = rotation;
    modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
}

glm::vec3 Entity::GetPosition()
{
    return position;
}

glm::vec3 Entity::GetScale()
{
    return scale;
}

glm::vec3 Entity::GetRotation()
{
    return rotation;
}