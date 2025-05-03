#include "objReader.h"

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

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec3> normals;
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
            glm::vec3 v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (prefix == "vt")
        {
            glm::vec2 vt;
            iss >> vt.x >> vt.y;
            texcoords.push_back(vt);
        }
        else if (prefix == "vn")
        {
            glm::vec3 vn;
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
    std::vector<GLfloat> vertexBuffer = BuildVertexBuffer(&faces, &vertices);

    return new Shape(VAO, vertexBuffer);
}

std::vector<GLfloat> ObjReader::BuildVertexBuffer(std::vector<std::vector<FaceElement>> *faces, std::vector<glm::vec3> *vertices)
{
    std::vector<GLfloat> buffer;

    for (std::vector<FaceElement> face : *faces)
    {
        size_t nV = face.size();

        // Triangle
        if (nV == 3)
        {
            for (FaceElement e : face)
            {
                glm::vec3 vertex = (*vertices)[e.v - 1];

                buffer.push_back((GLfloat)vertex.x);
                buffer.push_back((GLfloat)vertex.y);
                buffer.push_back((GLfloat)vertex.z);

                // TODO: Handle Tex Coords and Normals
            }
        }
        else if (nV == 4)
        {
            glm::vec3 v0 = (*vertices)[face[0].v - 1];
            glm::vec3 v1 = (*vertices)[face[1].v - 1];
            glm::vec3 v2 = (*vertices)[face[2].v - 1];
            glm::vec3 v3 = (*vertices)[face[3].v - 1];

            // Triangle 1
            buffer.insert(buffer.end(), {v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z});
            // Triangle 2
            buffer.insert(buffer.end(), {v0.x, v0.y, v0.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z});
        }
        // Convex N-Gon
        else
        {
            glm::vec3 v0 = (*vertices)[0];

            for (size_t i = 1; i + 1 < nV; i++)
            {
                glm::vec3 v1 = (*vertices)[i];
                glm::vec3 v2 = (*vertices)[i + 1];

                // Add v0
                buffer.push_back((GLfloat)v0.x);
                buffer.push_back((GLfloat)v0.y);
                buffer.push_back((GLfloat)v0.z);

                // Add v_i
                buffer.push_back((GLfloat)v1.x);
                buffer.push_back((GLfloat)v1.y);
                buffer.push_back((GLfloat)v1.z);

                // Add v_i+1
                buffer.push_back((GLfloat)v1.x);
                buffer.push_back((GLfloat)v1.y);
                buffer.push_back((GLfloat)v1.z);
            }
        }
    }

    return buffer;
}
