#include <iostream>
#include "Vertex.h"
#include <vector>
#include <cmath>



vector<Vertex *> createPlane(){
    vector<Vertex*> ret;

    Vertex* a = new Vertex(-0.5   ,0  ,-0.5   );
    Vertex* b = new Vertex(-0.5   ,0  ,0.5    );
    Vertex* c = new Vertex(0.5    ,0  ,0.5    );
    Vertex* d = new Vertex(0.5    ,0  ,-0.5   );

    ret.push_back(a);
    ret.push_back(b);
    ret.push_back(c);

    ret.push_back(a);
    ret.push_back(c);
    ret.push_back(d);

    return ret;
}


vector<Vertex *> createCone(float radius, float height, int slices, int stacks){
    vector<Vertex*> ret;
    Vertex* inicial = new Vertex(0, 0, 0);
    float alpha = (2*M_PI)/slices;
    float h = height/stacks;
        
    for(int i=0; i<slices; i++){
        ret.push_back(inicial);
        ret.push_back(inicial->plus( radius * sinf( alpha * (i+1) ) ,0  , radius * cosf( alpha * (i+1) ) ));
        ret.push_back(inicial->plus( radius * sinf( alpha * i )     ,0  , radius * cosf( alpha * i     ) ));
    }
    for(int j=0; j<stacks; j++){
        float r  = radius * ( (float)(stacks-j    ) / stacks );
        float r2 = radius * ( (float)(stacks-(j+1)) / stacks );
        for(int i=0; i<slices; i++){
            ret.push_back(inicial->plus( r * sinf( alpha * (i+1) ) ,h * j    , r * cosf( alpha * (i+1) ) ));
            ret.push_back(inicial->plus( r2* sinf( alpha * (i+1) ) ,h * (j+1), r2* cosf( alpha * (i+1) ) ));
            ret.push_back(inicial->plus( r * sinf( alpha * i )     ,h * j    , r * cosf( alpha * i     ) ));

            ret.push_back(inicial->plus( r * sinf( alpha * i )     ,h * j    , r * cosf( alpha * i     ) ));
            ret.push_back(inicial->plus( r2* sinf( alpha * (i+1) ) ,h * (j+1), r2* cosf( alpha * (i+1) ) ));
            ret.push_back(inicial->plus( r2* sinf( alpha * i )     ,h * (j+1), r2* cosf( alpha * i     ) ));
        }
    }

    return ret;
}


vector<Vertex *> createSphere(float radius, int slices, int stacks){
    vector<Vertex*> ret;
    Vertex* inicial = new Vertex(0, 0, 0);
    float alpha = (2*M_PI)/slices;
    float beta = M_PI/stacks;
        
    for(int i=0; i<slices; i++){
        for(int j=-stacks/2; j<=stacks/2; j++){
            ret.push_back(inicial->plus( radius*cosf(beta * j)*sinf(alpha * i)          ,radius*sinf(beta * j)      ,radius*cosf(alpha * i)*cosf(beta * j)          ));
            ret.push_back(inicial->plus( radius*cosf(beta * j)*sinf(alpha * (i+1))      ,radius*sinf(beta * j)      ,radius*cosf(alpha * (i+1))*cosf(beta * j)      ));
            ret.push_back(inicial->plus( radius*cosf(beta * (j+1))*sinf(alpha * (i+1))  ,radius*sinf(beta * (j+1))  ,radius*cosf(alpha * (i+1))*cosf(beta * (j+1))  ));

            ret.push_back(inicial->plus( radius*cosf(beta * (j+1))*sinf(alpha * (i+1))  ,radius*sinf(beta * (j+1))  ,radius*cosf(alpha * (i+1))*cosf(beta * (j+1))  ));
            ret.push_back(inicial->plus( radius*cosf(beta * (j+1))*sinf(alpha * i)      ,radius*sinf(beta * (j+1))  ,radius*cosf(alpha * i)*cosf(beta * (j+1))      ));
            ret.push_back(inicial->plus( radius*cosf(beta * j)*sinf(alpha * i)          ,radius*sinf(beta * j)      ,radius*cosf(alpha * i)*cosf(beta * j)          ));
        }
    }

    return ret;
}


