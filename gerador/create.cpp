#include <iostream>
#include "Vertex.h"
#include <vector>
#include <cmath>

extern float alpha;
extern float beta;
extern float radius;
extern float height;


void createPlane(vector<Vertex*> *ret){
    Vertex* a = new Vertex(-0.5   ,0  ,-0.5   );
    Vertex* b = new Vertex(-0.5   ,0  ,0.5    );
    Vertex* c = new Vertex(0.5    ,0  ,0.5    );
    Vertex* d = new Vertex(0.5    ,0  ,-0.5   );

    ret->push_back(a);
    ret->push_back(b);
    ret->push_back(c);

    ret->push_back(a);
    ret->push_back(c);
    ret->push_back(d);
}

float Xc(float r, int i){ return r * sinf(alpha*i); }
float Zc(float r, int i){ return r * cosf(alpha*i); }
float Yc(float h, int j){ return h * j; }

void createCone(vector<Vertex*>* ret, int slices, int stacks){
    Vertex* inicial = new Vertex(0, 0, 0);
    float h = height/stacks;

    alpha = (2*M_PI)/slices;
        
    //base do cone
    for(int i=0; i<slices; i++){
        ret->push_back(inicial);
        ret->push_back(inicial->plus( Xc(radius, i+1), 0, Zc(radius,i+1) ));
        ret->push_back(inicial->plus( Xc(radius, i  ), 0, Zc(radius,i  ) ));
    }

    //faces laterais
    for(int j=0; j<stacks; j++){
        float r  = radius * ( (float)(stacks-j    ) / stacks ); //raio da base inferior (maior)
        float rp = radius * ( (float)(stacks-(j+1)) / stacks ); //raio da base inferior (menor)

        for(int i=0; i<slices; i++){
            ret->push_back(inicial->plus( Xc(r, i+1) ,Yc(h, j  )    ,Zc(r,  i+1) ));
            ret->push_back(inicial->plus( Xc(rp,i+1) ,Yc(h, j+1)    ,Zc(rp, i+1) ));
            ret->push_back(inicial->plus( Xc(r, i  ) ,Yc(h, j  )    ,Zc(r,  i  ) ));

            ret->push_back(inicial->plus( Xc(r, i  ) ,Yc(h, j  )    ,Zc(r,  i  ) ));
            ret->push_back(inicial->plus( Xc(rp,i+1) ,Yc(h, j+1)    ,Zc(rp, i+1) ));
            ret->push_back(inicial->plus( Xc(rp,i  ) ,Yc(h, j+1)    ,Zc(rp, i  ) ));
        }
    }
}

float X(int i, int j){ return radius * cosf(beta*j) * sinf(alpha*i); }
float Z(int i, int j){ return radius * cosf(beta*j) * cosf(alpha*i); }
float Y(int j)       { return radius * sinf(beta*j); }

void createSphere(vector<Vertex*>* ret, int slices, int stacks){
    Vertex* inicial = new Vertex(0, 0, 0);

    alpha= (2*M_PI)/slices;
    beta = M_PI/stacks;
        
    for(int i=0; i<slices; i++){
        for(int j=-stacks/2; j<=stacks/2; j++){
            int ip=i+1, jp=j+1;

            ret->push_back(inicial->plus( X(i,j),   Y(j),   Z(i,j)   ));
            ret->push_back(inicial->plus( X(ip,j),  Y(j),   Z(ip,j)  ));
            ret->push_back(inicial->plus( X(ip,jp), Y(jp),  Z(ip,jp) ));

            ret->push_back(inicial->plus( X(ip,jp), Y(jp),  Z(ip,jp) ));
            ret->push_back(inicial->plus( X(i,jp),  Y(jp),  Z(i,jp)  ));
            ret->push_back(inicial->plus( X(i,j),   Y(j),   Z(i,j)   ));
        }
    }
}


void createBox(vector<Vertex*>* ret, float x, float y, float z, int d){
    //Vertex* inicial = new Vertex(0,0,0);
    Vertex* inicial = new Vertex(-(x/2),  -(y/2),  -(z/2));
    float dx=x/d;
    float dy=y/d;
    float dz=z/d;

    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){
            //paralelo ao plano xy
            ret->push_back(inicial->plus( i * dx     ,j * dy     ,0          ) );
            ret->push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,0          ) );
            ret->push_back(inicial->plus( (i+1) * dx ,j * dy     ,0          ) );

            ret->push_back(inicial->plus( i * dx     ,j * dy     ,0          ) );
            ret->push_back(inicial->plus( i * dx     ,(j+1) * dy ,0          ) );
            ret->push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,0          ) );
            //
            ret->push_back(inicial->plus( i * dx     ,j * dy     ,z          ) );
            ret->push_back(inicial->plus( (i+1) * dx ,j * dy     ,z          ) );
            ret->push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,z          ) );

            ret->push_back(inicial->plus( i * dx     ,j * dy     ,z          ) );
            ret->push_back(inicial->plus( (i+1) * dx ,(j+1) * dy ,z          ) );
            ret->push_back(inicial->plus( i * dx     ,(j+1) * dy ,z          ) );
            
        
            //paralelo ao plano xz
            ret->push_back(inicial->plus( i * dx     ,0          ,j * dz     ) );
            ret->push_back(inicial->plus( (i+1) * dx ,0          ,j * dz     ) );
            ret->push_back(inicial->plus( (i+1) * dx ,0          ,(j+1) * dz ) );

            ret->push_back(inicial->plus( i * dx     ,0          ,j * dz     ) );
            ret->push_back(inicial->plus( (i+1) * dx ,0          ,(j+1) * dz ) );
            ret->push_back(inicial->plus( i * dx     ,0          ,(j+1) * dz ) );
            //
            ret->push_back(inicial->plus( i * dx     ,y          ,j * dz     ) );
            ret->push_back(inicial->plus( (i+1) * dx ,y          ,(j+1) * dz ) );
            ret->push_back(inicial->plus( (i+1) * dx ,y          ,j * dz     ) );

            ret->push_back(inicial->plus( i * dx     ,y          ,j * dz     ) );
            ret->push_back(inicial->plus( i * dx     ,y          ,(j+1) * dz ) );
            ret->push_back(inicial->plus( (i+1) * dx ,y          ,(j+1) * dz ) );
            
            
            //paralelo ao plano yz
            ret->push_back(inicial->plus( 0          ,i * dy     ,j * dz     ) );
            ret->push_back(inicial->plus( 0          ,(i+1) * dy ,(j+1) * dz ) );
            ret->push_back(inicial->plus( 0          ,(i+1) * dy ,j * dz     ) );
                                                   
            ret->push_back(inicial->plus( 0          ,i * dy     ,j * dz     ) );
            ret->push_back(inicial->plus( 0          ,i * dy     ,(j+1) * dz ) );
            ret->push_back(inicial->plus( 0          ,(i+1) * dy ,(j+1) * dz ) );
            //
            ret->push_back(inicial->plus( x          ,i * dy     ,j * dz     ) );
            ret->push_back(inicial->plus( x          ,(i+1) * dy ,j * dz     ) );
            ret->push_back(inicial->plus( x          ,(i+1) * dy ,(j+1) * dz ) );
                                               
            ret->push_back(inicial->plus( x          ,i * dy     ,j * dz     ) );
            ret->push_back(inicial->plus( x          ,(i+1) * dy ,(j+1) * dz ) );
            ret->push_back(inicial->plus( x          ,i * dy     ,(j+1) * dz ) );
        }
    }
}

         
         
         
        

