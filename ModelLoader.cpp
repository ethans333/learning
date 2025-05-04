#include "ModelLoader.h"

Model *ModelLoader::LoadModel(std::string fileName, GLuint *VAO)
{
    Model *model;

    // Create an Assimp importer
    Assimp::Importer importer;

    // Import the model with some post-processing flags
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    // Check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return model;
    }

    // Extract vertex data
    std::vector<float> vertexData;

    // Process all meshes in the scene
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[i];

        // Get material color
        glm::vec3 color(1.0f);
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            aiColor3D diffuse(0.f, 0.f, 0.f);
            if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
            {
                color = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
            }
        }

        for (unsigned int j = 0; j < mesh->mNumFaces; j++)
        {
            const aiFace &face = mesh->mFaces[j];

            // Process each vertex in the face (triangles)
            for (unsigned int k = 0; k < face.mNumIndices; k++)
            {
                unsigned int vertexIndex = face.mIndices[k];

                // Position
                aiVector3D pos = mesh->mVertices[vertexIndex];
                vertexData.push_back(pos.x);
                vertexData.push_back(pos.y);
                vertexData.push_back(pos.z);

                // Color (from material)
                vertexData.push_back(color.r);
                vertexData.push_back(color.g);
                vertexData.push_back(color.b);

                // Normal
                if (mesh->HasNormals())
                {
                    aiVector3D normal = mesh->mNormals[vertexIndex];
                    vertexData.push_back(normal.x);
                    vertexData.push_back(normal.y);
                    vertexData.push_back(normal.z);
                }
                else
                {
                    vertexData.push_back(0.0f);
                    vertexData.push_back(0.0f);
                    vertexData.push_back(1.0f);
                }

                // // Texture coordinates
                // if (mesh->HasTextureCoords(0))
                // {
                //     aiVector3D uv = mesh->mTextureCoords[0][vertexIndex];
                //     vertexData.push_back(uv.x);
                //     vertexData.push_back(uv.y);
                // }
                // else
                // {
                //     vertexData.push_back(0.0f);
                //     vertexData.push_back(0.0f);
                // }
            }
        }
    }

    // Model Name
    std::string modelName = fileName.substr(fileName.find_last_of("/\\") + 1);
    modelName = modelName.substr(0, modelName.find_last_of('.'));

    // Create Model
    model = new Model(modelName, VAO, vertexData, "shaders/jet.vert", "shaders/jet.frag");
    return model;
}

std::map<std::string, Model *> ModelLoader::LoadModels(std::string fileName, GLuint *VAO)
{
    // Model Map
    std::map<std::string, Model *> models;

    // Create an Assimp importer
    Assimp::Importer importer;

    // Import the model with some post-processing flags
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    // Check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return models;
    }

    // Process all meshes in the scene
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[i];

        // Get material color
        glm::vec3 color(1.0f);
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            aiColor3D diffuse(0.f, 0.f, 0.f);
            if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
            {
                color = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
            }
        }

        // Extract vertex data
        std::vector<float> vertexData;

        for (unsigned int j = 0; j < mesh->mNumFaces; j++)
        {
            const aiFace &face = mesh->mFaces[j];

            // Process each vertex in the face (triangles)
            for (unsigned int k = 0; k < face.mNumIndices; k++)
            {
                unsigned int vertexIndex = face.mIndices[k];

                // Position
                aiVector3D pos = mesh->mVertices[vertexIndex];
                vertexData.push_back(pos.x);
                vertexData.push_back(pos.y);
                vertexData.push_back(pos.z);

                // Color (from material)
                vertexData.push_back(color.r);
                vertexData.push_back(color.g);
                vertexData.push_back(color.b);

                // Normal
                if (mesh->HasNormals())
                {
                    aiVector3D normal = mesh->mNormals[vertexIndex];
                    vertexData.push_back(normal.x);
                    vertexData.push_back(normal.y);
                    vertexData.push_back(normal.z);
                }
                else
                {
                    vertexData.push_back(0.0f);
                    vertexData.push_back(0.0f);
                    vertexData.push_back(1.0f);
                }

                // // Texture coordinates
                // if (mesh->HasTextureCoords(0))
                // {
                //     aiVector3D uv = mesh->mTextureCoords[0][vertexIndex];
                //     vertexData.push_back(uv.x);
                //     vertexData.push_back(uv.y);
                // }
                // else
                // {
                //     vertexData.push_back(0.0f);
                //     vertexData.push_back(0.0f);
                // }
            }
        }

        // Model name
        std::string modelName = fileName.substr(fileName.find_last_of("/\\") + 1);
        modelName = modelName.substr(0, modelName.find_last_of('.')) + "/" + mesh->mName.C_Str();

        // Create Model
        Model *model = new Model(modelName, VAO, vertexData, "shaders/jet.vert", "shaders/jet.frag");
        models[modelName] = model;
    }

    return models;
}