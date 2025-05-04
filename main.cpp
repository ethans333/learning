#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include "renderer.h"

int main()
{
    Renderer renderer = Renderer();

    // Load Models
    std::map<std::string, Model *> blocks = renderer.LoadModels("models/blocks/blocks.obj");
    Model *jetModel = renderer.LoadModel("models/Areosaur.1/model.obj");
    Model *jetModel2 = renderer.LoadModel("models/Jet/Jet_01.obj");

    // Create Entities
    Entity *stairs = renderer.CreateEntity(blocks["blocks/Stairs"]);
    Entity *jet1 = renderer.CreateEntity(jetModel);
    Entity *jet2 = renderer.CreateEntity(jetModel);
    Entity *jet3 = renderer.CreateEntity(jetModel2);

    // Set Entity Properties
    jet1->SetPosition(glm::vec3(-1, 0, 0));

    jet2->SetScale(0.1f);
    jet2->SetPosition(glm::vec3(-4, 3, 3));

    jet3->SetScale(0.1f);
    jet3->SetPosition(glm::vec3(4, -3, -3));

    // Draw
    do
    {
        renderer.Draw();

    } while (!glfwWindowShouldClose(renderer.GetWindow()));
}