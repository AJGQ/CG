
#include "bezierPatch.h"

extern FILE* outputFile;
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

void transpose(float* m, float* res){
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
			res[i] += m[i * 4 + j] * v[j];
		}
	}
}

void scalePoint(float s, float* p, float* res) {
    for (int i = 0; i<3; i++){
        res[i] = p[i] * s; 
    }
}

void sumPoint(float* p, float* res){
    res[0] += p[0];
    res[1] += p[1];
    res[2] += p[2];
}

void multVectorPoints(float *v, float *p, float *res) {
    float aux[4];
	for (int i = 0; i < 4; ++i) {
		res[4*i] = 0;         
		res[4*i + 1] = 0; 
		res[4*i + 2] = 0; 
		res[4*i + 3] = 1; 
		for (int j = 0; j < 4; ++j) {
			//res[i] += v[j] * p[j * 4 + i];
            scalePoint(v[j], p + 4*(4*j + i), aux);
            sumPoint(aux, res + 4*i);
		}
	}
}

void multPointsVector(float* p, float* v, float* res){
    float aux[4];
    res[0] = 0;
    res[1] = 0;
    res[2] = 0;
    res[3] = 1;
    for (int i = 0; i < 4; i++){
        scalePoint(v[i], p + 4*i, aux);
        sumPoint(aux, res);
    }
}

void getBezierPoint(float u, float v, float *patch, float *pos/*, float *deriv*/) {
    float M[4*4]= { -1,  3, -3, 1,
                     3, -6,  3, 0,
                    -3,  3,  0, 0,
                     1,  0,  0, 0      
                  };
    float MT[4*4];
    float A[4], B[4], C[4*4];
    float U[4] = {u*u*u, u*u, u, 1};
    float V[4] = {v*v*v, v*v, v, 1};
    transpose(M, MT);

    // B(U,V) = U*M*P*MT*V
    multVectorMatrix(U, M, A);
    multMatrixVector(MT, V, B);
    multVectorPoints(A, patch, C);
    multPointsVector(C,B,pos);
    //printf("%f %f %f %f\n", pos[0], pos[1], pos[2], pos[3]);

    //multMatrixVector(patch, A, B);
    //multMatrixVector(M ,B, C);
    //multVectorMatrix(U, C, pos);
}

void drawPatch(float* patch, int slices){

    int u, v;
    float step = 1.0/slices;
    float vertex[4];
    for(u=0; u<slices; u++){
        for(v=0; v<slices+1; v++){
            getBezierPoint((u+1)*step,  v*step,  patch, vertex);
            fprintf(outputFile, "%f:%f:%f\n",vertex[0], vertex[1], vertex[2]);
            
            getBezierPoint(u*step,      v*step,      patch, vertex);
            fprintf(outputFile, "%f:%f:%f\n",vertex[0], vertex[1], vertex[2]);
            
            fflush(outputFile);
        }
    }
    //fprintf(stderr, "exit drawPatch\n");
    
}

void getPatch(int* indexes, float** vertexes, float* res){
    int i, j;
    for(i=0; i<16; i++){
        for(j=0; j<3; j++){
            res[j + i*4] = vertexes[indexes[i]][j];
            //fprintf(stderr, "%f, ", res[j+ i*4]);
        }
        res[j + i*4] = 1.0;
        //fprintf(stderr, "%f\n", res[j+ i*4]);
    }
}

void readPatch(int **patch){
    int i, x;
    *patch = (int*)malloc(16 * sizeof(int));
    for(i=0; i<15; i++) fscanf(inputFile, "%d, ", &((*patch)[i]));
    fscanf(inputFile, "%d\n", &((*patch)[i]));
}

void readVertex(float **vertex){
    int i;
    *vertex = (float*)malloc(3 * sizeof(float));
    for(i=0; i<2; i++) fscanf(inputFile, " %f,", &((*vertex)[i]));
    fscanf(inputFile, " %f\n", &(*vertex)[i]);
}


void createBezier(char **argv) {
    int i, slices, nPatch, nVertex, **indexes;
    float** vertexes;
    float patch[16*4];

    inputFile = fopen(argv[2], "r");
    slices = atoi(argv[3]);
    if(!inputFile){ fprintf(stderr, "error: opening input file\n"); exit(0); }

    fscanf(inputFile, "%d\n", &nPatch);
    indexes = (int**)malloc(nPatch * sizeof(int*)); 
    for(i=0; i<nPatch; i++) readPatch(&indexes[i]);
    
    fscanf(inputFile, "%d\n", &nVertex);
    vertexes = (float**)malloc(nVertex * sizeof(float*));
    for(i=0; i<nVertex; i++) readVertex(&vertexes[i]);

    //printf("nPatch = %d;\nslices = %d;\n", nPatch, slices);

    fprintf(outputFile, "%d\n", nPatch*slices); 
    for(i = 0; i <  nPatch*slices; i++){
        fprintf(outputFile, "s%d\n", 2*(slices + 1));
    }

    for(i=0; i<nPatch; i++){
        getPatch(indexes[i], vertexes, patch); 
    //fprintf(stderr, "before drawPatch\n");
      drawPatch(patch, slices);
    //fprintf(stderr, "after drawPatch\n");
    }
}

