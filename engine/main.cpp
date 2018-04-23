
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "scene.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#define POINT_COUNT 4
#define TOTAL_POINTS 100

#include <math.h>

using namespace std;

//-Globais---------------------------------------------------------------------//

GLuint buffers[1];
//float *arrayFloat=NULL;

//vector<const char*> fileNameModels;
Scene* scene;

//-Camera--------//
float alpha = 0.0, beta = 0.0, radius = 20.0;
float camX, camY, camZ;
float mouX = 0.0, mouY = 0.0;

//-Display-------//
int disMode = 1;
//int disColor = 0; //white
int axes = 0;
int trajetorias = 1;

//-FPS Counter---//
int frame = 0;
int timebase = 0;

//-Rotacao ao longo do tempo --//
float p[POINT_COUNT][4] = {{-1,0,-1,1},{-1,0,1,1},{1,0,1,1},{1,0,-1,1}};

//-Funcoes---------------------------------------------------------------------//

void error(const char *s) {
    cerr << "\e[1;31mError:\e[0;1m" << s << "\e[0m" << endl;
    _exit(-1);
}

void spherical2Cartesian() {
    camX = radius * cos(beta) * sin(alpha);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alpha);
}

void printFPS() {
    float fps;
    frame++;
    char title[50];

    int time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        sprintf(title,"%f Um Belo Trabalho",fps);
        glutSetWindowTitle(title);
    }
}

void changeSize(int w, int h) {
    if(h == 0) h = 1;

    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void changeDisplayMode() {
    switch(disMode) {
        case 0:	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
        case 1:	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE ); break;
        case 2:	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );	break;
        default: break;
    }
    glutPostRedisplay();
}

//-Translacao ao longo do tempo------------------------------------------------//

void buildRotMatrix(float *x, float *y, float *z, float *m) {
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2] ; m[3] = 0 ;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2] ; m[7] = 0 ;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0  ; m[13] = 0  ; m[14] = 0   ; m[15] = 1;
}

void printMatrix(float* m){
  printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
    m[0] , m[1] , m[2] , m[3] ,
    m[4] , m[5] , m[6] , m[7] ,
    m[8] , m[9] , m[10], m[11],
    m[12], m[13], m[14], m[15]);
}

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


float length(float *v) {
	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;
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

void getCatmullRomPoint(float t,
                        float *p0, float *p1, float *p2, float *p3,
                        float *pos, float *deriv) {

	// catmull-rom matrix
	float m[16] =  {
    -0.5f,  1.5f, -1.5f,  0.5f,
	   1.0f, -2.5f,  2.0f, -0.5f,
		-0.5f,  0.0f,  0.5f,  0.0f,
		 0.0f,  1.0f,  0.0f,  0.0f
  };

	// Compute A = M * P
	float P[16] = {
    p0[0], p0[1], p0[2], p0[3],
    p1[0], p1[1], p1[2], p1[3],
    p2[0], p2[1], p2[2], p2[3],
    p3[0], p3[1], p3[2], p3[3]};

    float A[16];
    multMatrixMatrix(m,P,A);

	// Compute pos = T * A
    float T[4] = {t*t*t, t*t, t, 1};
    multVectorMatrix(T, A, pos);

	// compute deriv = T' * A
    float T_[4] = {3*t*t, 2*t, 1, 0};
    multVectorMatrix(T_, A, deriv);
}

void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT;
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void renderCatmullRomCurve() {
    glBegin(GL_LINE_LOOP);
    float t;
    float pos[4];
    float deriv[4];
    for(int i= 0; i<TOTAL_POINTS; i++){
        t = ((float)i)/TOTAL_POINTS;
        getGlobalCatmullRomPoint(t, pos, deriv);
        glVertex3f(pos[0],pos[1],pos[2]);
    }

    glEnd();
// desenhar a curva usando segmentos de reta - GL_LINE_LOOP
}

//-----------------------------------------------------------------------------//

void drawAxes() {
    glBegin(GL_LINES);

    glColor3f(1, 0, 0); //-RED----//
    glVertex3f(0         , 0, 0);
    glVertex3f(0.5*radius, 0, 0);

    glColor3f(0, 1, 0); //-GREEN-//
    glVertex3f(0, 0         , 0);
    glVertex3f(0, 0.5*radius, 0);

    glColor3f(0, 0, 1); //-BLUE-//
    glVertex3f(0, 0, 0         );
    glVertex3f(0, 0, 0.5*radius);

    glColor3f(1, 1, 1); //-WHITE-//
    glEnd();
}

//-Controlos-------------------------------------------------------------------//

void processKeys(unsigned char c, int xx, int yy) {

    switch(c) {
        // Mudar o modo de display
        case '1': disMode = 0; break; // GL_POINT
        case '2': disMode = 1; break; // GL_LINE
        case '3': disMode = 2; break; // GL_FILL
        case 'w': radius -= 0.1f;
                  if (radius < 0.1f) radius = 0.1f;
                  break;

        case 's': radius += 0.1f; break;
        case 'x': axes = 1 - axes; break;
        case 'x': trajetorias = 1 - trajetorias; break;

    }
    spherical2Cartesian();
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_RIGHT: alpha -= 0.1; break;
        case GLUT_KEY_LEFT:  alpha += 0.1; break;

        case GLUT_KEY_UP:  beta += 0.1f;
                           if (beta > 1.5f) beta = 1.5f;
                           break;

        case GLUT_KEY_DOWN: beta -= 0.1f;
                            if (beta < -1.5)  beta = -1.5f;
                            break;
    }
    spherical2Cartesian();
    glutPostRedisplay();
}

void processMouse (int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouX = x;
        mouY = y;
    }else if(button == 3){
        radius -= 0.3;
    }else if(button == 4){
        radius += 0.3;
    }
    spherical2Cartesian();
    glutPostRedisplay();

}

void mousePress (int x, int y) {
    alpha -= ((float)(x - mouX))/50;
    float aux = beta + ((float)(y - mouY))/50;
    if(aux<M_PI/2-0.1 && aux>-M_PI/2+0.1)   beta = aux;
    else if( aux>=M_PI/2-0.1 )              beta = M_PI/2-0.1;
    else                                    beta = -M_PI/2+0.1;
    mouX = x;
    mouY = y;
    spherical2Cartesian();
    glutPostRedisplay();
}

//-Render----------------------------------------------------------------------//

void renderScene(void) {
    printFPS();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    changeDisplayMode();

    glLoadIdentity();
    gluLookAt(
      camX, camY, camZ,
      0.0 , 0.0 , 0.0 ,
      0.0f, 1.0f, 0.0f);

    if (axes) { drawAxes(); }

    //setColor();
    scene->draw();
    glutSwapBuffers();
}

//-----------------------------------------------------------------------------//

int main(int argc, char** argv) {
    if(argc < 2) error("missing xml file");
    scene = new Scene(argv[1]);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Um Belo Trabalho");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard and mouse processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouse);
    glutMotionFunc(mousePress);

    // OpenGL settings
#ifndef __APPLE__
    glewInit();
#endif
    glGenBuffers(1, buffers);
    glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    spherical2Cartesian();

    // Enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
