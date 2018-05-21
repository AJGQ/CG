#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES


#ifndef PICKING_H
#define PICKING_H

char text[256] = "Nothing\n";
int tracking = 0;
int picked = 0;

int picking(int, int);
void renderText();

#endif
