#include "create.h"

extern FILE *outputFile;


//-Graphical Primitives--------------------------------------------------------//

void createPlane(char **argv) {
    fprintf(outputFile,"1\n");                                   // n de arrays
    fprintf(outputFile,"s4\n");                                  // n vertices da fan do topo
    fprintf(outputFile,"-0.5:0:0.5\n");
    fprintf(outputFile,"0.5:0:0.5\n");
    fprintf(outputFile,"-0.5:0:-0.5\n");
    fprintf(outputFile,"0.5:0:-0.5\n");
}

  //----------------------------------------------------//

void drawN64(){
    
    

}

void drawN(int color){
	
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

  //----------------------------------------------------//


void createBox(char **argv) {
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

    //-XY-----------------------//
    for(i=0; i<d; i++){
        for(j=0; j<=d; j++){
            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 ,   i   * dy-y/2.0 , -z/2.0 );
            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 , (i+1) * dy-y/2.0 , -z/2.0 );
        }
    }
    for(i=0; i<d; i++){
        for(j=0; j<=d; j++){
            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 , (i+1) * dy-y/2.0 , z/2.0 );
            fprintf(outputFile, "%f:%f:%f\n", j * dx-x/2.0 ,   i   * dy-y/2.0 , z/2.0 );
        }
    }


    //-XZ-----------------------//
    for(i=0; i<d; i++){
        for(j=0; j<=d; j++){
            fprintf(outputFile, "%f:%f:%f\n",   i   * dx-x/2.0 , -y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "%f:%f:%f\n", (i+1) * dx-x/2.0 , -y/2.0 , j * dz - z/2.0  );
        }
    }
    for(i=0; i<d; i++){
        for(j=0; j<=d; j++){
            fprintf(outputFile, "%f:%f:%f\n", (i+1) * dx-x/2.0 , y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "%f:%f:%f\n",   i   * dx-x/2.0 , y/2.0 , j * dz - z/2.0  );
        }
    }

    //-YZ-----------------------//
    for(i=0; i<d; i++){
        for(j=0; j<=d; j++){
            fprintf(outputFile, "%f:%f:%f\n", -x/2.0 , (i+1) * dy-y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "%f:%f:%f\n", -x/2.0 ,   i   * dy-y/2.0 , j * dz - z/2.0  );
        }
    }
    for(i=0; i<d; i++){
        for(j=0; j<=d; j++){
            fprintf(outputFile, "%f:%f:%f\n", x/2.0 ,   i   * dy-y/2.0 , j * dz - z/2.0  );
            fprintf(outputFile, "%f:%f:%f\n", x/2.0 , (i+1) * dy-y/2.0 , j * dz - z/2.0  );
        }
    }
}

  //----------------------------------------------------//

void createSphere(char **argv) {
	const float radius = atof(argv[2]);
	const int slices = atof(argv[3]);
	const int stacks = atof(argv[4]);
	const float alpha = 360.0/slices; 
    const float beta = 180.0/stacks;

	int i, j;

    fprintf(outputFile,"%d\n", stacks);                             
    fprintf(outputFile,"f%d\n", slices+2);                           
    fprintf(outputFile,"f%d\n", slices+2);                                
    for(i=0; i<stacks-2; i++) fprintf(outputFile , "s%d\n", 2*(slices+1)); 

    // base
    fprintf(outputFile, "0.0:%f:0.0\n", -radius); 
    for(i=0; i<=slices; i++) 
        fprintf(outputFile, "%f:%f:%f\n",cosf(i * alpha * M_PI/180.0)*sinf( beta*M_PI/180.0 )*radius,
                                         -cosf(beta*M_PI/180.0)*radius,
                                         sin(i * alpha * M_PI/180.0)*sinf(beta*M_PI/180.0)*radius);

    // topo
    fprintf(outputFile, "0.0:%f:0.0\n", radius); // vertice topo
    for(i=0; i<=slices; i++) 
        fprintf(outputFile, "%f:%f:%f\n",cosf(i * alpha * M_PI/180.0)*sinf(-beta*M_PI/180.0 )*radius,
                                         cosf(beta*M_PI/180.0)*radius,
                                         -sin(i * alpha * M_PI/180.0)*sinf(-beta*M_PI/180.0 )*radius);



     // body
    for(j=1; j<stacks-1; j++){
        for(i=0; i<=slices; i++){
            fprintf(outputFile,"%f:%f:%f\n",cosf(i*alpha*M_PI/180.0)*sinf(beta*j*M_PI/180.0)*radius,
                                            cosf(beta*j*M_PI/180.0)*radius,
                                            -sinf(beta*j*M_PI/180.0)*sinf(i*alpha*M_PI/180.0)*radius);

            fprintf(outputFile,"%f:%f:%f\n",cosf(i*alpha*M_PI/180.0)*sinf(beta*(j+1)*M_PI/180.0)*radius,
                                            cosf(beta*(j+1)*M_PI/180.0)*radius,
                                            -sinf(i*alpha*M_PI/180.0)*sinf(beta*(j+1)*M_PI/180.0)*radius);
        }
    }
}

  //----------------------------------------------------//
