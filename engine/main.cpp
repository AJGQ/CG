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

//-----------------------------------------------------------------------------//

GLuint buffers[1];
float *arrayFloat=NULL;

vector<const char*> fileNameModels;

//-Moviento Camera-//
float alfa = 0.0, beta = 0.0, radius = 5.0;
float camX, camY, camZ;

//-Modo-------//
int disMode = 1;
int axes = 0;

//-----------------------------------------------------------------------------//

void error(const char *s){
        cout << "\e[1;31mError:\e[0;1m" << s << "\e[0m" << endl;
        _exit(-1);
}


//-----------------------------------------------------------------------------//

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
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

//-------------------------------------------------------------------------------//

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// Compute window's aspect ratio
	float ratio = w * 1.0 / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
	// Return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------//

void drawAxes(float cmp) {
	glBegin(GL_LINES);

	glColor3f(1, 0, 0); //-RED----//
	glVertex3f(0      , 0, 0);
	glVertex3f(1.0*cmp, 0, 0);

	glColor3f(0, 1, 0); //-GREEN-//
	glVertex3f(0, 0      , 0);
	glVertex3f(0, 1.0*cmp, 0);

	glColor3f(0, 0, 1); //-BLUE-//
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1.0*cmp);

	glColor3f(1, 1, 1); //-WHITE-//
	glEnd();
}

//----------------------------------------------------------------------//

void processKeys(unsigned char c, int xx, int yy) {

	switch(c){

        // Mudar o modo de display
        case '1': disMode = 0; break; // GL_POINT
        case '2':	disMode = 1; break; // GL_LINE
        case '3':	disMode = 2; break; // GL_FILL

        case 'w': radius -= 0.1f;
                if (radius < 0.1f) radius = 0.1f;
                break;

        case 's': radius += 0.1f; break;
        case 'x': 
            if(axes == 1) axes = 0;
            else axes = 1;
            break;
	}
	spherical2Cartesian();
	glutPostRedisplay();
}

//----------------------------------------------------------------------//

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT: alfa -= 0.1; break;

	case GLUT_KEY_LEFT: alfa += 0.1; break;

	case GLUT_KEY_UP: beta += 0.1f;
		if (beta > 1.5f) beta = 1.5f;
	break;

	case GLUT_KEY_DOWN:beta -= 0.1f;
		if (beta < -1.5) beta = -1.5f;
	break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}

/*void processMouse (int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouse_x = x;
        mouse_y = y;
    }
}

void mousePress(int x, int y){
    angle_a -= x - mouse_x;
    angle_b += y - mouse_y;
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();

}
*/

//----------------------------------------------------------------------//

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  changeDisplayMode();

	// set the camera
	glLoadIdentity();
  gluLookAt(camX, camY, camZ,
            0.0 , 0.0 , 0.0 ,
            0.0f, 1.0f, 0.0f);

	if (axes) { drawAxes(3); }
	drawFiles();

	// End of frame
	glutSwapBuffers();
}

//----------------------------------------------------------------------//

int main(int argc, char** argv){
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
  //glutMouseFunc(processMouse);
  //glutMotionFunc(mousePress);

// OpenGL settings
  #ifndef __APPLE__
  glewInit();
  #endif
  glEnableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

  spherical2Cartesian();

// enter GLUT's main cycle
  glutMainLoop();

	return 1;
}
