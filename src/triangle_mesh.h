#include "config.h"

class TriangleMesh {
public:
TriangleMesh();
void draw();
~TriangleMesh();

private:
unsigned int EBO, VAO, vertex_count;
// EBO: Element Buffer Object
std::vector<unsigned int> VBOs;
};