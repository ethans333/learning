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

class ObjLoader
{
private:
    std::vector<GLfloat> BuildBuffer(std::vector<std::vector<FaceElement>> *faces, std::vector<glm::vec3> *vertices, std::vector<glm::vec3> *normal, std::vector<glm::vec3> *colors);
    std::unordered_map<std::string, glm::vec3> ParseMaterial(std::string fileName);
    std::string GetDirectory(const std::string &filePath);
    void AddTriangle(std::vector<GLfloat> &buffer, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &color, const glm::vec3 &normal);
    void AddVertexData(std::vector<GLfloat> &buffer, const glm::vec3 &vertex,
                       const glm::vec3 &color, const glm::vec3 &normal);

public:
    std::vector<Shape *> LoadShapes(std::string fileName, GLuint *VAO);
    Shape *LoadShape(std::string fileName, GLuint *VAO);
};