

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

    numShapes = 96 ;
    s = new Shapes * [numShapes];
    // s[0] = new Triangle(vec3(0,0.4,0),vec3(-0.2,0.2,0),vec3(0.2,0.2,0), vec3(0,0,0));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //floor
    // s[0] = new rectPrism(vec3(-0.983,-0.8629,0.8629), vec3(0.983,-0.8629,0.8629), vec3(0.983,-0.794,0.8629), vec3(-0.983,-0.794,0.8629), vec3(0.5,0.5,0.5), 0.82);  // top layer, depth
    // s[0] = new rectPrism(vec3(-0.5,-0.5,0.5), vec3(0.5,0.5,0.5), vec3(0.5,-0.5,0.5), vec3(-0.5,0.5,0.5), vec3(0.5,0.5,0.5), 0.5);
    s[0] = new rectPrism(vec3(0,0,0), 0.034, 0.822, 1.96, vec3(0.5,0.5,0.5));
    // s[0] = new rectPrism(vec3(0,0,0), 0.2, 0.2, 0.2, vec3(0.5,0.5,0.5));
    // s[1] = new Cylinder(vec3(-10.0,-10.0,-10.0),1.0,0.3,60,vec3(0.5,0.5,0.5));
    // s[2] = new triPrism(vec3(0.5,0,0), vec3(0.7,0,0), vec3(0.6,0.1,0), vec3(0.5,0.5,0.5), 0.3);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //walls x 4 (1r + 1r + (1r + 2t) + (1r + 2t) = shapes)
    //  s[8] = new rectPrism(vec3(0,0.138,0.331), 0.822, 0.822, 0.034, vec3(1,1,1)); //east wall with elevator shaft
    // s[2] = new rectPrism(vec3(0,0.138,-0.331), 0.822, 0.822, 0.034, vec3(1,1,1)); //west wall

    // s[3] = new rectPrism(vec3(0.141,0.136,0), 0.822, 0.034, 1.96, vec3(1,1,1)); //north wall 
    // s[4] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    // s[5] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // s[4] =  new rectPrism(vec3(-0.141,0.136,0), 0.822, 0.034, 1.96, vec3(1,1,1)); //south wall with cutouts
//     s[7] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[8] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    // s[95] = new triPrism(vec3(0.141,0.136,0), vec3(0.7,0,0.922), vec3(0.6,0.1,-0.722), vec3(0,1,0), 0.822);
    s[95] = new triPrism(vec3(0.02,0.08,-0.02), vec3(-0.02,0.08,-0.02), vec3(0,0.14,-0.02), vec3(0,1,0), 0.02);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //small wall x 6 (1 shape each)
    s[1] = new rectPrism(vec3(0.06,0.025,0.1), 0.15, 0.16, 0.0068, vec3(1,1,1));
    s[2] = new rectPrism(vec3(0.0,0.025,0.15), 0.15, 0.0068, 0.160, vec3(1,1,1));
    s[3] = new rectPrism(vec3(0.0,0.025,0.225), 0.15, 0.0068, 0.160, vec3(1,1,1));
    s[4] = new rectPrism(vec3(0.0,0.025,-0.01), 0.15, 0.160, 0.0068, vec3(1,1,1));
    s[5] = new rectPrism(vec3(0.0,0.025,-0.1), 0.15, 0.160, 0.0068, vec3(1,1,1));
    s[6] = new rectPrism(vec3(0.06,0.025,-0.18), 0.15, 0.0068, 0.160, vec3(1,1,1));
