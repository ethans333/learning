#include "shape.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

#pragma once

class ObjReader
{
public:
    ObjReader();
    Shape *Read(const char *fileName, GLuint *VAO);
};