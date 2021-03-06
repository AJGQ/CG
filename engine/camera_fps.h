#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include <math.h>


#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H


//Modo FPS
void modo_fps();
void teclado_especial_fps(int tecla,int x, int y);
void teclado_normal_fps(unsigned char tecla,int x, int y);
void mov_rato_fps(int x, int y);
void rato_fps(int botao, int estado, int x, int y);

#endif