//     s[287] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //elevator shaft (1 shape)
    // s[7] = new rectPrism(vec3(0,0.138,0.313), 0.822, 0.618, 0.077, vec3(0.5,0.5,0.5));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //2. cutouts x 6 (11 shapes each)
    //1
    s[7] = new rectPrism(vec3(-0.12,0.019,0.23), 0.068, 0.1, 0.0068, vec3(1,1,1));
    s[8] = new rectPrism(vec3(-0.104,0.019,0.202), 0.068, 0.0068, 0.17, vec3(1,1,1));
    s[9] = new rectPrism(vec3(-0.12,0.019,0.174), 0.068, 0.1, 0.0068, vec3(1,1,1));

    s[10] = new rectPrism(vec3(-0.12,0.019,0.146), 0.068, 0.1, 0.0068, vec3(1,1,1));
    s[11] = new rectPrism(vec3(-0.104,0.019,0.118), 0.068, 0.0068, 0.17, vec3(1,1,1));
    s[12] = new rectPrism(vec3(-0.12,0.019,0.09), 0.068, 0.1, 0.0068, vec3(1,1,1));

    s[13] = new rectPrism(vec3(-0.12,0.019,0.062), 0.068, 0.1, 0.0068, vec3(1,1,1));
    s[14] = new rectPrism(vec3(-0.104,0.019,0.034), 0.068, 0.0068, 0.17, vec3(1,1,1));
    s[15] = new rectPrism(vec3(-0.12,0.019,0.006), 0.068, 0.1, 0.0068, vec3(1,1,1));

    s[16] = new rectPrism(vec3(-0.12,0.019,-0.022), 0.068, 0.1, 0.0068, vec3(1,1,1));
    s[17] = new rectPrism(vec3(-0.104,0.019,-0.05), 0.068, 0.0068, 0.17, vec3(1,1,1));
    s[18] = new rectPrism(vec3(-0.12,0.019,-0.078), 0.068, 0.1, 0.0068, vec3(1,1,1));

    s[19] = new rectPrism(vec3(-0.12,0.019,-0.106), 0.068, 0.1, 0.0068, vec3(1,1,1));
    s[20] = new rectPrism(vec3(-0.104,0.019,-0.134), 0.068, 0.0068, 0.17, vec3(1,1,1));
    s[21] = new rectPrism(vec3(-0.12,0.019,-0.162), 0.068, 0.1, 0.0068, vec3(1,1,1));

    s[22] = new rectPrism(vec3(-0.12,0.019,-0.19), 0.068, 0.1, 0.0068, vec3(1,1,1));
    s[23] = new rectPrism(vec3(-0.104,0.019,-0.218), 0.068, 0.0068, 0.17, vec3(1,1,1));
    s[24] = new rectPrism(vec3(-0.12,0.019,-0.246), 0.068, 0.1, 0.0068, vec3(1,1,1));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //1. chair 1 x 7 (5 shapes each)
    //1
    s[25] = new rectPrism(vec3(-0.125,0.017,0.245), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[26] = new rectPrism(vec3(-0.132,0.01,0.238), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[27] = new rectPrism(vec3(-0.118,0.01,0.238), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[28] = new rectPrism(vec3(-0.132,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[29] = new rectPrism(vec3(-0.118,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));

    s[30] = new rectPrism(vec3(-0.125,0.017,0.161), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[31] = new rectPrism(vec3(-0.132,0.01,0.1603), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[32] = new rectPrism(vec3(-0.118,0.01,0.1603), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[33] = new rectPrism(vec3(-0.132,0.01,0.1617), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[34] = new rectPrism(vec3(-0.118,0.01,0.1617), 0.025, 0.005, 0.005, vec3(0,0,0));

    s[35] = new rectPrism(vec3(-0.125,0.017,0.077), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[36] = new rectPrism(vec3(-0.132,0.01,0.0763), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[37] = new rectPrism(vec3(-0.118,0.01,0.0763), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[38] = new rectPrism(vec3(-0.132,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[39] = new rectPrism(vec3(-0.118,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));

    s[40] = new rectPrism(vec3(-0.125,0.017,-0.007), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[41] = new rectPrism(vec3(-0.132,0.01,0.0), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[42] = new rectPrism(vec3(-0.118,0.01,0.0), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[43] = new rectPrism(vec3(-0.132,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[44] = new rectPrism(vec3(-0.118,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));

    s[45] = new rectPrism(vec3(-0.125,0.017,-0.091), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[46] = new rectPrism(vec3(-0.132,0.01,0.0917), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[47] = new rectPrism(vec3(-0.118,0.01,0.0917), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[48] = new rectPrism(vec3(-0.132,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[49] = new rectPrism(vec3(-0.118,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));

    s[50] = new rectPrism(vec3(-0.125,0.017,-0.175), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[51] = new rectPrism(vec3(-0.132,0.01,0.1757), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[52] = new rectPrism(vec3(-0.118,0.01,0.1757), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[53] = new rectPrism(vec3(-0.132,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));
    s[54] = new rectPrism(vec3(-0.118,0.01,0.252), 0.025, 0.005, 0.005, vec3(0,0,0));

    //poof chair
    s[55] = new Cylinder(vec3(-0.16,0.017,0.24), 0.04, 0.02, 10, vec3(1,1,0));
    s[56] = new Cylinder(vec3(-0.16,0.017,0.34), 0.04, 0.02, 10, vec3(1,1,0));
    s[67] = new rectPrism(vec3(-0.035,0.01,0.096), 0.025, 0.05, 0.05, vec3(0,0,1));

    s[57] = new Cylinder(vec3(0.04,0.017,0.04), 0.04, 0.02, 10, vec3(1,1,0));
    s[58] = new Cylinder(vec3(0.04,0.017,0.16), 0.04, 0.02, 10, vec3(1,1,0));
    s[59] = new Cylinder(vec3(0.12,0.017,0.04), 0.04, 0.02, 10, vec3(1,1,0));
    s[60] = new Cylinder(vec3(0.12,0.017,0.16), 0.04, 0.02, 10, vec3(1,1,0));
    s[61] = new Cylinder(vec3(-0.04,0.017,0.04), 0.04, 0.02, 10, vec3(1,1,0));
    s[62] = new Cylinder(vec3(-0.04,0.017,0.16), 0.04, 0.02, 10, vec3(1,1,0));
    s[63] = new Cylinder(vec3(-0.12,0.017,0.04), 0.04, 0.02, 10, vec3(1,1,0));
    s[64] = new Cylinder(vec3(-0.12,0.017,0.16), 0.04, 0.02, 10, vec3(1,1,0));
    s[65] = new Cylinder(vec3(0.18,0.017,0.09), 0.04, 0.02, 10, vec3(1,1,0));
    s[66] = new Cylinder(vec3(-0.18,0.017,0.09), 0.04, 0.02, 10, vec3(1,1,0));

    s[86] = new rectPrism(vec3(-0.03,0.01,0.035), 0.03, 0.1, 0.05, vec3(0,0,1));
    s[87] = new rectPrism(vec3(0.03,0.01,0.035), 0.03, 0.1, 0.05, vec3(0,0,1));

    s[68] = new Cylinder(vec3(-0.16,0.017,0.60), 0.0045, 0.015, 10, vec3(0,1,0));
    s[69] = new Cylinder(vec3(-0.16,0.018,0.60), 0.08, 0.002, 10, vec3(0,1,0));
    s[70] = new Cylinder(vec3(-0.16,0.059,0.60), 0.0015, 0.03, 10, vec3(0,1,0));

    s[71] = new Cylinder(vec3(-0.16,0.017,0.70), 0.0045, 0.015, 10, vec3(0,1,0));
    s[72] = new Cylinder(vec3(-0.16,0.018,0.70), 0.08, 0.002, 10, vec3(0,1,0));
    s[73] = new Cylinder(vec3(-0.16,0.059,0.70), 0.0015, 0.03, 10, vec3(0,1,0));

    s[74] = new Cylinder(vec3(-0.16,0.017,0.50), 0.0045, 0.015, 10, vec3(0,1,0));
    s[75] = new Cylinder(vec3(-0.16,0.018,0.50), 0.08, 0.002, 10, vec3(0,1,0));
    s[76] = new Cylinder(vec3(-0.16,0.059,0.50), 0.0015, 0.03, 10, vec3(0,1,0));

    s[77] = new Cylinder(vec3(-0.1,0.017,-0.70), 0.0045, 0.015, 10, vec3(0,1,0));
    s[78] = new Cylinder(vec3(-0.1,0.018,-0.70), 0.08, 0.002, 10, vec3(0,1,0));
    s[79] = new Cylinder(vec3(-0.1,0.059,-0.70), 0.0015, 0.03, 10, vec3(0,1,0));

    s[80] = new Cylinder(vec3(0.1,0.017,-0.70), 0.0045, 0.015, 10, vec3(0,1,0));
    s[81] = new Cylinder(vec3(0.1,0.018,-0.70), 0.08, 0.002, 10, vec3(0,1,0));
    s[82] = new Cylinder(vec3(0.1,0.059,-0.70), 0.0015, 0.03, 10, vec3(0,1,0));

    s[83] = new Cylinder(vec3(0,0.017,-0.70), 0.0045, 0.015, 10, vec3(0,1,0));
    s[84] = new Cylinder(vec3(0,0.018,-0.70), 0.08, 0.002, 10, vec3(0,1,0));
    s[85] = new Cylinder(vec3(0,0.059,-0.70), 0.0015, 0.03, 10, vec3(0,1,0));

    s[88] = new rectPrism(vec3(-0.02,0.01,-0.091), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[89] = new rectPrism(vec3(0.0,0.01,-0.091), 0.025, 0.05, 0.05, vec3(0,0,1));
    s[90] = new rectPrism(vec3(0.02,0.01,-0.091), 0.025, 0.05, 0.05, vec3(0,0,1));

    s[91] = new rectPrism(vec3(0.017,0.01,-0.017), 0.06, 0.05, 0.025, vec3(0.65,0.16,0.16));
    s[92] = new rectPrism(vec3(-0.017,0.01,-0.017), 0.06, 0.05, 0.025, vec3(0.65,0.16,0.16));

    s[93] = new rectPrism(vec3(0.055,0.01,-0.165), 0.06, 0.025, 0.05, vec3(0.65,0.16,0.16));
    s[94] = new rectPrism(vec3(0.055,0.01,-0.195), 0.06, 0.025, 0.05, vec3(0.65,0.16,0.16));

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //3. planter box x 11 (5 shapes each)
//     //1
//     s[111] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[112] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[113] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[114] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[115] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[116] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[117] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[118] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[119] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[120] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //3
//     s[121] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[122] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[123] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[124] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[125] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //4
//     s[126] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[127] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[128] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[129] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[130] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //5
//     s[131] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[132] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[133] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[134] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[135] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //6
//     s[136] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[137] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[138] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[139] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[140] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //7
//     s[141] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[142] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[143] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[144] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[145] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //8
//     s[146] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[147] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[148] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[149] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[150] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //9
//     s[151] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[152] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[153] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[154] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[155] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //10
//     s[156] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[157] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[158] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[159] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[160] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //11
//     s[161] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[162] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[163] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[164] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[165] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //4. booth chair x 8 (7 shapes each)
//     //1
//     s[166] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[167] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[168] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[169] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[170] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[171] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[172] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[173] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[174] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[175] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[176] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[177] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[178] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[179] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //3
//     s[180] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[181] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[182] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[183] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[184] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[185] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[186] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //4
//     s[187] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[188] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[189] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[190] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[191] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[192] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[193] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //5
//     s[194] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[195] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[196] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[197] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[198] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[199] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[200] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //6
//     s[201] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[202] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[203] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[204] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[205] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[206] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[207] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //7
//     s[208] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[209] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[210] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[211] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[212] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[213] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[214] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //8
//     s[215] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[216] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[217] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[218] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[219] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[220] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[221] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //5. round poof chair x 14 (1 shape each)
//     //cylinders
//     // s[222] = new 
//     // s[223] = new 
//     // s[224] = new 
//     // s[225] = new 
//     // s[226] = new 
//     // s[227] = new 
//     // s[228] = new 
//     // s[229] = new 
//     // s[230] = new 
//     // s[231] = new 
//     // s[232] = new 
//     // s[233] = new 
//     // s[234] = new 
//     // s[235] = new 

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //6. square poof chair x 4 (1 shape each)
//     s[236] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[237] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[238] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[239] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //7. table x 6 (7 shapes each)
//     //1
//     s[240] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[241] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[242] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[243] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[244] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[245] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[246] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[247] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[248] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[249] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[250] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[251] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[252] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[253] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
//     //3
//     s[254] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[255] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[256] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[257] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[258] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[259] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[260] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
//     //4
//     s[261] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[262] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[263] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[264] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[265] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[266] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[267] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
//     //5
//     s[268] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[269] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[270] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[271] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[272] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[273] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[274] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
    
//     //6
//     s[275] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[276] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[277] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[278] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[279] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[280] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[281] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //small wall x 6 (1 shape each)
//     s[282] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[283] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[284] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[285] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[286] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[287] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //9. table x 3 (3 shapes each)
//     //3 x 3 cylinders
//     // s[288] = new 
//     // s[289] = new 
//     // s[290] = new 
//     // s[291] = new 
//     // s[292] = new 
//     // s[293] = new 
//     // s[294] = new 
//     // s[295] = new 
//     // s[296] = new 

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //10. chair x 6 (14 shapes each)
//     //1
//     s[297] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[298] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[299] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[300] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[301] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[302] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[303] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[304] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 6 cylinders
//     // s[305] = new 
//     // s[306] = new 
//     // s[307] = new 
//     // s[308] = new 
//     // s[309] = new 
//     // s[310] = new 

//     //2
//     s[311] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[312] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[313] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[314] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[315] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[316] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[317] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[318] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 6 cylinders
//     // s[319] = new 
//     // s[320] = new 
//     // s[321] = new 
//     // s[322] = new 
//     // s[323] = new 
//     // s[324] = new 

//     //3
//     s[325] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[326] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[327] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[328] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[329] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[330] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[331] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[332] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 6 cylinders
//     // s[333] = new 
//     // s[334] = new 
//     // s[335] = new 
//     // s[336] = new 
//     // s[337] = new 
//     // s[338] = new 

//     //4
//     s[339] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[340] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[341] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[342] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[343] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[344] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[345] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[346] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 6 cylinders
//     // s[347] = new 
//     // s[348] = new 
//     // s[349] = new 
//     // s[350] = new 
//     // s[351] = new 
//     // s[352] = new 

//     //5
//     s[353] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[354] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[355] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[356] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[357] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[358] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[359] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[360] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 6 cylinders
//     // s[361] = new 
//     // s[362] = new 
//     // s[363] = new 
//     // s[364] = new 
//     // s[365] = new 
//     // s[366] = new 

//     //6
//     s[367] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[368] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[369] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[370] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[371] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[372] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[373] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[374] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 6 cylinders
//     // s[375] = new 
//     // s[376] = new 
//     // s[377] = new 
//     // s[378] = new 
//     // s[379] = new 
//     // s[380] = new 

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //11. chair x 6 (11 shapes each)
//     //1
//     s[381] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[382] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[383] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[384] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[385] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[386] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[387] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[388] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[389] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[390] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[391] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[392] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[393] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[394] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[395] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[396] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[397] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[398] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[399] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[400] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[401] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[402] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //3
//     s[403] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[404] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[405] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[406] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[407] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[408] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[409] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[410] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[411] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[412] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[413] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //4
//     s[414] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[415] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[416] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[417] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[418] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[419] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[420] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[421] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[422] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[423] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[424] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //5
//     s[425] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[426] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[427] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[428] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[429] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[430] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[431] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[432] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[433] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[434] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[435] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //6
//     s[436] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[437] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[438] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[439] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[440] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[441] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[442] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[443] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[444] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[445] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[446] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //12. table x 6 (4 shapes each)
//     //1
//     s[447] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[448] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[449] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[450] = new

//     //2
//     s[451] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[452] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[453] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[454] = new

//     //3
//     s[455] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[456] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[457] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[458] = new
    
//     //4
//     s[459] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[460] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[461] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[462] = new

//     //5
//     s[463] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[464] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[465] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[466] = new

//     //6
//     s[467] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[468] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[469] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[470] = new


//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //13. chair x 6 (7 shapes each)
//     //1
//     s[471] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[472] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[473] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[474] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[475] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[476] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[477] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[478] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[479] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[480] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[481] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[482] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[483] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[484] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //3
//     s[485] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[486] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[487] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[488] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[489] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[490] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[491] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //4
//     s[492] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[493] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[494] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[495] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[496] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[497] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[498] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //5
//     s[499] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[500] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[501] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[502] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[503] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[504] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[505] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //6
//     s[506] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[507] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[508] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[509] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[510] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[511] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[512] = new triPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //14. glass wall/door x 9 (5 shapes each)
//     //1
//     s[513] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[514] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[515] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[516] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[517] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[518] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[519] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[520] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[521] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[522] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //3
//     s[523] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[524] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[525] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[526] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[527] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //4
//     s[528] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[529] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[530] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[531] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[532] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //5
//     s[533] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[534] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[535] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[536] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[537] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //6
//     s[538] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[539] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[540] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[541] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[542] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //7
//     s[543] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[544] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[545] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[546] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[547] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //8
//     s[548] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[549] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[550] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[551] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[552] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //9
//     s[553] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[554] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[555] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[556] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[557] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //15. table x 2 (5 shapes each)
//     //1
//     s[558] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[559] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[560] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[561] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[562] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[563] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[564] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[565] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[566] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[567] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

    
//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //16. table x 3 (5 shapes each)
//     //1
//     s[568] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[569] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[570] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[571] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[572] = new

//     //2
//     s[573] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[574] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[575] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[576] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[577] = new

//     //3
//     s[578] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[579] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[580] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[581] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     // + 1 cylinder
//     // s[582] = new

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //17. chair x 5 (8 shapes each)
//     //1
//     s[583] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[584] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[585] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[586] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[587] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[588] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[589] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[590] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[591] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[592] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[593] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[594] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[595] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[596] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[597] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[598] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //3
//     s[599] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[600] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[601] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[602] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[603] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[604] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[605] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[606] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //4
//     s[607] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[608] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[609] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[610] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[611] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[612] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[613] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[614] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //5
//     s[615] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[616] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[617] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[618] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[619] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[620] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[621] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[622] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //18. counter x 6 (3 shapes each)
//     //1
//     s[623] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[624] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[625] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //2
//     s[626] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[627] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[628] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //3
//     s[629] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[630] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[631] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //4
//     s[632] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[633] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[634] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //5
//     s[635] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[636] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[637] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     //6
//     s[638] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[639] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[640] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     //19. stairs x 1 (40 steps/up-steps + 6 up poles + 25 horizontal poles = shapes)

//     s[641] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[642] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[643] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[644] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[645] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[646] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[647] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[648] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[649] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[650] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //10
//     s[651] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[652] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[653] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[654] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[655] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[656] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[657] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[658] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[659] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[660] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //20
//     s[661] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[662] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[663] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[664] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[665] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[666] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[667] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[668] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[669] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[670] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //30
//     s[671] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[672] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[673] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[674] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[675] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[676] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[677] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[678] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[679] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);
//     s[680] = new rectPrism(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0.0);  //40

//     // + 6 cylinders
//     // s[681] = new
//     // s[682] = new
//     // s[683] = new
//     // s[684] = new
//     // s[685] = new
//     // s[686] = new 


//     // + 25 cylinders
//     // s[687] = new
//     // s[688] = new
//     // s[689] = new
//     // s[690] = new
//     // s[691] = new 
//     // s[692] = new
//     // s[693] = new
//     // s[694] = new
//     // s[695] = new
//     // s[696] = new 
//     // s[697] = new
//     // s[698] = new
//     // s[699] = new
//     // s[700] = new
//     // s[701] = new 
//     // s[702] = new
//     // s[703] = new
//     // s[704] = new
//     // s[705] = new
//     // s[706] = new 
//     // s[707] = new
//     // s[708] = new
//     // s[709] = new
//     // s[710] = new
//     // s[711] = new 


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

// rectPrism::rectPrism(vec3 p1, vec3 p2, vec3 p3, vec3 p4, vec3 c, double Z) {
//   numShapes = 6;
//   s = new Shapes * [numShapes];
//   s[0] = new Rectangle(p1,p2,p3,p4,c);//Base
//   s[1] = new Rectangle(p1,p2, vec3(p1.x,p1.y,p1.z+Z), vec3(p2.x,p2.y,p2.z+Z),c);//back face
//   s[2] = new Rectangle(p2,p3, vec3(p2.x,p2.y,p2.z+Z), vec3(p3.x,p3.y,p3.z+Z),c);//right face
//   s[3] = new Rectangle(p3,p4, vec3(p3.x,p3.y,p3.z+Z), vec3(p4.x,p4.y,p4.z+Z),c);//front face
//   s[4] = new Rectangle(p4,p1, vec3(p4.x,p4.y,p4.z+Z), vec3(p1.x,p1.y,p1.z+Z),c);//left face
//   s[5] = new Rectangle(vec3(p1.x,p1.y,p1.z-Z), vec3(p2.x,p2.y,p2.z-Z), vec3(p3.x,p3.y,p3.z-Z), vec3(p4.x,p4.y,p4.z-Z),c);

// }

rectPrism::rectPrism(vec3 center, double height, double width, double length, vec3 color)
{
    numShapes = 6;
    s = new Shapes*[numShapes];

    vec3 topPlane = center + vec3(0, height / 2, 0);
    vec3 bottomPlane = center - vec3(0, height / 2, 0);
    vec3 leftPlane = center - vec3(width / 2, 0, 0);
    vec3 rightPlane = center + vec3(width / 2, 0, 0);
    vec3 nearPlane = center - vec3(0, 0, length / 2);
    vec3 farPlane = center + vec3(0, 0, length / 2);

    vec3 nearLeftTop = nearPlane + leftPlane + topPlane;
    vec3 nearRightTop = nearPlane + rightPlane + topPlane;
    vec3 nearLeftBottom = nearPlane + leftPlane + bottomPlane;
    vec3 nearRightBottom = nearPlane + rightPlane + bottomPlane;

    vec3 farLeftTop = farPlane + leftPlane + topPlane;
    vec3 farRightTop = farPlane + rightPlane + topPlane;
    vec3 farLeftBottom = farPlane + leftPlane + bottomPlane;
    vec3 farRightBottom = farPlane + rightPlane + bottomPlane;

    s[0] = new Rectangle(nearLeftTop, nearRightTop, nearLeftBottom, nearRightBottom, color);
    s[1] = new Rectangle(farRightTop, farLeftTop, farRightBottom, farLeftBottom, color);
    s[2] = new Rectangle(farLeftTop, nearLeftTop, farLeftBottom, nearLeftBottom, color);
    s[3] = new Rectangle(nearRightTop, farRightTop, nearRightBottom, farRightBottom, color);
    s[4] = new Rectangle(nearLeftBottom, nearRightBottom, farLeftBottom, farRightBottom, color);
    s[5] = new Rectangle(nearLeftTop, nearRightTop, farLeftTop, farRightTop, color);

}


triPrism::triPrism(vec3 p1, vec3 p2, vec3 p3, vec3 c,double Z) {
  numShapes = 5;
  s = new Shapes * [numShapes];
  s[0] = new Triangle(p1, p2, p3, c);
  s[1] = new Rectangle(vec3(p2.x,p2.y,p2.z-Z) ,p2, vec3(p3.x,p3.y,p3.z-Z),p3,c);
  s[2] = new Triangle(vec3(p1.x,p1.y,p1.z-Z), vec3(p2.x,p2.y,p2.z-Z), vec3(p3.x,p3.y,p3.z-Z),c);
  //s[3] = new Rectangle(vec3(p2.x,p2.y,p2.z-Z),p2,p1, vec3(p1.x,p1.y,p1.z-Z),c);
  s[3] = new Rectangle(vec3(p1.x,p1.y,p1.z-Z),p1,vec3(p2.x,p2.y,p2.z-Z), p2,c);
  s[4] = new Rectangle(p3,vec3(p3.x,p3.y,p3.z-Z), p1, vec3(p1.x,p1.y,p1.z-Z),c);

}

Cylinder::Cylinder(glm::vec3 center, double height, double radius, int numSegments, glm::vec3 color) {
    numShapes = numSegments * 2 + numSegments * 2; // Two triangles per segment for sides and top/bottom
    s = new Shapes * [numShapes];

    glm::vec3 topCenter = center + glm::vec3(0, height / 2, 0);
    glm::vec3 bottomCenter = center - glm::vec3(0, height / 2, 0);

    double angleStep = 2 * M_PI / numSegments;

    for (int i = 0; i < numSegments; ++i) {
        double angle1 = i * angleStep;
        double angle2 = (i + 1) * angleStep;

        glm::vec3 topPoint1 = topCenter + glm::vec3(radius * cos(angle1), 0, radius * sin(angle1));
        glm::vec3 topPoint2 = topCenter + glm::vec3(radius * cos(angle2), 0, radius * sin(angle2));
        glm::vec3 bottomPoint1 = bottomCenter + glm::vec3(radius * cos(angle1), 0, radius * sin(angle1));
        glm::vec3 bottomPoint2 = bottomCenter + glm::vec3(radius * cos(angle2), 0, radius * sin(angle2));

        // Side rectangles (two triangles per segment)
        s[i * 2] = new Triangle(topPoint1, bottomPoint1, topPoint2, color);
        s[i * 2 + 1] = new Triangle(topPoint2, bottomPoint1, bottomPoint2, color);

        // Top circle
        s[numSegments * 2 + i] = new Triangle(topCenter, topPoint1, topPoint2, color);

        // Bottom circle
        s[numSegments * 3 + i] = new Triangle(bottomCenter, bottomPoint2, bottomPoint1, color);
    }
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

mat4 perspective(float fov, float aspect, float near, float far) {
    float tanHalfFov = tan(radians(fov) / 2.0f);
    mat4 result(0.0f);

    result[0][0] = 1.0f / (aspect * tanHalfFov);
    result[1][1] = 1.0f / tanHalfFov;
    result[2][2] = -(far + near) / (far - near);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * far * near) / (far - near);

    return result;
}

mat4 lookAt(vec3 eye, vec3 center, vec3 up) {
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);

    mat4 result(1.0f);
    result[0][0] = s.x;
    result[1][0] = s.y;
    result[2][0] = s.z;
    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[0][2] = -f.x;
    result[1][2] = -f.y;
    result[2][2] = -f.z;
    result[3][0] = -dot(s, eye);
    result[3][1] = -dot(u, eye);
    result[3][2] = dot(f, eye);

    return result;
}