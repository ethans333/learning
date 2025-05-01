#include "objReader.h"

struct Vec3
{
    float x, y, z;
};
struct Vec2
{
    float u, v;
};
struct FaceElement
{
    int v, vt, vn;
};

ObjReader::ObjReader()
{
}

Shape *ObjReader::Read(const char *fileName, GLuint *VAO)
{
    // Open File
    std::ifstream file(fileName);

    // Failed to Open File
    if (!file)
    {
        std::cerr << "Unable to open file\n";
        return nullptr;
    }

    std::vector<Vec3> vertices;
    std::vector<Vec2> texcoords;
    std::vector<Vec3> normals;
    std::vector<std::vector<FaceElement>> faces;

    // Read Lines
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v")
        {
            Vec3 v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (prefix == "vt")
        {
            Vec2 vt;
            iss >> vt.u >> vt.v;
            texcoords.push_back(vt);
        }
        else if (prefix == "vn")
        {
            Vec3 vn;
            iss >> vn.x >> vn.y >> vn.z;
            normals.push_back(vn);
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
        }
    }

    file.close();

    // Build Data
    GLenum mode = ((int)(faces[0].size() / sizeof(FaceElement)) == 4) ? GL_TRIANGLES : GL_TRIANGLE_STRIP;

    std::vector<GLfloat> vertexBuffer;
    size_t nVertices = 0;

    for (auto face : faces)
    {
        for (auto fe : face)
        {
            vertexBuffer.push_back((GLfloat)vertices[fe.v - 1].x);
            vertexBuffer.push_back((GLfloat)vertices[fe.v - 1].y);
            vertexBuffer.push_back((GLfloat)vertices[fe.v - 1].z);

            nVertices += 1;
            // vertexBuffer.push_back(texcoords[fe.vt - 1].u);
            // vertexBuffer.push_back(texcoords[fe.vt - 1].v);
            // vertexBuffer.push_back(normals[fe.vn - 1].x);
            // vertexBuffer.push_back(normals[fe.vn - 1].y);
            // vertexBuffer.push_back(normals[fe.vn - 1].z);
        }
    }

    return new Shape(VAO, vertexBuffer, mode);
}