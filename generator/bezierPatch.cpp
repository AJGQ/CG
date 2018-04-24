
#include "bezierPatch.h"

extern FILE* outputfile;
FILE* inputFile;



void cross(float *a, float *b, float *res) {
	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
    res[3] = 0;
}

void normalize(float *a) {
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
    a[3] = 1;
}

void multVectorMatrix(float *v, float *m, float *res) {
	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[k * 4 + j];
		}
	}
}

void multMatrixMatrix(float* m1, float* m2, float *res){
    for(int i = 0; i<4; i++){
        multVectorMatrix(m1 + i*4, m2, res + i*4);
    }
}

void tranpose(float* m, float* res){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            res[i + 4*j] = m[j + 4*i];
        }
    
    }
}
      
void multMatrixVector(float *m, float *v, float *res) {
	for (int i = 0; i < 4; i++) {
		res[i] = 0;
		for (int j = 0; j < 4; j++) {
			res[i] += m[i+ j * 4] * v[j];
		}
	}
}

void multMatrixVertex_Matrix(float){

}
      

void readPatch(int **patch){
    *patch = (int*)malloc(16 * sizeof(int));
    for(int i=0; i<16; i++) fscanf(inputFile, "%d, ", &(*patch)[i]);
    fscanf(inputFile, "%d", &(*patch)[15]);
}

void readVertex(float **vertex){
    *vertex = (float*)malloc(3 * sizeof(float));
    for(int i=0; i<3; i++) fscanf(inputFile, "%f, ", &(*vertex)[i]);
    fscanf(inputFile, "%f", &(*vertex)[3]);
}


void getBezierPoint(float u, float v, float *patch, float *pos/*, float *deriv*/) {
    float M[4*4]= { -1,  3, -3, 1,
                     3, -6,  3, 0,
                    -3,  3,  0, 0,
                     1,  0,  0, 0      
                  };
    float MT[4*4];
    float A[4*4], B[4*4], C[4*4];
    float U[4] = {u*u*u, u*u, u, 1};
    float V[4] = {v*v*v, v*v, v, 1};
    tranpose(M, MT);

    multMatrixVector(MT, V, A);

    multMatrixMatrix(patch, A, B);

    multMatrixMatrix(M ,B, C);

    multVectorMatrix(U, V, pos);

}

void getPatch(int* indexes, float** vertexes, float* res){
    for(int i=0; i<16; i++){
        for(int j=0; j<3; j++){
            res[j + 16*i] = vertexes[indexes[i]][j];
        }
        res[4 + i*16] = 1;
    }
    
}

void drawPatch(float* patch, int slices){
    int u, v;
    float step = 1/slices;
    float vertex[3];
    for(u=0; u<slices; u++){
        for(v=0; v<slices; v++){
            getBezierPoint(u*step,      v*step,      patch, vertex);
            fprintf(stderr, "%f %f %f\n",vertex[0], vertex[1], vertex[2]);
            getBezierPoint((u+1)*step,  (v+1)*step,  patch, vertex);
            getBezierPoint((u+1)*step,  v*step,      patch, vertex);

            getBezierPoint(u*step,      v*step,      patch, vertex);
            getBezierPoint((u+1)*step,  (v+1)*step,  patch, vertex);
            getBezierPoint(u*step,      (v+1)*step,  patch, vertex);
        }
    }
}


void createBezier(char **argv) {
    FILE* inputFile = fopen(argv[2], "r");
    int slices, nPatch, nVertex, **indexes;
    float** vertexes;
    float patch[16*4];

    slices = atoi(argv[3]);


    if(!inputFile){
        fprintf(stderr, "error: opening input file\n");
        exit(0);
    }
	// read file
    fscanf(inputFile, "%d", &nPatch);
    fprintf(stderr, "%d\n", nPatch);
    indexes = (int**)malloc(nPatch * sizeof(int*));
    for(int i=0; i<nPatch; i++) readPatch(&indexes[i]);
    
    fscanf(inputFile, "%d", &nVertex);
    vertexes = (float**)malloc(nVertex * sizeof(float*));
    for(int i=0; i<nVertex; i++) readVertex(&vertexes[i]);

    for(int i=0; i<nPatch; i++){
        getPatch(indexes[i], vertexes, patch); 
        drawPatch(patch, slices);
    }
}


    
