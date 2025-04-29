#include "loadShader.cpp"
#include "shape.h"

Shape::Shape(const char *vert, const char *frag, GLfloat *vertices, GLfloat *colors, size_t nVertices, size_t nColors, GLuint *VAO)
{
    this->nVertices = nVertices;
    this->VAO = VAO;

    // Bind VAO
    glBindVertexArray(*VAO);

    // Create Vertex VBO
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * nVertices * 3, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // Create Color VBO
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * nColors * 3, colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindVertexArray(0);

    // Create and compile shaders
    shaderProgram = LoadShaders(vert, frag);
}

Shape::~Shape()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteProgram(shaderProgram);
}

void Shape::Draw(Camera *camera)
{
    // Use shader
    glUseProgram(shaderProgram);

    // Set Model View Projection Matrix
    glm::mat4 mvp = camera->projection * camera->view * model;
    GLint mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);

    // Bind VAO and draw
    glDrawArrays(GL_TRIANGLES, 0, nVertices);
}

void Shape::SetPosition(glm::vec3 position)
{
    this->position = position;
    model = glm::translate(glm::mat4(1.0f), position);
}