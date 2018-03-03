#include "create.h"

extern ofstream outputFile;


//-Graphical Primitives--------------------------------------------------------//
/*
void createPlane(vector<Vertex*> *ret) {
    Vertex* a = new Vertex(-0.5, 0, -0.5);
    Vertex* b = new Vertex(-0.5, 0,  0.5);
    Vertex* c = new Vertex( 0.5, 0,  0.5);
    Vertex* d = new Vertex( 0.5, 0, -0.5);

    ret->push_back(a);
    ret->push_back(b);
    ret->push_back(c);

    ret->push_back(a);
    ret->push_back(c);
    ret->push_back(d);
}

  //----------------------------------------------------//

void createBox(vector<Vertex*>* ret, float x, float y, float z, int d) {
    Vertex* inicial = new Vertex(-(x/2), -(y/2), -(z/2));

    float dx = x/d;
    float dy = y/d;
    float dz = z/d;

    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){

          //-XY-----------------------//
            ret->push_back(inicial->plus(   i   *dx,   j   *dy, 0 ));
            ret->push_back(inicial->plus( (i+1) *dx, (j+1) *dy, 0 ));
            ret->push_back(inicial->plus( (i+1) *dx,   j   *dy, 0 ));
            ret->push_back(inicial->plus(   i   *dx,   j   *dy, 0 ));
            ret->push_back(inicial->plus(   i   *dx, (j+1) *dy, 0 ));
            ret->push_back(inicial->plus( (i+1) *dx, (j+1) *dy, 0 ));

            ret->push_back(inicial->plus(   i   *dx,   j   *dy, z ));
            ret->push_back(inicial->plus( (i+1) *dx,   j   *dy, z ));
            ret->push_back(inicial->plus( (i+1) *dx, (j+1) *dy, z ));
            ret->push_back(inicial->plus(   i   *dx,   j   *dy, z ));
            ret->push_back(inicial->plus( (i+1) *dx, (j+1) *dy, z ));
            ret->push_back(inicial->plus(   i   *dx, (j+1) *dy, z ));

          //-XZ-----------------------//
            ret->push_back(inicial->plus(   i   *dx, 0,   j   *dz));
            ret->push_back(inicial->plus( (i+1) *dx, 0,   j   *dz));
            ret->push_back(inicial->plus( (i+1) *dx, 0, (j+1) *dz));
            ret->push_back(inicial->plus(   i   *dx, 0,   j   *dz));
            ret->push_back(inicial->plus( (i+1) *dx, 0, (j+1) *dz));
            ret->push_back(inicial->plus(   i   *dx, 0, (j+1) *dz));

            ret->push_back(inicial->plus(   i   *dx, y,   j   *dz));
            ret->push_back(inicial->plus( (i+1) *dx, y, (j+1) *dz));
            ret->push_back(inicial->plus( (i+1) *dx, y,   j   *dz));
            ret->push_back(inicial->plus(   i   *dx, y,   j   *dz));
            ret->push_back(inicial->plus(   i   *dx, y, (j+1) *dz));
            ret->push_back(inicial->plus( (i+1) *dx, y, (j+1) *dz));

          //-YZ-----------------------//
            ret->push_back(inicial->plus( 0,   i   *dy,   j   *dz));
            ret->push_back(inicial->plus( 0, (i+1) *dy, (j+1) *dz));
            ret->push_back(inicial->plus( 0, (i+1) *dy,   j   *dz));
            ret->push_back(inicial->plus( 0,   i   *dy,   j   *dz));
            ret->push_back(inicial->plus( 0,   i   *dy, (j+1) *dz));
            ret->push_back(inicial->plus( 0, (i+1) *dy, (j+1) *dz));

            ret->push_back(inicial->plus( x,   i   *dy,   j   *dz));
            ret->push_back(inicial->plus( x, (i+1) *dy,   j   *dz));
            ret->push_back(inicial->plus( x, (i+1) *dy, (j+1) *dz));
            ret->push_back(inicial->plus( x,   i   *dy,   j   *dz));
            ret->push_back(inicial->plus( x, (i+1) *dy, (j+1) *dz));
            ret->push_back(inicial->plus( x,   i   *dy, (j+1) *dz));
        }
    }
}

  //----------------------------------------------------//

void createSphere(vector<Vertex*>* ret, int slices, int stacks) {
    Vertex* inicial = new Vertex(0, 0, 0);

    alpha = (2*M_PI)/slices;
    beta  = M_PI/stacks;

    for(int i=0; i<slices; i++){
        for(int j=0; j<stacks; j++){
            int ip=i+1, jp=j+1;

            ret->push_back(inicial->plus( X(i,j)  , Y(j) , Z(i,j)   ));
            ret->push_back(inicial->plus( X(ip,jp), Y(jp), Z(ip,jp) ));
            ret->push_back(inicial->plus( X(ip,j) , Y(j) , Z(ip,j)  ));

            ret->push_back(inicial->plus( X(ip,jp), Y(jp), Z(ip,jp) ));
            ret->push_back(inicial->plus( X(i,j)  , Y(j) , Z(i,j)   ));
            ret->push_back(inicial->plus( X(i,jp) , Y(jp), Z(i,jp)  ));
        }
    }
}

  //----------------------------------------------------//
*/
void createCone(char **argv){
    const float radius = atof(argv[3]);
    const float height = atof(argv[4]);
    const int slices = atoi(argv[5]);
    const int stacks = atoi(argv[6]);
    const float angle = (2*M_PI)/slices;  

    int i,j;
    float rM, rm, hM, hm;

    outputFile << to_string(stacks+1) << endl;                                  // n de arrays
    outputFile << "F" << to_string(slices+2) << ":F" << to_string(slices+2);  // n vertices da fan da base e do topo
    for(i=0; i<(stacks-1); i++) outputFile << ":S" << to_string(slices+2);  // n vertices da fan
    outputFile << endl; 

    outputFile << "F:" << to_string(0.0) + ":" << to_string(height/2) << ":" << to_string(0.0) << endl;   // vertice topo
    outputFile << "F:" << to_string(0.0) + ":" << to_string(-height/2) << ":" << to_string(0.0) << endl;  // vertice da base

    for(i=0; i<=slices; i++){
        outputFile << "0:" << to_string(radius*cosf(angle*i)) + ":" << to_string(height/2) << ":" << to_string(radius*sinf(angle*i)) << endl;
        outputFile << "1:" << to_string(radius*(1/stacks)*cosf(angle*i)) << ":" + to_string(height/2) << ":" << to_string(radius*(1/stacks)*sinf(angle*i)) << endl;
        for(j=1; j<stacks-1; j++){
            rM = radius * (j/stacks);
            hM = height * (j/stacks);
            rm = radius * (j+1/stacks);
            hm = height * (j+1/stacks);
            outputFile << to_string(j+1) << ":" << to_string(rm*cosf(angle*i)) << ":" << to_string((height/2)+hm) << ":" << to_string(rm*sinf(angle*i)) << endl;
            outputFile << to_string(j+1) << ":" << to_string(rM*cosf(angle*i)) << ":" << to_string((height/2)+hM) << ":" << to_string(rM*sinf(angle*i)) << endl;
        }
    }
}

