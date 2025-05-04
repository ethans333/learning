#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <unordered_map>
#include <string>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "model.h"

#pragma once

class ModelLoader
{
public:
    std::map<std::string, Model *> LoadModels(std::string fileName, GLuint *VAO);
    Model *LoadModel(std::string fileName, GLuint *VAO);
};