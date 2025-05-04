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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma once

class ObjLoader
{
public:
    std::vector<Shape *> LoadShapes(std::string fileName, GLuint *VAO);
    Shape *LoadShape(std::string fileName, GLuint *VAO);
};