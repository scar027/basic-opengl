#include "triangle_mesh.h"

TriangleMesh::TriangleMesh()
{
  // [x, y, z, r, g, b] also called as normalized device coordinates(NDC)
  // vertex is a collection of all the attributes required to draw a point
  std::vector<float> positions = {
    -1.0f, -1.0f, 0.0f, 
     1.0f, -1.0f, 0.0f, 
    -1.0f,  1.0f, 0.0f,
     1.0f, 1.0f, 0.0f
  };

  std::vector<int> colorIndices = {
    0, 1, 2, 3
  };
  
  std::vector<int> elementIndices = {
    0, 1, 2, 2, 1, 3
  };

  vertex_count = 6;

  glGenVertexArrays(1, &VAO); // VAO: Vertex Array Object
  glBindVertexArray(VAO);

  VBOs.resize(2); // create 2 unsigned integers

  glGenBuffers(2, VBOs.data()); // VBO: Vertex Buffer Object
  
  //position
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  // with std::vector, .data() fn returns pointer to the beginning of the data
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0); 
  // 12 is the stride or the number of bytes required to get to the attribute for the next vertex
  // here our attribute consists of 3 floats and each float is 4 bytes which indicates
  // a stride of 3 * 4 = 12
  glEnableVertexAttribArray(0);

  //color indices
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(float), colorIndices.data(), GL_STATIC_DRAW);
  glVertexAttribIPointer(1, 1, GL_INT, 4, (void*)0);
  // here we used a stride of 4 since 1 int is 4 bytes
  glEnableVertexAttribArray(1);

  //element buffer
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementIndices.size() * sizeof(float), elementIndices.data(), GL_STATIC_DRAW);
}


void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
    // parameters of the above fn are the draw mode(triangle here), first vertex, no. of vertices
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs.data());
    glDeleteBuffers(1, &EBO);
}