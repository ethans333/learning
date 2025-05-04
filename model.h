#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "camera.h"

#pragma once

class Model
{

private:
    GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

public:
    std::string name;

    GLuint *VAO;
    GLuint VBO;
    GLuint buffer;
    GLuint shader;
    size_t vertexCount;

    Model(std::string name, GLuint *VAO, std::vector<GLfloat> vertices, std::string vertexShader, std::string fragmentShader);
    ~Model();

    void UseShader(glm::mat4 modelMatrix, Camera *camera);
    void Draw();
};