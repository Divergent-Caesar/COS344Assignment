

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <iostream>

#ifndef PRAC2_SHAPES_H
#define PRAC2_SHAPES_H

using namespace glm;
using namespace std;

struct Shapes {
    vec3** vertices; //stores vertices of shape
    vec3* colors; //stores color of shape
    Shapes** s; // array of array of Shapes of triangle/rectangle... to build car
    int numShapes; // number of shapes in a shape - 2 in rectangle

    ~Shapes();
    virtual void applyMat(mat4x4 t);
    virtual GLfloat* toVertexArray();
    virtual GLfloat* toColorArray();
    virtual int getNumPoints();
    virtual int getNumVertices();
    virtual int getNumColors();

};

struct Triangle : public Shapes{
    Triangle(vec3 p1,vec3 p2, vec3 p3,vec3 color);
    int getNumPoints();
    int getNumVertices();
    int getNumColors();
};

struct Rectangle: public Shapes
{
    Rectangle(vec3 p11, vec3 p12, vec3 p13, vec3 p21, vec3 color);
};
struct Circle : public Shapes
{
    Circle(double radius, int triangles, vec3 middleP,vec3 p1,vec3 color);
};
struct triPrism:public Shapes{
  triPrism(vec3 p1,vec3 p2, vec3 p3,vec3 c,double Z);
};
struct rectPrism:public Shapes{
  rectPrism(vec3 p1, vec3 p2 ,vec3 p3,vec3 p4, vec3 c,double Z);
};

/*struct cone:public Shapes{
  cone(double radius, int triangles, vec3 middleP,vec3 p1,vec3 color,double moveBack);
};*/
struct floorPlan : public Shapes {
    floorPlan();
};


#endif//PRAC2_SHAPES_H
