#include "shape.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <unordered_map>
#include <string>

#pragma once

struct FaceElement
{
    int v, vt, vn;
};

class ObjReader
{
private:
    std::vector<GLfloat> BuildVertexBuffer(std::vector<std::vector<FaceElement>> *faces, std::vector<glm::vec3> *vertices, std::vector<glm::vec3> *colors);
    std::unordered_map<std::string, glm::vec3> ParseMtlFile(std::string fileName);
    std::string GetDirectory(const std::string &filePath);

public:
    ObjReader();
    Shape *Read(const char *fileName, GLuint *VAO);
};