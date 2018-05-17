
#include "create.h"

extern FILE *outputFile;

//-Graphical Primitives--------------------------------------------------------//

void createPlane(char **argv) {
    fprintf(outputFile,"1\n");              // num de arrays
    fprintf(outputFile,"s4\n");             // num vertices da fan do topo

    fprintf(outputFile,"-0.5:0:0.5\n");
    fprintf(outputFile,"0:1:0\n");
    fprintf(outputFile,"0:1\n");

    fprintf(outputFile,"0.5:0:0.5\n");
    fprintf(outputFile,"0:1:0\n");
    fprintf(outputFile,"1:1\n");
    
    fprintf(outputFile,"-0.5:0:-0.5\n");
    fprintf(outputFile,"0:1:0\n");
    fprintf(outputFile,"0:0\n");
    
    fprintf(outputFile,"0.5:0:-0.5\n");
    fprintf(outputFile,"0:1:0\n");
    fprintf(outputFile,"1:0\n");
}

//---------------------------//

void createBox(char **argv, int inv) {
    const float x = atof(argv[2]);
    const float y = atof(argv[3]);
    const float z = atof(argv[4]);
    const int d = atof(argv[5]);

    int i, j;
    float dx = x/d;
    float dy = y/d;
    float dz = z/d;

    fprintf(outputFile, "%d\n", d*6);
    for(i=0; i<d*6; i++) fprintf(outputFile, "s%d\n", 2*(d+1) );

    //-XY----------------------//

    for(i=0; i<d; i++) {
        for(j=0; j<=d; j++) {
            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 ,   i   * dy-y/2.0 , -z/2.0 );
            fprintf(outputFile, "0:0:-%d\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)i/d, (float)j/d);

            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 , (i+1) * dy-y/2.0 , -z/2.0 );
            fprintf(outputFile, "0:0:-%d\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)(i+1)/d, (float)j/d);
        }
    }
    for(i=0; i<d; i++) {
        for(j=0; j<=d; j++) {
            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 , (i+1) * dy-y/2.0 , z/2.0 );
            fprintf(outputFile, "0:0:%d\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)(i+1)/d, (float)j/d);

            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 ,   i   * dy-y/2.0 , z/2.0 );
            fprintf(outputFile, "0:0:%d\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)i/d, (float)j/d);
        }
    }

    //-XZ----------------------//

    for(i=0; i<d; i++) {
        for(j=0; j<=d; j++) {
            fprintf(outputFile, "%f:%f:%f\n",   i   * dx-x/2.0 , -y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "0:-%d:0\n", inv); 
            fprintf(outputFile,"%f:%f\n", (float)i/d, (float)j/d);

            fprintf(outputFile, "%f:%f:%f\n", (i+1) * dx-x/2.0 , -y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "0:-%d:0\n", inv); 
            fprintf(outputFile,"%f:%f\n", (float)(i+1)/d, (float)j/d);
        }
    }
    for(i=0; i<d; i++) {
        for(j=0; j<=d; j++) {
            fprintf(outputFile, "%f:%f:%f\n", (i+1) * dx-x/2.0 , y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "0:%d:0\n", inv); 
            fprintf(outputFile,"%f:%f\n", (float)(i+1)/d, (float)j/d);

            fprintf(outputFile, "%f:%f:%f\n",   i   * dx-x/2.0 , y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "0:%d:0\n", inv); 
            fprintf(outputFile,"%f:%f\n", (float)i/d, (float)j/d);
        }
    }

    //-YZ----------------------//

    for(i=0; i<d; i++) {
        for(j=0; j<=d; j++) {
            fprintf(outputFile, "%f:%f:%f\n", -x/2.0 , (i+1) * dy-y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "-%d:0:0\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)(i+1)/d, (float)j/d);

            fprintf(outputFile, "%f:%f:%f\n", -x/2.0 ,   i   * dy-y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "-%d:0:0\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)i/d, (float)j/d);
        }
    }
    for(i=0; i<d; i++) {
        for(j=0; j<=d; j++) {
            fprintf(outputFile, "%f:%f:%f\n", x/2.0 ,   i   * dy-y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "%d:0:0\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)i/d, (float)j/d);

            fprintf(outputFile, "%f:%f:%f\n", x/2.0 , (i+1) * dy-y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "%d:0:0\n",inv); 
            fprintf(outputFile,"%f:%f\n", (float)(i+1)/d, (float)j/d);
        }
    }
}

//-----------------------------------------------------------------------------//

void createSphere(char **argv, int inv) {

    const float radius = atof(argv[2]);
    const int   slices = atof(argv[3]);
    const int   stacks = atof(argv[4]);
    const float alpha  = 360.0/slices;
    const float beta   = 180.0/stacks;

    int i, j;

    fprintf(outputFile,"%d\n", stacks);
    for(i=0; i<stacks; i++) { fprintf(outputFile , "s%d\n", 2*(slices+1)); }

    for(j=0; j<stacks; j++) {
        for(i=0; i<=slices; i++) {
            fprintf(outputFile,"%f:%f:%f\n",
                    cosf(i*alpha*M_PI/180.0)*sinf(beta*j*M_PI/180.0)*radius,
                    cosf(beta*j*M_PI/180.0)*radius,
                    -sinf(beta*j*M_PI/180.0)*sinf(i*alpha*M_PI/180.0)*radius);
            fprintf(outputFile,"%f:%f:%f\n",
                    cosf(i*alpha*M_PI/180.0)*sinf(beta*j*M_PI/180.0)*inv,
                    cosf(beta*j*M_PI/180.0)*inv,
                    -sinf(beta*j*M_PI/180.0)*sinf(i*alpha*M_PI/180.0)*inv);
            fprintf(outputFile,"%f:%f\n",
                    (float)i/stacks,
                    (float)j/stacks);


            fprintf(outputFile,"%f:%f:%f\n",
                    cosf(i*alpha*M_PI/180.0)*sinf(beta*(j+1)*M_PI/180.0)*radius,
                    cosf(beta*(j+1)*M_PI/180.0)*radius,
                    -sinf(i*alpha*M_PI/180.0)*sinf(beta*(j+1)*M_PI/180.0)*radius);
            fprintf(outputFile,"%f:%f:%f\n",
                    cosf(i*alpha*M_PI/180.0)*sinf(beta*(j+1)*M_PI/180.0)*inv,
                    cosf(beta*(j+1)*M_PI/180.0)*inv,
                    -sinf(i*alpha*M_PI/180.0)*sinf(beta*(j+1)*M_PI/180.0)*inv);
            fprintf(outputFile,"%f:%f\n",
                    (float)i/stacks,
                    (float)(j+1)/stacks);
        }
    }
}

//-----------------------------------------------------------------------------//

void createCone(char **argv) {
  const float radius = atof(argv[2]);
  const float height = atof(argv[3]);
  const int   slices = atoi(argv[4]);
  const int   stacks = atoi(argv[5]);
  const float angle  = 2*M_PI/slices;
  const float normalY= atanf(radius/height);

  int i,j;
  float rM, rm, hM, hm;

  fprintf(outputFile,"%d\n" , stacks+1);                                  // num de arrays
  fprintf(outputFile,"f%d\n", slices+2);                                  // num vertices da fan da base
  for(i=0; i<stacks; i++) fprintf(outputFile , "s%d\n", 2*(slices+2));  // num vertices da s

  //-Base--------------------//

  fprintf(outputFile, "0.0:0.0:0.0\n"); // vertice da base
  fprintf(outputFile, "0.0:-1:0.0\n"); // vertice da base
      fprintf(outputFile, "0.5:0.5\n");
  for(i=0; i<=slices; i++) {
      fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle)*radius, 0.0, sinf(i * angle)*radius);
      fprintf(outputFile, "0:-1:0\n");
      fprintf(outputFile, "%f:%f\n", 0.5 + cosf(i * angle)/2, 0.5 + sinf(i * angle)/2);
  }

  //-Body--------------------//

  for(j=0; j<stacks; j++) {
      for(i=0; i<=slices+1; i++) {
          rM = radius * ((stacks-(float)j)/stacks);
          hM = height * ((float)j/stacks);
          rm = radius * ((stacks-(float)(j+1))/stacks);
          hm = height * ((float)(j+1)/stacks);
          fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle)*rm, hm, -sinf(i * angle)*rm);
          fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle), normalY, -sinf(i * angle));         //normal
          fprintf(outputFile, "%f:%f\n", (float)i/slices, (float)(j+1)/stacks);

          fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle)*rM, hM, -sinf(i * angle)*rM);
          fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle), normalY, -sinf(i * angle));         //normal
          fprintf(outputFile, "%f:%f\n", (float)i/slices, (float)j/stacks);
      }
  }
}

