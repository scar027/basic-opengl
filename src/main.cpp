#include "config.h"
#include "triangle_mesh.h"

unsigned int make_module(const std::string& filepath, unsigned int module_type);

unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);


int main()
{
  GLFWwindow* window;

  if (!glfwInit())
  {
    std::cout << "GLFW couldn't start" << std::endl;
    return -1;
  }

  window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL); // defining the size of the window
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    glfwTerminate();
    return -1;
  }

   glClearColor(0.75f, 0.5f, 0.5f, 1.0f); // setting default colour when cleared

  // get viewport size
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  glViewport(0,0,w,h);

  TriangleMesh* triangle = new TriangleMesh();

  unsigned int shader = make_shader("../src/shaders/vertex.txt", "../src/shaders/fragment.txt");

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT); // clearing the colour buffer
    glUseProgram(shader);
    triangle -> draw();
    glfwSwapBuffers(window);
  }

  glDeleteProgram(shader);
  glfwTerminate();
  return 0;
}

unsigned int make_module(const std::string& filepath, unsigned int module_type)
{
  // function to take a file path and make a shader module
  std::ifstream file;
  std::stringstream bufferedLines;
  std::string line;

  file.open(filepath);
  while (std::getline(file, line))
  {
    bufferedLines << line << "\n";
  }
  std::string shaderSource = bufferedLines.str();

  // convert from cpp standard library string to c style char pointer
  const char* shaderSrc = shaderSource.c_str();
  bufferedLines.str("");
  file.close();

  // creating a shader module and attaching the source code to it
  unsigned int shaderModule = glCreateShader(module_type);
  glShaderSource(shaderModule, 1, &shaderSrc, NULL);
  glCompileShader(shaderModule);

  // check if the shader module has compiled successfully
  int success;
  glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char errorLog[1024];
    glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
    std::cout << "Shader module compilation error: \n" << errorLog << std::endl;
  }

  return shaderModule;
}

unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
  std::vector<unsigned int> modules;
  modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
  modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

  // link the compiled shader modules
  unsigned int shader = glCreateProgram();
  for (unsigned int shaderModule : modules)
  {
    glAttachShader(shader, shaderModule);
  }
  glLinkProgram(shader);

  // check if the shader module has linked successfully
  int success;
  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  if (!success)
  {
    char errorLog[1024];
    glGetProgramInfoLog(shader, 1024, NULL, errorLog);
    std::cout << "Shader module linking error: \n" << errorLog << std::endl;
  }

  // shader modules can be deleted after linking
  for (unsigned int shaderModule : modules)
  {
    glDeleteShader(shaderModule);
  }

  return shader;
}