vector<Vertex *> createBox(float x, float y, float z, int d){
    vector<Vertex*> ret;
    //Vertex* inicial = new Vertex(0,0,0);
    Vertex* inicial = new Vertex(-(x/2),  -(y/2),  -(z/2));
    float dx=x/d;
    float dy=y/d;
    float dz=z/d;

    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){
            //paralelo ao plano xy
            ret.push_back(inicial->plus( i * dx     ,j * dy     ,0          ) );
            ret.push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,0          ) );
            ret.push_back(inicial->plus( (i+1) * dx ,j * dy     ,0          ) );

            ret.push_back(inicial->plus( i * dx     ,j * dy     ,0          ) );
            ret.push_back(inicial->plus( i * dx     ,(j+1) * dy ,0          ) );
            ret.push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,0          ) );
            //
            ret.push_back(inicial->plus( i * dx     ,j * dy     ,z          ) );
            ret.push_back(inicial->plus( (i+1) * dx ,j * dy     ,z          ) );
            ret.push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,z          ) );

            ret.push_back(inicial->plus( i * dx     ,j * dy     ,z          ) );
            ret.push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,z          ) );
            ret.push_back(inicial->plus( i * dx     ,(j+1) * dy ,z          ) );
            //paralelo ao plano xz
            ret.push_back(inicial->plus( i * dx     ,0          ,j * dz     ) );
            ret.push_back(inicial->plus( (i+1) * dx ,0          ,j * dz     ) );
            ret.push_back(inicial->plus( (i+1) * dx ,0          ,(j+1) * dz ) );

            ret.push_back(inicial->plus( i * dx     ,0          ,j * dz     ) );
            ret.push_back(inicial->plus( (i+1) * dx ,0          ,(j+1) * dz ) );
            ret.push_back(inicial->plus( i * dx     ,0          ,(j+1) * dz ) );
            //
            ret.push_back(inicial->plus( i * dx     ,y          ,j * dz     ) );
            ret.push_back(inicial->plus( (i+1) * dx ,y          ,(j+1) * dz ) );
            ret.push_back(inicial->plus( (i+1) * dx ,y          ,j * dz     ) );

            ret.push_back(inicial->plus( i * dx     ,y          ,j * dz     ) );
            ret.push_back(inicial->plus( i * dx     ,y          ,(j+1) * dz ) );
            ret.push_back(inicial->plus( (i+1) * dx ,y          ,(j+1) * dz ) );
            //paralelo ao plano yz
            ret.push_back(inicial->plus( 0          ,i * dy     ,j * dz     ) );
            ret.push_back(inicial->plus( 0          ,(i+1) * dy ,(j+1) * dz ) );
            ret.push_back(inicial->plus( 0          ,(i+1) * dy ,j * dz     ) );
                                                     
            ret.push_back(inicial->plus( 0          ,i * dy     ,j * dz     ) );
            ret.push_back(inicial->plus( 0          ,i * dy     ,(j+1) * dz ) );
            ret.push_back(inicial->plus( 0          ,(i+1) * dy ,(j+1) * dz ) );
            //
            ret.push_back(inicial->plus( x          ,i * dy     ,j * dz     ) );
            ret.push_back(inicial->plus( x          ,(i+1) * dy ,j * dz     ) );
            ret.push_back(inicial->plus( x          ,(i+1) * dy ,(j+1) * dz ) );
                                                     
            ret.push_back(inicial->plus( x          ,i * dy     ,j * dz     ) );
            ret.push_back(inicial->plus( x          ,(i+1) * dy ,(j+1) * dz ) );
            ret.push_back(inicial->plus( x          ,i * dy     ,(j+1) * dz ) );
        }
    }
    return ret;
}

         
         
         
        

