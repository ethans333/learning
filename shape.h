#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

class Shape
{
private:
    size_t numVertices;
    GLuint vao;
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint shaderProgram;

public:
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0, 0, 0);

    Shape(char *vert, char *frag, GLfloat *vertices, GLfloat *colors);
    ~Shape();

    void Draw(Camera *camera);
};