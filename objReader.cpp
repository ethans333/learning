#include "objReader.h"

Shape *ObjReader::Read(std::string fileName, GLuint *VAO)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> texcoords;
    std::vector<glm::vec3> normals;

    std::vector<glm::vec3> colors;
    std::vector<std::vector<FaceElement>> faces;

    std::unordered_map<std::string, glm::vec3> colorMap;
    std::string currentMat;

    // Open File
    std::ifstream file(fileName);

    // Check if File Opened Successfully
    if (!file.is_open())
    {
        fprintf(stderr, "Failed to open OBJ file: %s \n", fileName);
    }

    // Read Lines
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

            std::string fullPath = GetDirectory(fileName) + "/" + mtlFile;
            colorMap = ParseMtlFile(fullPath);
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

    // Build Data
    std::vector<GLfloat> modelBuffer = BuildVertexBuffer(&faces, &vertices, &normals, &colors);

    return new Shape(VAO, modelBuffer);
}

std::vector<GLfloat> ObjReader::BuildVertexBuffer(std::vector<std::vector<FaceElement>> *faces, std::vector<glm::vec3> *vertices, std::vector<glm::vec3> *normals, std::vector<glm::vec3> *colors)
{
    std::vector<GLfloat> buffer;
    size_t i = 0;

    for (std::vector<FaceElement> face : *faces)
    {
        size_t nV = face.size();
        glm::vec3 color = (*colors)[i];
        glm::vec3 normal = (*normals)[face[0].vn];

        // Triangle
        if (nV == 3)
        {
            for (FaceElement e : face)
            {
                glm::vec3 vertex = (*vertices)[e.v - 1];

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
        }
        else if (nV == 4)
        {
            glm::vec3 v0 = (*vertices)[face[0].v - 1];
            glm::vec3 v1 = (*vertices)[face[1].v - 1];
            glm::vec3 v2 = (*vertices)[face[2].v - 1];
            glm::vec3 v3 = (*vertices)[face[3].v - 1];

            // Triangle 1, Vertex 1
            buffer.push_back((GLfloat)v0.x);
            buffer.push_back((GLfloat)v0.y);
            buffer.push_back((GLfloat)v0.z);

            // Add Color
            buffer.push_back((GLfloat)color.x);
            buffer.push_back((GLfloat)color.y);
            buffer.push_back((GLfloat)color.z);

            // Add Normal
            buffer.push_back((GLfloat)normal.x);
            buffer.push_back((GLfloat)normal.y);
            buffer.push_back((GLfloat)normal.z);

            // Triangle 1, Vertex 2
            buffer.push_back((GLfloat)v1.x);
            buffer.push_back((GLfloat)v1.y);
            buffer.push_back((GLfloat)v1.z);

            // Add Color
            buffer.push_back((GLfloat)color.x);
            buffer.push_back((GLfloat)color.y);
            buffer.push_back((GLfloat)color.z);

            // Add Normal
            buffer.push_back((GLfloat)normal.x);
            buffer.push_back((GLfloat)normal.y);
            buffer.push_back((GLfloat)normal.z);

            // Triangle 3, Vertex 3
            buffer.push_back((GLfloat)v2.x);
            buffer.push_back((GLfloat)v2.y);
            buffer.push_back((GLfloat)v2.z);

            // Add Color
            buffer.push_back((GLfloat)color.x);
            buffer.push_back((GLfloat)color.y);
            buffer.push_back((GLfloat)color.z);

            // Add Normal
            buffer.push_back((GLfloat)normal.x);
            buffer.push_back((GLfloat)normal.y);
            buffer.push_back((GLfloat)normal.z);

            // Triangle 2, Vertex 1
            buffer.push_back((GLfloat)v0.x);
            buffer.push_back((GLfloat)v0.y);
            buffer.push_back((GLfloat)v0.z);

            // Add Color
            buffer.push_back((GLfloat)color.x);
            buffer.push_back((GLfloat)color.y);
            buffer.push_back((GLfloat)color.z);

            // Add Normal
            buffer.push_back((GLfloat)normal.x);
            buffer.push_back((GLfloat)normal.y);
            buffer.push_back((GLfloat)normal.z);

            // Triangle 2, Vertex 2
            buffer.push_back((GLfloat)v2.x);
            buffer.push_back((GLfloat)v2.y);
            buffer.push_back((GLfloat)v2.z);

            // Add Color
            buffer.push_back((GLfloat)color.x);
            buffer.push_back((GLfloat)color.y);
            buffer.push_back((GLfloat)color.z);

            // Add Normal
            buffer.push_back((GLfloat)normal.x);
            buffer.push_back((GLfloat)normal.y);
            buffer.push_back((GLfloat)normal.z);

            // Triangle 2, Vertex 3
            buffer.push_back((GLfloat)v3.x);
            buffer.push_back((GLfloat)v3.y);
            buffer.push_back((GLfloat)v3.z);

            // Add Color
            buffer.push_back((GLfloat)color.x);
            buffer.push_back((GLfloat)color.y);
            buffer.push_back((GLfloat)color.z);

            // Add Normal
            buffer.push_back((GLfloat)normal.x);
            buffer.push_back((GLfloat)normal.y);
            buffer.push_back((GLfloat)normal.z);
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

                // Add Color
                buffer.push_back((GLfloat)color.x);
                buffer.push_back((GLfloat)color.y);
                buffer.push_back((GLfloat)color.z);

                // Add Normal
                buffer.push_back((GLfloat)normal.x);
                buffer.push_back((GLfloat)normal.y);
                buffer.push_back((GLfloat)normal.z);

                // Add v_i
                buffer.push_back((GLfloat)v1.x);
                buffer.push_back((GLfloat)v1.y);
                buffer.push_back((GLfloat)v1.z);

                // Add Color
                buffer.push_back((GLfloat)color.x);
                buffer.push_back((GLfloat)color.y);
                buffer.push_back((GLfloat)color.z);

                // Add Normal
                buffer.push_back((GLfloat)normal.x);
                buffer.push_back((GLfloat)normal.y);
                buffer.push_back((GLfloat)normal.z);

                // Add v_i+1
                buffer.push_back((GLfloat)v2.x);
                buffer.push_back((GLfloat)v2.y);
                buffer.push_back((GLfloat)v2.z);

                // Add Color
                buffer.push_back((GLfloat)color.x);
                buffer.push_back((GLfloat)color.y);
                buffer.push_back((GLfloat)color.z);

                // Add Normal
                buffer.push_back((GLfloat)normal.x);
                buffer.push_back((GLfloat)normal.y);
                buffer.push_back((GLfloat)normal.z);
            }
        }

        i++;
    }

    return buffer;
}

std::unordered_map<std::string, glm::vec3> ObjReader::ParseMtlFile(std::string fileName)
{
    std::unordered_map<std::string, glm::vec3> colorMap;
    std::string currentMaterial;

    // Open File
    std::ifstream file(fileName);

    // Check if File Opened Successfully
    if (!file.is_open())
    {
        fprintf(stderr, "Failed to open material file: %s \n", fileName);
    }

    // Read Lines
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

std::string ObjReader::GetDirectory(const std::string &filePath)
{
    size_t found = filePath.find_last_of("/\\");
    return (found != std::string::npos) ? filePath.substr(0, found) : ".";
}
