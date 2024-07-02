#include "triangle_mesh.h"

TriangleMesh::TriangleMesh()
{
  // [x, y, z, r, g, b] also called as normalized device coordinates(NDC)
  // vertex is a collection of all the attributes required to draw a point
  std::vector<float> data = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left vertex
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right vertex
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top vertex
  };
  vertex_count = 3;

  glGenVertexArrays(1, &VAO); // VAO: Vertex Array Object
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO); // VBO: Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // with std::vector, .data() fn returns pointer to the address where the data is stored
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

  //position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
  glEnableVertexAttribArray(0);

  //color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
  glEnableVertexAttribArray(1);

}


void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}