#include "loadShader.cpp"
#include "shape.h"

Shape::Shape(char *vert, char *frag, GLfloat *vertices, GLfloat *colors)
{
    numVertices = sizeof(vertices) / sizeof(vertices[0]);

    // Create VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create Vertex VBO
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create Color VBO
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Create and compile shaders
    shaderProgram = LoadShaders(vert, frag);
}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteProgram(shaderProgram);
}

void Shape::Draw(Camera *camera)
{
    // Set Model View Projection Matrix
    glm::mat4 mvp = camera->projection * camera->view * model;
    GLint mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);

    // Use shader
    glUseProgram(shaderProgram);

    // Bind VAO
    glBindVertexArray(vao);

    // Enable Vertex Attributes
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // Enable Color Attribute
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // Draw Triangles
    glDrawArrays(GL_TRIANGLES, 0, numVertices);

    // Disable Vertex Attributes
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}