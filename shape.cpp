#include "loadShader.cpp"
#include "shape.h"

Shape::Shape(const char *vert, const char *frag, GLfloat *vertices, GLfloat *colors, size_t nVertices, size_t nColors, GLuint *VAO)
{
    this->nVertices = nVertices;
    this->VAO = VAO;

    mode = GL_TRIANGLES;

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

    // Unbind VAO
    glBindVertexArray(0);

    // Create and compile shaders
    shaderProgram = LoadShaders(vert, frag);
}

Shape::Shape(GLuint *VAO, std::vector<GLfloat> &vertices, GLenum mode)
{
    this->VAO = VAO;
    this->nVertices = vertices.size() / 3;
    this->mode = mode;

    // Bind VAO
    glBindVertexArray(*VAO);

    // Create Vertex VBO
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // Unbind VAO
    glBindVertexArray(0);

    // Create Shader Program
    shaderProgram = LoadShaders("./shaders/jet.vert", "./shaders/jet.frag");
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
    glDrawArrays(mode, 0, nVertices);
}

void Shape::SetPosition(glm::vec3 position)
{
    this->position = position;
    model = glm::translate(glm::mat4(1.0f), position);
}