//-Extra primitives------------------------------------------------------------//
/*
void createCylinder(vector<Vertex*>* ret, int slices) {

    Vertex* inicial = new Vertex(0, -(height/2), 0);

    alpha = (2*M_PI)/slices;

  //-Bases----//
    for(int i=0; i<slices; i++){
      //-Up-//
        ret->push_back(inicial);
        ret->push_back(inicial->plus( Xc(radius, i+1), 0, Zc(radius,i+1) ));
        ret->push_back(inicial->plus( Xc(radius,  i ), 0, Zc(radius, i ) ));
      //-Down-//
        ret->push_back(inicial->plus( 0              , height, 0              ));
        ret->push_back(inicial->plus( Xc(radius,  i ), height, Zc(radius, i ) ));
        ret->push_back(inicial->plus( Xc(radius, i+1), height, Zc(radius,i+1) ));
    }

  //-Laterais-//
    for(int i=0; i<slices; i++){
      //-Up-//
        ret->push_back(inicial->plus( Xc(radius, i+1), 0     , Zc(radius,i+1) ));
        ret->push_back(inicial->plus( Xc(radius, i+1), height, Zc(radius,i+1) ));
        ret->push_back(inicial->plus( Xc(radius,  i ), 0     , Zc(radius, i ) ));
      //-Down-//
        ret->push_back(inicial->plus( Xc(radius,  i ), 0     , Zc(radius, i ) ));
        ret->push_back(inicial->plus( Xc(radius, i+1), height, Zc(radius,i+1) ));
        ret->push_back(inicial->plus( Xc(radius,  i ), height, Zc(radius, i ) ));
    }
}
*/
    //----------------------------------------------------//

void createN64(char **argv) {

}

    //----------------------------------------------------//

void createAxes(char **argv) {
    // ACHO QUE ISTO FIXE SER UMA FLAH DO GERADOR
    // E ERA PORREIRO DE MUDASSE DE TAMANHO COM A DISTANCIA A CAMERA
}