void createCone(char **argv){
    const float radius = atof(argv[2]);
    const float height = atof(argv[3]);
    const int slices = atoi(argv[4]);
    const int stacks = atoi(argv[5]);
    const float angle = 360.0/slices;  

    int i,j;
    float rM, rm, hM, hm;

    fprintf(outputFile,"%d\n", stacks+1);                                   // n de arrays
    fprintf(outputFile,"f%d\n", slices+2);                                  // n vertices da fan do topo
    fprintf(outputFile,"f%d\n", slices+2);                                  // n vertices da fan da base
    for(i=0; i<stacks-1; i++) fprintf(outputFile , "s%d\n", 2*(slices+2));  // n vertices da s

    // base
    fprintf(outputFile, "0.0:0.0:0.0\n"); // vertice da base
    for(i=0; i<=slices; i++) 
        fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle * M_PI/180.0)*radius, 0.0, sinf(i * angle * M_PI/180.0)*radius);

    // topo
    fprintf(outputFile, "0.0:%f:0.0\n", height); // vertice topo
    for(i=0; i<=slices; i++) 
        fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle * M_PI/180.0)*radius*(1.0/stacks), height*((stacks-1.0)/stacks), -sinf(i * angle * M_PI/180.0)*radius*(1.0/stacks));

    // body
    for(j=0; j<stacks-1; j++){
        for(i=0; i<=slices+1; i++){
            rM = radius * ((stacks-(float)j)/stacks);
            hM = height * ((float)j/stacks);
            rm = radius * ((stacks-(float)(j+1))/stacks);
            hm = height * ((float)(j+1)/stacks);
            fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle * M_PI/180.0)*rm, hm, -sinf(i * angle *M_PI/180.0)*rm);
            fprintf(outputFile, "%f:%f:%f\n", cosf(i * angle * M_PI/180.0)*rM, hM, -sinf(i * angle *M_PI/180.0)*rM);
        }
    }
}

//-Extra primitives------------------------------------------------------------//

void createCylinder(char **argv) {
	const float radius = atof(argv[2]);
	const float height = atof(argv[3]);
	const int slices = atof(argv[4]);
	const int stacks = atof(argv[5]);
	const float angle = 360.0/slices; 
    const float h = height/stacks;

	int i, j;

    fprintf(outputFile,"%d\n", stacks+2);                             
    fprintf(outputFile,"f%d\n", slices+2);                           
    fprintf(outputFile,"f%d\n", slices+2);                                
    for(i=0; i<stacks; i++) fprintf(outputFile , "s%d\n", 2*(slices+2)); 

    // base
    fprintf(outputFile, "0.0:%f:0.0\n", -height/2); // vertice da base
    for(i=0; i<=slices; i++) 
        fprintf(outputFile, "%f:%f:%f\n", cos(i * angle * M_PI/180.0)*radius, -height/2.0 , sin(i * angle * M_PI/180.0)*radius);

    // topo
    fprintf(outputFile, "0.0:%f:0.0\n", height/2); // vertice topo
    for(i=0; i<=slices; i++) 
        fprintf(outputFile, "%f:%f:%f\n", cos(i * angle * M_PI/180.0)*radius, height/2.0, -sin(i * angle * M_PI/180.0)*radius);



     // body
    for(j=0; j<stacks; j++){
        for(i=0; i<=slices+1; i++){
            fprintf(outputFile, "%f:%f:%f\n", cos(i * angle * M_PI/180.0)*radius,   j   * h -height/2.0 , sin(i * angle *M_PI/180.0)*radius);
            fprintf(outputFile, "%f:%f:%f\n", cos(i * angle * M_PI/180.0)*radius, (j+1) * h -height/2.0 , sin(i * angle *M_PI/180.0)*radius);
        }
    }
}
    //----------------------------------------------------//

void createN64(char **argv) {

}

    //----------------------------------------------------//

void createAxes(char **argv) {
    // ACHO QUE ISTO FIXE SER UMA FLAH DO GERADOR
    // E ERA PORREIRO DE MUDASSE DE TAMANHO COM A DISTANCIA A CAMERA
}
