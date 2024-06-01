

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

int Shapes::numNormals()
{
    return getNumVertices();
}

/**
 * Returns the normal for the shape
*/
GLfloat *Shapes::toNormalArray()
{
    GLfloat *result = new GLfloat[numNormals()];
    if (numShapes > 0)
    {
        int count = 0;
        for (int i = 0; i < numShapes; i++)
        {
            GLfloat *temp = s[i]->toNormalArray();
            for (int j = 0; j < s[i]->numNormals(); j++)
            {
                result[count++] = temp[j];
            }
            delete[] temp;
        }
    }
    else
    {
        int count = 0;
        for (int i = 0; i < getNumPoints(); i+=3)
        {
            vec3 normal = normalize(cross((*vertices[i + 1]) - (*vertices[i]), (*vertices[i + 2]) - (*vertices[i])));
            for (int j = 0; j < 3; j++)
            {
                result[count++] = normal[0];
                result[count++] = normal[1];
                result[count++] = normal[2];
            }
        }
    }
    return result;
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

            delete[]t;
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

floorPlan::floorPlan() {
    //712 shapes total at the moment

    numShapes = 1 ;
    s = new Shapes * [numShapes];
    s[0] = new Triangle(vec3(0,0.4,0),vec3(-0.2,0.2,0),vec3(0.2,0.2,0), vec3(0,0,0));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //floor
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //what is the double

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //walls x 4 (1r + 1r + (1r + 2t) + (1r + 2t) = shapes)
    // s[1] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0); //east wall with elevator shaft
    // s[2] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0); //west wall

    // s[3] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0); //north wall 
    // s[4] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[5] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // s[6] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0); //south wall with cutouts
    // s[7] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[8] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //elevator shaft (1 shape)
    // s[9] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //1. chair 1 x 7 (5 shapes each)
    // //1
    // s[10] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[11] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[12] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[13] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[14] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[15] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[16] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[17] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[18] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[19] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[20] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[21] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[22] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[23] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[24] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[25] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[26] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[27] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[28] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[29] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[30] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[31] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[32] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[33] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[34] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[35] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[36] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[37] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[38] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[39] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //7
    // s[40] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[41] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[42] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[43] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[44] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //2. cutouts x 6 (11 shapes each)
    // //1
    // s[45] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[46] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[47] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[48] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[49] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[50] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[51] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[52] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[53] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[54] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[55] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[56] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[57] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[58] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[59] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[60] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[61] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[62] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[63] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[64] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[65] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[66] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[67] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[68] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[69] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[70] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[71] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[72] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[73] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[74] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[75] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[76] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[77] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[78] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[79] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[80] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[81] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[82] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[83] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[84] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[85] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[86] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[87] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[88] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5 
    // s[89] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[90] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[91] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[92] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[93] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[94] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[95] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[96] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[97] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[98] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[99] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[100] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[101] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[102] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[103] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[104] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[105] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[106] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[107] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[108] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[109] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[110] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //3. planter box x 11 (5 shapes each)
    // //1
    // s[111] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[112] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[113] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[114] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[115] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[116] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[117] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[118] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[119] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[120] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[121] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[122] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[123] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[124] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[125] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[126] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[127] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[128] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[129] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[130] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[131] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[132] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[133] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[134] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[135] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[136] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[137] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[138] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[139] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[140] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //7
    // s[141] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[142] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[143] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[144] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[145] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //8
    // s[146] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[147] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[148] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[149] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[150] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //9
    // s[151] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[152] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[153] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[154] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[155] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //10
    // s[156] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[157] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[158] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[159] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[160] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //11
    // s[161] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[162] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[163] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[164] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[165] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //4. booth chair x 8 (7 shapes each)
    // //1
    // s[166] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[167] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[168] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[169] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[170] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[171] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[172] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[173] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[174] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[175] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[176] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[177] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[178] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[179] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[180] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[181] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[182] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[183] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[184] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[185] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[186] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[187] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[188] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[189] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[190] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[191] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[192] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[193] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[194] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[195] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[196] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[197] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[198] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[199] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[200] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[201] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[202] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[203] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[204] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[205] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[206] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[207] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //7
    // s[208] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[209] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[210] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[211] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[212] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[213] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[214] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //8
    // s[215] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[216] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[217] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[218] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[219] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[220] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[221] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //5. round poof chair x 14 (1 shape each)
    // //cylinders
    // // s[222] = new 
    // // s[223] = new 
    // // s[224] = new 
    // // s[225] = new 
    // // s[226] = new 
    // // s[227] = new 
    // // s[228] = new 
    // // s[229] = new 
    // // s[230] = new 
    // // s[231] = new 
    // // s[232] = new 
    // // s[233] = new 
    // // s[234] = new 
    // // s[235] = new 

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //6. square poof chair x 4 (1 shape each)
    // s[236] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[237] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[238] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[239] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //7. table x 6 (7 shapes each)
    // //1
    // s[240] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[241] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[242] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[243] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[244] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[245] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[246] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[247] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[248] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[249] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[250] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[251] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[252] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[253] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
    // //3
    // s[254] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[255] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[256] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[257] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[258] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[259] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[260] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
    // //4
    // s[261] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[262] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[263] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[264] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[265] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[266] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[267] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
    // //5
    // s[268] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[269] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[270] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[271] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[272] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[273] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[274] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
    // //6
    // s[275] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[276] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[277] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[278] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[279] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[280] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[281] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //small wall x 6 (1 shape each)
    // s[282] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[283] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[284] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[285] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[286] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[287] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //9. table x 3 (3 shapes each)
    // //3 x 3 cylinders
    // // s[288] = new 
    // // s[289] = new 
    // // s[290] = new 
    // // s[291] = new 
    // // s[292] = new 
    // // s[293] = new 
    // // s[294] = new 
    // // s[295] = new 
    // // s[296] = new 

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //10. chair x 6 (14 shapes each)
    // //1
    // s[297] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[298] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[299] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[300] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[301] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[302] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[303] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[304] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 6 cylinders
    // // s[305] = new 
    // // s[306] = new 
    // // s[307] = new 
    // // s[308] = new 
    // // s[309] = new 
    // // s[310] = new 

    // //2
    // s[311] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[312] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[313] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[314] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[315] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[316] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[317] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[318] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 6 cylinders
    // // s[319] = new 
    // // s[320] = new 
    // // s[321] = new 
    // // s[322] = new 
    // // s[323] = new 
    // // s[324] = new 

    // //3
    // s[325] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[326] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[327] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[328] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[329] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[330] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[331] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[332] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 6 cylinders
    // // s[333] = new 
    // // s[334] = new 
    // // s[335] = new 
    // // s[336] = new 
    // // s[337] = new 
    // // s[338] = new 

    // //4
    // s[339] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[340] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[341] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[342] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[343] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[344] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[345] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[346] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 6 cylinders
    // // s[347] = new 
    // // s[348] = new 
    // // s[349] = new 
    // // s[350] = new 
    // // s[351] = new 
    // // s[352] = new 

    // //5
    // s[353] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[354] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[355] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[356] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[357] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[358] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[359] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[360] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 6 cylinders
    // // s[361] = new 
    // // s[362] = new 
    // // s[363] = new 
    // // s[364] = new 
    // // s[365] = new 
    // // s[366] = new 

    // //6
    // s[367] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[368] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[369] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[370] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[371] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[372] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[373] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[374] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 6 cylinders
    // // s[375] = new 
    // // s[376] = new 
    // // s[377] = new 
    // // s[378] = new 
    // // s[379] = new 
    // // s[380] = new 

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //11. chair x 6 (11 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //12. table x 6 (4 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder

    // //3
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder//1
    
    // //4
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder

    // //5
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder

    // //6
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder


    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //13. chair x 6 (7 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //14. glass wall/door x 9 (5 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //7
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //8
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //9
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //15. table x 2 (5 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //16. table x 3 (5 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder

    // //3
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // // + 1 cylinder

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //17. chair x 5 (8 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //18. counter x 6 (3 shapes each)
    // //1
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //2
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //3
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //4
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //5
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // //6
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //19. stairs x 1 (40 steps/up-steps + 6 up poles + 25 horizontal poles = shapes)

    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //10
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //20
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //30
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[0] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //40

    // + 6 cylinders

    // + 25 cylinders


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
