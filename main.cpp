#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#include "renderer.h"
#include "shape.h"

int main()
{
    Renderer renderer = Renderer();

    std::vector<Shape *> blocks = renderer.LoadShapes("models/blocks/blocks.obj");
    Shape *jet1 = renderer.LoadShape("models/Areosaur.1/model.obj");
    Shape *jet2 = renderer.LoadShape("models/Jet/Jet_01.obj");

    jet1->SetPosition(glm::vec3(-1, 0, 0));

    jet2->SetScale(0.1f);
    jet2->SetPosition(glm::vec3(-4, 3, 3));

    for (Shape *block : blocks)
    {
        block->SetScale(0.1f);
    }

    do
    {
        renderer.Draw();

    } while (!glfwWindowShouldClose(renderer.GetWindow()));
}