#include "shape.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

#pragma once

struct FaceElement
{
    int v, vt, vn;
};

class ObjReader
{
private:
    std::vector<GLfloat> BuildVertexBuffer(std::vector<std::vector<FaceElement>> *faces, std::vector<glm::vec3> *vertices);

public:
    ObjReader();
    Shape *Read(const char *fileName, GLuint *VAO);
};