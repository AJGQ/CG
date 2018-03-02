
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include "pugixml-1.8/src/pugixml.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;

//-------------------------------------------------------------------------------//

//-Transladacao----//
float tx = 0.0, ty = 0.0, tz = 0.0;

//-Rotacao---------//
float rx = 0.0, ry = 1.0, rz = 0.0;
int ang = 0;

//-Moviento Camera-//
float camH = 0.0, camV = 0.0, camR = 5.0;
float mouX = 0.0,mouY = 0.0;

//-Modo-----------//
int disMode = 1;

vector<const char*> v_models;

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

//-----------------------------------------------------------------//

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

//-----------------------------------------------------------------//

void changeDisplayMode() {
		switch(disMode) {
			case 0:	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
			case 1:	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE ); break;
			case 2:	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );	break;
			default: break;
		}
		glutPostRedisplay();
}

//-----------------------------------------------------------------//

void drawFile(const char* file) {
    char fi[50] = "models/";
    strcat(fi,file);
    FILE* f = fopen(fi, "r");
    if(f) {
        float x,y,z;
        while(fscanf(f,"%f %f %f",&x,&y,&z) != EOF) { glVertex3f(x,y,z); }
        fclose(f);
    }
}

void drawFiles() {
  glBegin(GL_TRIANGLES);
    for(int i = 0; i<v_models.size(); i++) { drawFile((const char*)v_models.at(i)); }
	glEnd();
}

//-----------------------------------------------------------------//

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float cam_x = camR*cosf(camV*(M_PI/180.0))*sinf(camH*(M_PI/180.0));
    float cam_y = camR*sinf(camV*(M_PI/180.0));
    float cam_z = camR*cosf(camV*(M_PI/180.0))*cosf(camH*(M_PI/180.0));

	glLoadIdentity();
    gluLookAt(cam_x,cam_y,cam_z,
            0.0 ,0.0 ,0.0 ,
            0.0f,1.0f,0.0f);

	changeDisplayMode();

	glTranslatef(tx,ty,tz);
	glRotatef(ang,rx,ry,rz);

	drawAxes(2);
	drawFiles();

	glutSwapBuffers();
}

//-Controlos-------------------------------------------------------//

void processKeys (unsigned char key, int xmouse, int ymouse) {

	switch (key) {

		// Mudar o modo de display
		case '1': disMode = 0; break; // GL_POINT
		case '2':	disMode = 1; break; // GL_LINE
		case '3':	disMode = 2; break; // GL_FILL

		// Mudar o objeto de sitio
		case 'w': tx += 0.25; break;
		case 's':	tx -= 0.25; break;
		case 'q':	ty += 0.25; break;
		case 'e':	ty -= 0.25; break;
		case 'a':	tz += 0.25; break;
		case 'd':	tz -= 0.25; break;

		// Transladacao da camera
    case 'u':	rx += 5.0; break;
		case 'j':	rx -= 5.0; break;
		case 'y':	ry += 5.0; break;
		case 'i':	ry -= 5.0; break;
		case 'h':	rz += 5.0; break;
		case 'k':	rz -= 5.0; break;

		case 'n':	ang += 5; break;
		case 'm':	ang -= 5; break;

		default: break;
	}
   glutPostRedisplay(); //request display() call ASAP
}

void processSpecialKeys(int key, int xx, int yy) {
    switch(key) {
        case GLUT_KEY_UP:    camV += 5.0; break;
        case GLUT_KEY_DOWN:  camV -= 5.0; break;
        case GLUT_KEY_LEFT:  camH -= 5.0; break;
        case GLUT_KEY_RIGHT: camH += 5.0; break;
    }
  glutPostRedisplay(); //request display() call ASAP
}

void processMouse (int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouX = x; mouY = y;
    }
}

void mousePress(int x, int y) {
    camH -= x - mouX; camV += y - mouY;
    mouX = x; mouY = y;
    glutPostRedisplay();
}

//----------------------------------------------------------------------//

using namespace std;
using namespace pugi;

void timer(int value) {
	//glutTimerFunc(60, timer, 0); // next timer call milliseconds later
}

int main(int argc, char* argv[]) {
    xml_document doc;

    xml_parse_result result = doc.load_file("../example.xml");
    if(!result) {
        cout << result.description() << endl;
        return -1;
    }

    xml_node models = doc.child("scene");
    cout << models.name() << endl;

    for(xml_node model = models.first_child(); model; model = model.next_sibling()) {

        cout << " " << model.name() << endl;

        for(xml_attribute attr = model.first_attribute(); attr; attr = attr.next_attribute()) {

            cout << "  " << attr.name() << " = " << attr.value() << endl;
            v_models.push_back(attr.value());

        }
    }
    cout << endl;

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
  glutMouseFunc(processMouse);
  glutMotionFunc(mousePress);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// Timer para o fps (e rotacoes automaticas?)
	glutTimerFunc(0, timer, 0);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}

/*
 * ofstream myfile;
 * myfile.open ("example.bin", ios::out);
 */
