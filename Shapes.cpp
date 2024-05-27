

#include "Shapes.h"
Shapes::~Shapes() {
    // delete pointers

}
int Shapes::getNumPoints() {
    int c = 0;
    for (int i = 0; i < numShapes; ++i) {
        c += s[i]->getNumPoints();
    }
    return c;
}
GLfloat *Shapes::toVertexArray() {

    int n = getNumVertices();
    GLfloat * r = new GLfloat [n];
    if (numShapes >0)
    {
        // for complex shapes
        int count =0;
        for (int i = 0; i < numShapes; ++i) {
            GLfloat * t = s[i]->toVertexArray();
            for (int j = 0; j < s[i]->getNumVertices(); ++j) {
                r[count++] = t[j];
            }
            delete[]t;
        }
    } else
    {
        // for simple shapes
        int count =0;
        for (int i = 0; i < getNumPoints(); ++i) {
            r[count++] = (*vertices[i])[0];
            r[count++] = (*vertices[i])[1];
            r[count++] = (*vertices[i])[2];
        }

    }
    return r;
}


GLfloat *Shapes::toColorArray() {
    GLfloat * r = new GLfloat [getNumColors()];
    if (numShapes >0)
    {
        // for complex shapes
        int count =0;
        for (int i = 0; i < numShapes; ++i) {
            GLfloat  *t = s[i]->toColorArray();
            for (int j = 0; j < s[i]->getNumColors(); ++j) {
                r[count++] = t[j];
            }

            //delete[]t;
        }
    } else
    {

        // for simple shapes
        int count =0;
        for (int i = 0; i < getNumPoints(); ++i) {
            r[count++] = colors[i][0];
            r[count++] = colors[i][1];
            r[count++] = colors[i][2];
        }

    }
    return r;
}
int Shapes::getNumVertices() {
    int total =0;
    for (int i = 0; i < numShapes; ++i) {
        total+= s[i]->getNumVertices();
    }
    return total;
}
int Shapes::getNumColors() {
    int total =0;
    for (int i = 0; i < numShapes; ++i) {
        total+= s[i]->getNumColors();
    }
    return total;
}


Triangle::Triangle(vec3 p1,vec3 p2, vec3 p3, vec3 color) {
    //base shape
    numShapes=0;
    s = new Shapes*[numShapes];

    int n = getNumPoints();
    vertices = new vec3 * [n];

    //storing vertices in vertices array
    vertices[0] = new vec3(p1);
    vertices[1] = new vec3(p2);
    vertices[2] = new vec3(p3);


    //storing triangle colors in color array
   /* double ** colorArr = new double * [n];
    for (int i = 0; i <n ; ++i) {
        colorArr[i] = new double [3];
        for (int j = 0; j < 3; ++j) {
            colorArr[i][j] = color[j];
        }
    }
    colors = new Matrix(n,3,colorArr);*/
    colors = new vec3[n];
    for (int i = 0; i < 3; i++)
    {
      colors[i] = color;
    }
}
int Triangle::getNumPoints() {
    return 3;
}
int Triangle::getNumVertices() {
    return 9; // 3 points, each 3 coordinates
}
int Triangle::getNumColors() {
    return 9; // 3 points , each 3 colors
}
Rectangle::Rectangle(vec3 p11, vec3 p12, vec3 p13, vec3 p21, vec3 color) {
    numShapes = 2; // 2 triangles
    s = new Shapes * [numShapes];
    s[0] = new Triangle(p12,p11,p13,color);
    s[1] = new Triangle(p13,p21,p12,color);
    int n = getNumPoints();
    vertices = new vec3 * [n];
    int c =0;
    for (int i = 0; i < numShapes; ++i) {
        for (int j = 0; j < s[i]->getNumPoints(); ++j) {
            vertices[c++] = s[i]->vertices[j];
        }
    }

    /*double ** colorArr = new double * [n];
    for (int i = 0; i < n; ++i) {
        colorArr [i] = new double [3];
        for (int j = 0; j < 3; ++j) {
            colorArr[i][j] = color[j];
        }
    }
    colors = new Matrix(n,3,colorArr);*/
    colors = new vec3[n];

    for (int i = 0; i < n; i++)
    {
      colors[i] = color;
    }
}
/*Circle::Circle(double radius, int triangles, Vector middleP,Vector p1,Vector color) {
    numShapes = triangles;
    s = new Shapes * [numShapes];
   // Vector ** arrV = new Vector*[triangles+2];
    for (int i = 0; i < triangles; ++i) {
       double xb = radius*cos((i+1)*(360/triangles)*3.14/180)+(1000*middleP.operator[](0));
       double yb = radius*sin((i+1)*(360/triangles)*3.14/180)+(1000*middleP.operator[](1));
        Vector rotated = generateVectors(xb,yb);
        s[i] = new Triangle(middleP,rotated,p1,color);
        p1.operator[](0) = xb/1000;
        p1.operator[](1) = yb/1000;

    }
}*/

