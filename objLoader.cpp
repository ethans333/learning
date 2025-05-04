#include "objLoader.h"

Shape *ObjLoader::LoadShape(std::string fileName, GLuint *VAO)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> texcoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<std::vector<FaceElement>> faces;

    std::unordered_map<std::string, glm::vec3> colorMap;
    std::string currentMat;

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        fprintf(stderr, "Failed to open OBJ file: %s \n", fileName);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "mtllib")
        {
            std::string mtlFile;
            iss >> mtlFile;
            colorMap = ParseMaterial(GetDirectory(fileName) + "/" + mtlFile);
        }
        else if (prefix == "v")
        {
            glm::vec3 v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (prefix == "vt")
        {
            glm::vec3 vt;
            iss >> vt.x >> vt.y;
            texcoords.push_back(vt);
        }
        else if (prefix == "vn")
        {
            glm::vec3 vn;
            iss >> vn.x >> vn.y >> vn.z;
            normals.push_back(vn);
        }
        else if (prefix == "usemtl")
        {
            iss >> currentMat;
        }
        else if (prefix == "f")
        {
            std::vector<FaceElement> face;
            std::string vertex;

            while (iss >> vertex)
            {
                std::replace(vertex.begin(), vertex.end(), '/', ' ');
                std::istringstream viss(vertex);
                FaceElement fe;
                viss >> fe.v >> fe.vt >> fe.vn;
                face.push_back(fe);
            }

            faces.push_back(face);
            colors.push_back(colorMap[currentMat]);
        }
    }

    file.close();
    std::vector<GLfloat> modelBuffer = BuildBuffer(&faces, &vertices, &normals, &colors);
    return new Shape(VAO, modelBuffer);
}

std::vector<Shape *> ObjLoader::LoadShapes(std::string fileName, GLuint *VAO)
{
    // TODO
}

void ObjLoader::AddVertexData(std::vector<GLfloat> &buffer, const glm::vec3 &vertex, const glm::vec3 &color, const glm::vec3 &normal)
{
    // Add Vertex
    buffer.push_back((GLfloat)vertex.x);
    buffer.push_back((GLfloat)vertex.y);
    buffer.push_back((GLfloat)vertex.z);

    // Add Color
    buffer.push_back((GLfloat)color.x);
    buffer.push_back((GLfloat)color.y);
    buffer.push_back((GLfloat)color.z);

    // Add Normal
    buffer.push_back((GLfloat)normal.x);
    buffer.push_back((GLfloat)normal.y);
    buffer.push_back((GLfloat)normal.z);
}

void ObjLoader::AddTriangle(std::vector<GLfloat> &buffer, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &color, const glm::vec3 &normal)
{
    AddVertexData(buffer, v1, color, normal);
    AddVertexData(buffer, v2, color, normal);
    AddVertexData(buffer, v3, color, normal);
}

std::vector<GLfloat> ObjLoader::BuildBuffer(std::vector<std::vector<FaceElement>> *faces, std::vector<glm::vec3> *vertices, std::vector<glm::vec3> *normals, std::vector<glm::vec3> *colors)
{
    std::vector<GLfloat> buffer;

    for (size_t i = 0; i < faces->size(); i++)
    {
        std::vector<FaceElement> &face = (*faces)[i];
        size_t nV = face.size();
        glm::vec3 color = (*colors)[i];
        glm::vec3 normal = (*normals)[face[0].vn];

        if (nV == 3)
        {
            // Simple triangle
            AddTriangle(buffer, (*vertices)[face[0].v - 1], (*vertices)[face[1].v - 1], (*vertices)[face[2].v - 1], color, normal);
        }
        else if (nV == 4)
        {
            // Quad - split into two triangles
            glm::vec3 v0 = (*vertices)[face[0].v - 1];
            glm::vec3 v1 = (*vertices)[face[1].v - 1];
            glm::vec3 v2 = (*vertices)[face[2].v - 1];
            glm::vec3 v3 = (*vertices)[face[3].v - 1];

            AddTriangle(buffer, v0, v1, v2, color, normal);
            AddTriangle(buffer, v0, v2, v3, color, normal);
        }
        else
        {
            // N-gon - triangulate using fan method
            glm::vec3 v0 = (*vertices)[face[0].v - 1];

            for (size_t j = 1; j + 1 < nV; j++)
            {
                AddTriangle(buffer, v0, (*vertices)[face[j].v - 1], (*vertices)[face[j + 1].v - 1], color, normal);
            }
        }
    }

    return buffer;
}

std::unordered_map<std::string, glm::vec3> ObjLoader::ParseMaterial(std::string fileName)
{
    std::unordered_map<std::string, glm::vec3> colorMap;
    std::string currentMaterial;

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        fprintf(stderr, "Failed to open material file: %s \n", fileName);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "newmtl")
        {
            iss >> currentMaterial;
        }
        else if (prefix == "Kd")
        {
            float r, g, b;
            iss >> r >> g >> b;
            colorMap[currentMaterial] = glm::vec3(r, g, b);
        }
    }

    return colorMap;
}

std::string ObjLoader::GetDirectory(const std::string &filePath)
{
    size_t found = filePath.find_last_of("/\\");
    return (found != std::string::npos) ? filePath.substr(0, found) : ".";
}