
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "parseXML.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//-Globais---------------------------------------------------------------------//

GLuint buffers[1];
float *arrayFloat=NULL;

vector<const char*> fileNameModels;

//-Camera--------//
float alpha = 0.0, beta = 0.0, radius = 10.0;
float camX, camY, camZ;
float mouX = 0.0, mouY = 0.0;

//-Display-------//
int disMode = 1;
int disColor = 0; //white
int axes = 0;

//-FPS Counter---//
int frame = 0;
int timebase = 0;

//-Funcoes---------------------------------------------------------------------//

void error(const char *s) {
   cout << "\e[1;31mError:\e[0;1m" << s << "\e[0m" << endl; _exit(-1);
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
    case '2':	disMode = 1; break; // GL_LINE
    case '3':	disMode = 2; break; // GL_FILL

    case 'w': radius -= 0.1f;
            if (radius < 0.1f) radius = 0.1f;
            break;

    case 's': radius += 0.1f; break;

    case 'x':
        axes = 1 - axes;
        break;

    case 'p': disColor = 4; break; // Pink
    case 'r': disColor = 1; break; // Red
    case 'g': disColor = 2; break; // Green
    case 'b': disColor = 3; break; // Blue
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
    }
}

void mousePress (int x, int y) {
    alpha -= ((float)(x - mouX))/50;
    float aux = beta + ((float)(y - mouY))/50;
    if(aux<M_PI/2 && aux>-M_PI/2)   beta = aux;
    else if( aux>=M_PI/2 )          beta = M_PI/2;
    else                            beta = -M_PI/2;
    mouX = x;
    mouY = y;
    spherical2Cartesian();
    glutPostRedisplay();
}

//-Color-----------------------------------------------------------------------//
void setColor(){
    switch(disColor) {
      case 0:	glColor3f(1.0f,1.0f,1.0f); break; //White
      case 4:	glColor3f(0.737255f,0.560784f,0.560784f); break; //Pink
      case 1:	glColor3f(1.0f,0.0f,0.0f); break; //Red
      case 2:	glColor3f(0.0f,1.0f,0.0f); break; //Green
      case 3:	glColor3f(0.0f,0.0f,1.0f); break; //Blue
    default: break;
  }
}
//-Render----------------------------------------------------------------------//

void renderScene(void) {
  printFPS();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  changeDisplayMode();

	glLoadIdentity();
  gluLookAt(camX, camY, camZ,
            0.0 , 0.0 , 0.0 ,
            0.0f, 1.0f, 0.0f);

	if (axes) { drawAxes(); }

  setColor();
	drawFiles();
	glutSwapBuffers();
}

//-----------------------------------------------------------------------------//

int main(int argc, char** argv) {
  if(argc < 2) error("missing xml file");
  parseXML(argv[1]);

// init GLUT and the window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(800,800);
  glutCreateWindow("CG@DI-UM");

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
  glEnableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

  spherical2Cartesian();

// Enter GLUT's main cycle
  glutMainLoop();

	return 1;
}