floorPlan::floorPlan(){}() {
  numShapes = 0;
  s = new Shapes * [numShapes];



}


/*cone::cone(double radius, int triangles, vec3 middleP, vec3 p1, vec3 color, double moveBack) {
  numShapes = triangles;
  s = new Shapes *[numShapes];
  for (int i = 0; i < triangles; ++i) {
    double xb = radius * cos((i + 1) * (360 / triangles) * 3.14 / 180) +
                (1000 * middleP.operator[](0));
    double yb = radius * sin((i + 1) * (360 / triangles) * 3.14 / 180) +
                (1000 * middleP.operator[](1));

    vec3 rotated = vec3(xb, yb,0);
    double *middleArr = new double[3];
    middleArr[0] = middleP[0] - moveBack;
    middleArr[1] = middleP[1] ;
    middleArr[2] = middleP[2] ;
    vec3 middlePBack = vec3( middleArr[0],middleArr[1],middleArr[2]);
    s[i] = new Triangle(middlePBack, rotated, p1, color);
    p1.operator[](0) = xb / 1000;
    p1.operator[](1) = yb / 1000;
  }
}*/

rectPrism::rectPrism(vec3 p1, vec3 p2, vec3 p3, vec3 p4, vec3 c, double Z) {
  numShapes = 6;
  s = new Shapes * [numShapes];
  s[0] = new Rectangle(p1,p2,p3,p4,c);
  s[1] = new Rectangle(p1,p2, vec3(p1.x,p1.y,p1.z-Z), vec3(p2.x,p2.y,p2.z-Z),c);
  s[2] = new Rectangle(p2, vec3(p2.x,p2.y,p2.z-Z),p4, vec3 (p4.x,p4.y,p4.z-Z),c);
  s[3] = new Rectangle(p4, vec3(p4.x,p4.y,p4.z-Z),p3, vec3 (p3.x,p3.y,p3.z-Z),c);
  s[4] = new Rectangle(p3, vec3(p3.x,p3.y,p3.z-Z),p1, vec3(p1.x,p1.y,p1.z-Z),c);
  s[5] = new Rectangle(vec3(p1.x,p1.y,p1.z-Z), vec3(p2.x,p2.y,p2.z-Z), vec3(p3.x,p3.y,p3.z-Z), vec3(p4.x,p4.y,p4.z-Z),c);

}

triPrism::triPrism(vec3 p1, vec3 p2, vec3 p3, vec3 c,double Z) {
  numShapes = 5;
  s = new Shapes * [numShapes];
  s[0] = new Triangle(p1, p2, p3, c);
  s[1] = new Rectangle(vec3(p2.x,p2.y,p3.z-Z) ,p2, vec3(p3.x,p3.y,p3.z-Z),p3,c);
  s[2] = new Triangle(vec3(p1.x,p1.y,p1.z-Z), vec3(p2.x,p2.y,p2.z-Z), vec3(p3.x,p3.y,p3.z-Z),c);
  s[3] = new Rectangle(vec3(p2.x,p2.y,p2.z-Z),p2,p1, vec3(p1.x,p1.y,p1.z-Z),c);
  s[4] = new Rectangle(p1,p3, vec3(p3.x,p3.y,p3.z-Z), vec3(p1.x,p1.y,p1.z-Z),c);

}

/*vec3 Shapes::subtractZ(vec3 point, double z) {
  double * arr = new double [3];
  arr[0] = point.operator[](0);
  arr[1] = point.operator[](1);
  arr[2] = point.operator[](2) -z;
  return vec3(arr);
}*/






void Shapes::applyMat(mat4x4 t) {
  if (numShapes > 0) {
    for (int i = 0; i < numShapes; ++i) {
      s[i]->applyMat(t);
    }
  } else {
    for (int i = 0; i < numShapes; ++i) {
      (*vertices[i]) = t*vec4((*vertices[i]),1);
    }
  }
}