//-Extra primitives------------------------------------------------------------//

void createCylinder(char **argv) {
    const float radius = atof(argv[2]);
    const float height = atof(argv[3]);
    const int slices = atof(argv[4]);
    const int stacks = atof(argv[5]);
    const float angle = 2*M_PI/slices;
    const float h = height/stacks;

    int i, j;

    fprintf(outputFile,"%d\n", stacks+2);
    fprintf(outputFile,"f%d\n", slices+2);
    fprintf(outputFile,"f%d\n", slices+2);
    for(i=0; i<stacks; i++) fprintf(outputFile , "s%d\n", 2*(slices+2));

    //-Base--------------------//
    fprintf(outputFile, "0.0:%f:0.0\n", -height/2); // vertice da base
    fprintf(outputFile, "0.0:-1:0.0\n");
    for(i=0; i<=slices; i++) {
        fprintf(outputFile, "%f:%f:%f\n", cos(i * angle)*radius, -height/2.0 , sin(i * angle)*radius);
        fprintf(outputFile, "0.0:-1:0.0\n");
    }

    //-Topo--------------------//
    fprintf(outputFile, "0.0:%f:0.0\n", height/2); // vertice topo
    fprintf(outputFile, "0.0:1:0.0\n");
    for(i=0; i<=slices; i++) {
        fprintf(outputFile, "%f:%f:%f\n", cos(i * angle)*radius, height/2.0, -sin(i * angle)*radius);
        fprintf(outputFile, "0.0:1:0.0\n");
    }

    //-Body--------------------//
    for(j=0; j<stacks; j++) {
        for(i=0; i<=slices+1; i++) {
            fprintf(outputFile, "%f:%f:%f\n", cos(i * angle)*radius,   j   * h -height/2.0 , sin(i * angle)*radius);
            fprintf(outputFile, "%f:%f:%f\n", cos(i * angle),   j   * h -height/2.0 , sin(i * angle));

            fprintf(outputFile, "%f:%f:%f\n", cos(i * angle)*radius, (j+1) * h -height/2.0 , sin(i * angle)*radius);
            fprintf(outputFile, "%f:%f:%f\n", cos(i * angle),   j   * h -height/2.0 , sin(i * angle));
        }
    }
}

