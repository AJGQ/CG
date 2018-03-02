#include <iostream>
#include "generatorHeaders/Vertex.h"
#include <vector>
#include <cmath>

//-Points----------------------------------------------------------------------//

Vertex* spherePoint(Vertex* inicial, float radius, float alpha, float beta, int i, int j){
    return inicial->plus( radius * sinf(beta*j) * sinf(alpha*i) ,
                          radius * cosf(beta*j),
                          radius * sinf(beta*j) * cosf(alpha*i) );
}

//-Graphical Primitives--------------------------------------------------------//

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

void createSphere(vector<Vertex*>* ret, float radius, int slices, int stacks) {
    Vertex* inicial = new Vertex(0, 0, 0);

    float alpha = (2*M_PI)/slices;
    float beta  = M_PI/stacks;

    for(int i=0; i<slices; i++){
        int ip = i+1, j=0, jp=1;
        ret->push_back(spherePoint(inicial,radius,alpha,beta, i, j));
        ret->push_back(spherePoint(inicial,radius,alpha,beta, i, jp));
        ret->push_back(spherePoint(inicial,radius,alpha,beta, ip, jp));

        for(j=1; j<stacks-1; j++){
            jp=j+1;

            ret->push_back(spherePoint(inicial,radius,alpha,beta, i, j));
            ret->push_back(spherePoint(inicial,radius,alpha,beta, ip, jp));
            ret->push_back(spherePoint(inicial,radius,alpha,beta, ip, j));

            ret->push_back(spherePoint(inicial,radius,alpha,beta, ip, jp));
            ret->push_back(spherePoint(inicial,radius,alpha,beta, i, j));
            ret->push_back(spherePoint(inicial,radius,alpha,beta, i, jp));
        }
        jp = j+1;

        ret->push_back(spherePoint(inicial,radius,alpha,beta, i, j));
        ret->push_back(spherePoint(inicial,radius,alpha,beta, ip, jp));
        ret->push_back(spherePoint(inicial,radius,alpha,beta, i, jp));
    }
}

//----------------------------------------------------//

void createCone(vector<Vertex*>* ret, float radius, float height, int slices, int stacks) {
    Vertex* inicial = new Vertex(0, -(height/2), 0);

    float h = height/stacks;
    float alpha = (2*M_PI)/slices;

  //-Base------//
    for(int i=0; i<slices; i++){
        ret->push_back(inicial);
        ret->push_back(inicial->plus( radius * sinf(alpha*i+1), 0, radius * cosf(alpha*(i+1)) ));
        ret->push_back(inicial->plus( radius * sinf(alpha*i)  , 0, radius * cosf(alpha*i)     ));
    }

  //-Laterais-//
    for(int j=0; j<stacks; j++){
        float r  = radius * ( (float)(stacks-  j  ) / stacks ); //raio da base inferior (maior)
        float rp = radius * ( (float)(stacks-(j+1)) / stacks ); //raio da base inferior (menor)

        for(int i=0; i<slices; i++){
            ret->push_back(inicial->plus( r * sinf(alpha*i)     , h * j    , r * cosf(alpha*(i+1))  ));
            ret->push_back(inicial->plus( rp * sinf(alpha*(i+1)), h * (j+1), rp * cosf(alpha*(i+1)) ));
            ret->push_back(inicial->plus( r * sinf(alpha*i)     , h * j    , r * cosf(alpha*i)      ));

            ret->push_back(inicial->plus( r * sinf(alpha*i)     , h * j    , r * cosf(alpha*i)      ));
            ret->push_back(inicial->plus( rp * sinf(alpha*(i+1)), h * (j+1), rp * cosf(alpha*(i+1)) ));
            ret->push_back(inicial->plus( rp * sinf(alpha*i)    , h * (j+1), rp * cosf(alpha*i)     ));
        }
    }
}

//-Extra primitives------------------------------------------------------------//

void createCylinder(vector<Vertex*>* ret, float radius, float height, int slices) {

    Vertex* inicial = new Vertex(0, -(height/2), 0);

    float alpha = (2*M_PI)/slices;

  //-Bases----//
    for(int i=0; i<slices; i++){
      //-Up-//
        ret->push_back(inicial);
        ret->push_back(inicial->plus( radius * sinf(alpha*(i+1)), 0, radius * cosf(alpha*(i+1)) ));
        ret->push_back(inicial->plus( radius * sinf(alpha*i)    , 0, radius * cosf(alpha*i)     ));
      //-Down-//
        ret->push_back(inicial->plus( 0                         , height, 0                          ));
        ret->push_back(inicial->plus( radius * sinf(alpha*i)    , height, radius * cosf(alpha*i)     ));
        ret->push_back(inicial->plus( radius * sinf(alpha*(i+1)), height, radius * cosf(alpha*(i+1)) ));
    }

  //-Laterais-//
    for(int i=0; i<slices; i++){
      //-Up-//
        ret->push_back(inicial->plus( radius * sinf(alpha*(i+1)), 0     , radius * cosf(alpha*(i+1))      ));
        ret->push_back(inicial->plus( radius * sinf(alpha*(i+1)), height, radius * cosf(alpha*(i+1)) ));
        ret->push_back(inicial->plus( radius * sinf(alpha*i)    , 0     , radius * cosf(alpha*i)     ));
      //-Down-//
        ret->push_back(inicial->plus( radius * sinf(alpha*i)    , 0     , radius * cosf(alpha*i)     ));
        ret->push_back(inicial->plus( radius * sinf(alpha*(i+1)), height, radius * cosf(alpha*(i+1)) ));
        ret->push_back(inicial->plus( radius * sinf(alpha*i)    , height, radius * cosf(alpha*i)     ));
    }
}

    //----------------------------------------------------//

void createAxes(vector<Vertex*>* ret) {
    // ACHO QUE ISTO FIXE SER UMA FLAH DO GERADOR
    // E ERA PORREIRO DE MUDASSE DE TAMANHO COM A DISTANCIA A CAMERA
}
