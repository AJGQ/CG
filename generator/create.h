
#ifndef CREATE_H
#define CREATE_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void createPlane     (char **argv);
void createBox       (char **argv);
void createInv_Box   (char **argv);
void createSphere    (char **argv);
void createInv_Sphere(char **argv);
void createCone      (char **argv);
void createCylinder  (char **argv);

void createBezier   (char **argv);

void torusPoint(float R, float r, float angle_a, float angle_b, int i, int j);
void createTorus(char **argv);
//void createN64      (char **argv);

#endif
