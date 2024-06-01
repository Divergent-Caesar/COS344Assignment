#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono> 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shapes.h"
#include "shader.hpp"



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

  GLuint ID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
  /*GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader , 1, &SimpleVertexShader, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader , 1, &SimpleFragmentShader, NULL);
  glCompileShader(fragmentShader);*/


  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  GLuint ColorBuffer;
  glGenBuffers(1, &ColorBuffer);

  GLuint normalbuffer;
  glGenBuffers(1, &normalbuffer);

  floorPlan* p = new floorPlan();

  //lighting declarations
  vec3 lightPosition = vec3(0.0f, 5.0f, -10.0f);
  vec3 lightColor = vec3(1.0f, 1.0f, 1.1f);
  vec3 ambientLight = vec3(0.8f, 0.8f, 0.8f);

  GLuint lightPositionID = glGetUniformLocation(ID, "lightPosition_worldspace");
  GLuint lightColorID = glGetUniformLocation(ID, "lightColor");
  GLuint ambientLightID = glGetUniformLocation(ID, "ambientLight");

  double lastTime;
  lastTime = glfwGetTime();
  do {
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(ID);
    GLfloat *v = p->toVertexArray();
    GLfloat *c = p->toColorArray();
    GLfloat *n = p->toNormalArray();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[p->getNumVertices()]), v,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[p->getNumColors()]), c,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, p->numNormals() * sizeof(GLfloat), n, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    //here we will put the perspective matrix
    mat4 ProjectionMatrix = perspective(radians(160.0f), 1.0f / 1.0f, 0.1f, 100.0f);
    mat4 ViewMatrix = lookAt(vec3(0, 0, 20), vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 ModelMatrix = mat4(1.0);
    mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    GLuint MatrixID = glGetUniformLocation(ID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(ID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(ID, "M");

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        
    // Pass the lighting parameters to the shaders
    glUniform3fv(lightPositionID, 1, &lightPosition[0]);
    glUniform3fv(lightColorID, 1, &lightColor[0]);
    glUniform3fv(ambientLightID, 1, &ambientLight[0]);

    glDrawArrays(GL_TRIANGLES,0, p->getNumVertices());
    /*if (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && !pressed) {
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

    }*/

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glfwSwapBuffers(window);
    glfwPollEvents();
    lastTime = currentTime;
    cout << "FPS: " << 1 / deltaTime << endl;
    delete[] v;
    delete[] c;

  } while (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
  //delete p;
}
