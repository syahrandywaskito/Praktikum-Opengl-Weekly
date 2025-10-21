#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// vertex shader source
const char* vertexShaderSource = R"(
  #version 460 core
  layout (location = 0) in vec2 aPos;
  void main() {
    vec2 normalizedPos = aPos / 0.5;
    vec2 scaledPos = normalizePos * 0.5f;

    gl_Position = vec4(scaledPos, 0.0, 1.0);
  }
)";

// fragment shader source
const char* fragmentShaderSource = R"(
  #version 460 core
  out vec4 FragColor;
  void main(){
    FragColor = vec4(0.0, 1.0, 1.0, 1.0); 
  }
)";


int main(int argc, char **argv) 
{
  // ini GLFW
  glfwInit();

  // error handling init GLFW
  if (!glfwInit())
  {
    std::cerr << "Gagal ini GLFW" << std::endl;
    return -1;
  }

  // set window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // versi besar (depan titik)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // versi kecil (belakang titik)
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // membuat window dengan ukuran 750px X 750px
  GLFWwindow* window = glfwCreateWindow(750, 750, "Tugas Praktikum 3", NULL, NULL);

  // error handling jika window gagal dibuat dan dimuat
  if (!window)
  {
    std::cerr << "Gagar memuat window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // set window ke current menggunakan context current
  glfwMakeContextCurrent(window);

  // init GLAD
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Gagal init GLAD" << std::endl;
    return -1; 
  }

  // compile shader start

  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // shader program (memasangkan shader (fragment dan vertex ke dalam shader program))
  // alur : attacht -> link -> delete
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // setup vertices, atau titik yang digunakan untuk menggambar bentuk
  float vertices[] = {
    -0.5f, -0.5f,
    -0.5f, 0.5f,
    0.5f, 0.5f,
    0.5f, -0.5f,
  };

  // setup indices : setiga yang digunakan untuk membagi gambar agar tidak terlalu berat
  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0, 
  };
  
  // setup VAO, VBO, dan EBO
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  // bind VBO dan set buffer data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  // bind EBO dan set buffer data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // loop render untuk merender objek selama window tidak di close
  while (!glfwWindowShouldClose(window))
  {
    // setup warna background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers dan poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // cleanup rendering 
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(2, &EBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}