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
#include <glm/gtc/matrix_transform.hpp>
#include "Shapes.h"
#include "shader.hpp"

using namespace std;
using namespace glm;

const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "u21434558_u21451070", NULL, NULL);

    if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open GLFW window.";
    }
    glfwMakeContextCurrent(window);
    startUpGLEW();
    return window;
}

int main()
{
    GLFWwindow *window;
    try
    {
        window = setUp();
    }
    catch (const char *e)
    {
        cout << e << endl;
        throw;
    }

    glClearColor(1.0f, 0.85f, 0.7f, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint ID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    GLuint ColorBuffer;
    glGenBuffers(1, &ColorBuffer);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);

    // rectPrism *r = new rectPrism(vec3(0.0,0.0,0.0),vec3(0.1,0.0,0.0),vec3(0.1,0.1,0.0),vec3(0.0,0.1,0.0),vec3(0.1,0.0,0.0),0.1);
    //rectPrism *r = new rectPrism(vec3(0,0,0), 0.2, 0.2, 0.2, vec3(0.5,0.5,0.5));

    floorPlan *p = new floorPlan();
    float lightIntensity = 8.0f;
    vec3 lightPosition = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambientLight = vec3(0.2f, 0.2f, 0.2f);

    GLuint lightPositionID = glGetUniformLocation(ID, "lightPosition_worldspace");
    GLuint lightColorID = glGetUniformLocation(ID, "lightColor");
    GLuint ambientLightID = glGetUniformLocation(ID, "ambientLight");

    float radius = 40.0f; // Radius of the orbit
    float speed = 0.5f;   // Speed of the orbit (radians per second)
    vec3 orbitCenter(0.0f, 0.0f, 0.0f);

    double lastTime = glfwGetTime();

    float camX = 30.0f;
    float camY = 30.0f;
    float camZ = 30.0f;
    vec3 cameraPosition = vec3(camX, camY, camZ);
    mat4 ViewMatrix = lookAt(cameraPosition, vec3(0, 0, 0), vec3(0, 1, 0));
    vec3 forward = normalize(vec3(ViewMatrix * vec4(0,0,-1,0)));
    vec3 right = normalize(cross(vec3(0, 1, 0), forward));
    float movementSpeed = 10;
    float camPitch = 30.0f;
    float camYaw = 30.0f;
    do
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(ID);

        GLfloat *v = p->toVertexArray();
        GLfloat *c = p->toColorArray();
        GLfloat *n = p->toNormalArray();

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, p->getNumVertices() * 3 * sizeof(GLfloat), v, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, p->getNumColors() * sizeof(GLfloat), c, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, p->numNormals() * sizeof(GLfloat), n, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        ViewMatrix = lookAt(cameraPosition, cameraPosition + forward, vec3(0, 1, 0));

        mat4 ProjectionMatrix = perspective(radians(90.0f), 1920.0f / 1080.0f, 0.1f, 300.0f);
        mat4 ViewMatrix = lookAt(cameraPosition, vec3(0, 0, 0), vec3(0, 1, 0));
        mat4 ModelMatrix = mat4(1.0);
        mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        GLuint MatrixID = glGetUniformLocation(ID, "MVP");
        GLuint ViewMatrixID = glGetUniformLocation(ID, "V");
        GLuint ModelMatrixID = glGetUniformLocation(ID, "M");

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

        vec3 intenseLightColor = lightColor * lightIntensity;

        glUniform3fv(lightPositionID, 1, &lightPosition[0]);
        glUniform3fv(lightColorID, 1, &lightColor[0]);
        glUniform3fv(ambientLightID, 1, &ambientLight[0]);

        //glDrawArrays(GL_TRIANGLES, 0, r->getNumVertices());
        forward = vec3(ViewMatrix[0][2], ViewMatrix[1][2], ViewMatrix[2][2]);
        forward = normalize(forward);
        right = normalize(cross(vec3(0, 1, 0), forward));

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cameraPosition -= forward * movementSpeed * deltaTime;
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cameraPosition += forward * movementSpeed * deltaTime;
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cameraPosition -= right * movementSpeed * deltaTime;
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cameraPosition += right * movementSpeed * deltaTime;
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            cameraPosition += vec3(0,0.1,0);
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            cameraPosition -= vec3(0,0.1,0);
        }

        // Rotate the camera up or down
        float pitchSpeed = 1.0f; // Adjust this value for the rotation speed
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            camPitch += pitchSpeed * deltaTime; // Increase pitch angle for looking up
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            camPitch -= pitchSpeed * deltaTime; // Decrease pitch angle for looking down
        }

        // Calculate new forward vector based on updated pitch angle
        vec3 forward;
        forward.x = cos(camYaw) * cos(camPitch);
        forward.y = sin(camPitch);
        forward.z = sin(camYaw) * cos(camPitch);
        forward = normalize(forward);

        // Update ViewMatrix with the new viewing angles
        ViewMatrix = lookAt(cameraPosition, cameraPosition + forward, vec3(0, 1, 0));

        bool pressed = false;
        cout<<p->getNumPoints()<<endl;
        if (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && !pressed) {
            glDrawArrays(GL_LINES, 0, p->getNumPoints());
            pressed = true;
        } else if (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && pressed)
        {
        pressed = false;
            glDrawArrays(GL_TRIANGLES,0, p->getNumPoints());

        }else if (!pressed){
            glDrawArrays(GL_TRIANGLES,0, p->getNumPoints());

        }else
        {
            glDrawArrays(GL_LINES, 0, p->getNumPoints());

        }
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = currentTime;
        cout << "FPS: " << 1 / deltaTime << endl;

        delete[] v;
        delete[] c;
        delete[] n;
    } while (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    delete p;
}
