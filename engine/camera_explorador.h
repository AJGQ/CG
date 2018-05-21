#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include <math.h>

#ifndef CAMERA_EXPLORADOR_H
#define CAMERA_EXPLORADOR_H

void modo_explorador();
void rato_explorador(int botao, int estado, int x, int y);
void mov_rato_explorador(int x, int y);
void teclado_normal_explorador(unsigned char tecla,int x, int y);
void teclado_especial_explorador(int tecla,int x, int y);


#endif
