#ifndef CATMULL_H
#define CATMULL_H

#include "pugixml-1.8/src/pugixml.hpp"
#include <unistd.h>
#include <string.h>
#include <vector>
#include <math.h>

#define _USE_MATH_DEFINES


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


void cross(float *, float *, float *);


void normalize(float *);


void multVectorMatrix(float *, float *, float *);


void multMatrixMatrix(float *, float *, float *);


void getCatmullRomPoint(float, 
                        float *, float *, float *, float *,
                        float *, float *);


void getGlobalCatmullRomPoint(std::vector<float*>, float, float *, float *);


void renderCatmullRomCurve(std::vector<float*>);


void startPath(std::vector<float*>, float);

#endif