//-Torus---------------------//

void torusPoint(float R, float r, float angle_a, float angle_b, int i, int j){
    fprintf(outputFile, "%f:%f:%f\n", sin(i * angle_a) * (R + r * cos(j * angle_b)),
                                      r * sin(j * angle_b),
                                      cos(i * angle_a) * (R + r * cos(j * angle_b)));

    fprintf(outputFile, "%f:%f:%f\n", sin(i * angle_a) * (cos(j * angle_b)),
                                      sin(j * angle_b),
                                      cos(i * angle_a) * (cos(j * angle_b)));
}

void createTorus(char **argv){
    const float R = atof(argv[2]);
    const float r = atof(argv[3]);
    const int Sl = atoi(argv[4]);
    const int sl = atoi(argv[5]);
    const float angle_a = 2*M_PI / Sl;
    const float angle_b = 2*M_PI / sl;
    
    fprintf(outputFile, "%d\n", Sl);
    for(int i = 0; i<Sl; i++){
        fprintf(outputFile, "s%d\n", 2*(sl+1));
    }

    for(int i = 0; i<Sl; i++){
        for(int j = 0; j<sl+1; j++){
            torusPoint(R,r,angle_a,angle_b,i  ,j  );
            fprintf(outputFile, "%f:%f\n", (float)i/Sl, (float)j/sl);
            torusPoint(R,r,angle_a,angle_b,i+1,j  );
            fprintf(outputFile, "%f:%f\n", (float)(i+1)/Sl, (float)j/sl);
        }
    }

}


//-Nintendo------------------//
/*
void drawN64() {



}

void drawN(int color) {

	//down
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0-5.0/3.0, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0-5.0/3.0, 1.0f);

	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0-5.0/3.0, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 2.0f);
	//up
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 5.0/3.0, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 5.0/3.0, 2.0f);

	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 5.0/3.0, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 1.0f);

	//out
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 0.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);

	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 0.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 0.0f);
	//
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0-5.0/3.0, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 2.0f);

	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 5.0/3.0, 2.0f);
	//
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 3.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 3.0f);

	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 3.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 2.0f);
	//in
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 0.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 0.0f);
	//
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 5.0/3.0, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0-5.0/3.0, 1.0f);

	fprintf(outputFile,"%f:%f:%f\n",1.0f, 5.0/3.0, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0-5.0/3.0, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 1.0f);
	//
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 3.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 3.0f);

	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 2.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 3.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 2.0f);

	//bottom
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 0.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 0.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 1.0f);

	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 0.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 0.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 0.0f, 1.0f);
	//top
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 0.0f);

	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 1.0f);
	fprintf(outputFile,"%f:%f:%f\n",1.0f, 3.0f, 0.0f);
	fprintf(outputFile,"%f:%f:%f\n",0.0f, 3.0f, 0.0f);
}
*/

