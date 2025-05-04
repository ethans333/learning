#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include "renderer.h"
#include "shape.h"

int main()
{
    Renderer renderer = Renderer();

    // Shape *blocks = renderer.LoadShape("models/blocks/blocks.obj");
    Shape *jet1 = renderer.LoadShape("models/Areosaur.1/model.obj");
    // Shape *jet2 = renderer.LoadShape("models/Jet/Jet_01.obj");

    jet1->SetPosition(glm::vec3(-1, 0, 0));

    // jet2->SetScale(0.1f);
    // jet2->SetPosition(glm::vec3(-4, 3, 3));

    // blocks->SetPosition(glm::vec3(3, 0, 3));

    do
    {
        renderer.Draw();

    } while (!glfwWindowShouldClose(renderer.GetWindow()));
}