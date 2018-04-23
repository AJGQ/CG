
#include "bezierPatch.h"

extern FILE* outputfile;

void readPatch(FILE* inputFile, int **patch){
    *patch = (int*)malloc(16 * sizeof(int));
    for(int i=0; i<16; i++) fscanf(inputFile, "%d, ", &(*patch)[i]);
    fscanf(inputFile, "%d", &(*patch)[15]);
}

void readVertex(FILE* inputFile, float **vertex){
    *vertex = (float*)malloc(3 * sizeof(float));
    for(int i=0; i<3; i++) fscanf(inputFile, "%f, ", &(*vertex)[i]);
    fscanf(inputFile, "%f", &(*vertex)[3]);
}

void createBezier(char **argv) {
    FILE* inputFile = fopen(argv[2], "r");
    int nPatch, nVertex, **patches;
    float** vertexes;

    if(inputFile){
        fprintf(stderr, "error: opening file\n");
        exit(0);
    }

    fscanf(inputFile, "%d", &nPatch);
    patches = (int**)malloc(nPatch * sizeof(int*));
    for(int i=0; i<nPatch; i++) readPatch(inputFile, &patches[i]);
    
    fscanf(inputFile, "%d", &nVertex);
    vertexes = (float**)malloc(nVertex * sizeof(float*));
    for(int i=0; i<nVertex; i++) readVertex(inputFile, &vertexes[i]);


}
