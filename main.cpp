#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono> 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shapes.h"



using namespace std;

const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    GLFWwindow *window;                                            // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1000, 1000, "u21434558", NULL, NULL);

   if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    startUpGLEW();
    return window;
}
const char *SimpleFragmentShader = R"(
    #version 330 core

    // Ouput data
    out vec3 color;
    in vec3 fragmentColor;

    void main()
    {

	// Output color = red
	color = fragmentColor;

    }
)";

const char *SimpleVertexShader = R"(
    #version 330 core

    // Input vertex data, different for all executions of this shader.
    layout(location = 0) in vec3 vertexPosition_modelspace;
    layout(location = 1) in vec3 vertexColor;
    out vec3 fragmentColor;

    void main(){

        gl_Position.xyz = vertexPosition_modelspace;
        gl_Position.w = 1.0;
        fragmentColor = vertexColor;

    }
)";

int main() {
  GLFWwindow *window;
  try {
    window = setUp();
  } catch (const char *e) {
    cout << e << endl;
    throw;
  }

  // Add code here
  glClearColor(0, 0.1, 1, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_NEAREST);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);


  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  GLuint ID = LoadShaders(SimpleVertexShader, SimpleFragmentShader);


  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  GLuint ColorBuffer;
  glGenBuffers(1, &ColorBuffer);
  Shapes* p = new Plane();
  double lastTime;
  lastTime = glfwGetTime();
  bool pressed = false;
  do {
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(ID);
    GLfloat *v = p->toVertexArray();
    GLfloat *c = p->toColorArray();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[p->getNumVertices()]), v,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[p->getNumColors()]), c,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);


    //glDrawArrays(GL_TRIANGLES,0, p->getNumVertices());
    if (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && !pressed) {
      glDrawArrays(GL_LINES, 0, p->getNumVertices());
      pressed = true;
    } else if (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && pressed)
    {
      pressed = false;
      glDrawArrays(GL_TRIANGLES,0, p->getNumVertices());

    }else if (!pressed){
      glDrawArrays(GL_TRIANGLES,0, p->getNumVertices());

    }else
    {
      glDrawArrays(GL_LINES, 0, p->getNumVertices());

    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      //rotate around x axis in anti-clockwise directiom
      mat4x4 trnsformation = IdentityMatrix(4);
      trnsformation[1][1] = cos(-45*3.14/180);
      trnsformation[1][2] = -sin(-45*3.14/180);
      trnsformation[2][1] = sin(-45*3.14/180);
      trnsformation[2][2] = cos(-45*3.14/180);

      p->applyMat(trnsformation);
    }
    if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[1][1] = cos(45*3.14/180);
      trnsformation[1][2] = -sin(45*3.14/180);
      trnsformation[2][1] = sin(45*3.14/180);
      trnsformation[2][2] = cos(45*3.14/180);

      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[0][0] = cos(-45*3.14/180);
      trnsformation[0][2] = sin(-45*3.14/180);
      trnsformation[2][0] = -sin(-45*3.14/180);
      trnsformation[2][2] = cos(-45*3.14/180);
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[0][0] = cos(45*3.14/180);
      trnsformation[0][2] = sin(45*3.14/180);
      trnsformation[2][0] = -sin(45*3.14/180);
      trnsformation[2][2] = cos(45*3.14/180);
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS)
    {
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[0][0] = cos(-45*3.14/180);
      trnsformation[0][1] = sin(-45*3.14/180);
      trnsformation[1][0] = -sin(-45*3.14/180);
      trnsformation[1][1] = cos(-45*3.14/180);
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS)
    {
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[0][0] = cos(45*3.14/180);
      trnsformation[0][1] = sin(45*3.14/180);
      trnsformation[1][0] = -sin(45*3.14/180);
      trnsformation[1][1] = cos(45*3.14/180);
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_I) == GLFW_PRESS)
    {
      //increase y pos
      IdentityMatrix trnsformation = IdentityMatrix(4);
     trnsformation[1][3] = 0.1;
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_K) == GLFW_PRESS)
    {
      //decrease y pos
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[1][3] = -0.1;
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS)
    {
      //increase x pos
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[0][3] = 0.1;
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_J) == GLFW_PRESS)
    {
      //decrease x pos
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[0][3] = -0.1;
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_O) == GLFW_PRESS)
    {
      //increase y pos
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[2][3] = 0.1;
      p->applyMat(trnsformation);
    }
    if(glfwGetKey(window,GLFW_KEY_U) == GLFW_PRESS)
    {
      //increase y pos
      IdentityMatrix trnsformation = IdentityMatrix(4);
      trnsformation[2][3] = -
                            0.1;
      p->applyMat(trnsformation);
    }
    lastTime = currentTime;
    cout << "FPS: " << 1 / deltaTime << endl;
    delete[] v;
    delete[] c;

  } while (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
  //delete p;
}
