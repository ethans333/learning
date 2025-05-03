#include "loadShader.cpp"
#include "shape.h"

Shape::Shape(GLuint *VAO, std::vector<GLfloat> vertices)
{
    this->VAO = VAO;
    this->nVertices = vertices.size() / 9;

    // Bind VAO
    glBindVertexArray(*VAO);

    // Create Vertex VBO
    glGenBuffers(1, &modelBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Set Vertex VBO Attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Unbind VAO
    glBindVertexArray(0);

    // Create Shader Program
    shaderProgram = LoadShaders("./shaders/jet.vert", "./shaders/jet.frag");
}

Shape::~Shape()
{
    glDeleteBuffers(1, &modelBuffer);
    glDeleteProgram(shaderProgram);
}

void Shape::Draw(Camera *camera)
{
    // Use shader
    glUseProgram(shaderProgram);

    // Shader Variables
    GLint modelId = glGetUniformLocation(shaderProgram, "model");
    GLint viewId = glGetUniformLocation(shaderProgram, "view");
    GLint projectionId = glGetUniformLocation(shaderProgram, "projection");
    GLint lightPosId = glGetUniformLocation(shaderProgram, "lightPos");
    GLint viewPosId = glGetUniformLocation(shaderProgram, "viewPos");

    glUniformMatrix4fv(modelId, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(camera->view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(camera->projection));

    glUniform3fv(lightPosId, 1, glm::value_ptr(glm::vec3(1, 20, 1)));
    glUniform3fv(viewPosId, 1, glm::value_ptr(camera->position));

    // Bind VAO
    glBindVertexArray(*VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);

    // Configure attributes for this VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));

    // Bind VAO and draw
    glDrawArrays(GL_TRIANGLES, 0, nVertices);
}

void Shape::SetPosition(glm::vec3 position)
{
    this->position = position;
    model = glm::translate(model, position);
}

void Shape::SetScale(glm::f32 scale)
{
    this->scale = scale;
    model = glm::scale(model, glm::vec3(scale, scale, scale));
}