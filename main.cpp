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

//-Transladacao-//
float tx = 0.0, ty = 0.0, tz = 0.0;

//-Rotacao-----//
float rx = 0.0, ry = 1.0, rz = 0.0;
int ang = 0;

vector<const char*> v_models;

float angle_a = 0.0, angle_b = 0.0, cam_raio = 5.0;
float mouse_x = 0.0,mouse_y = 0.0;
  


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

void drawFile(const char* file){
    char fi[50] = "models/";
    strcat(fi,file);
    FILE* f = fopen(fi, "r");
    if(f){
        float x,y,z;
        while(fscanf(f,"%f %f %f",&x,&y,&z) != EOF){
            glVertex3f(x,y,z);
        }
        fclose(f);
    }
}


//----------------------------------------------------------------------//

void drawFiles() {
	glBegin(GL_TRIANGLES);

	//----------------------------------------------------------------------//
    for(int i = 0; i<v_models.size(); i++){
        drawFile((const char*)v_models.at(i));
    }
	//----------------------------------------------------------------------//

	glEnd();
}

//----------------------------------------------------------------------//

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float cam_x = cam_raio*cosf(angle_b*(M_PI/180.0))*sinf(angle_a*(M_PI/180.0));
    float cam_y = cam_raio*sinf(angle_b*(M_PI/180.0));
    float cam_z = cam_raio*cosf(angle_b*(M_PI/180.0))*cosf(angle_a*(M_PI/180.0));

	// set the camera
	glLoadIdentity();
    gluLookAt(cam_x,cam_y,cam_z,
            0.0,0.0,0.0,
            0.0f,1.0f,0.0f);

	glTranslatef(tx,ty,tz);
	glRotatef(ang,rx,ry,rz);

	drawAxes(2);
	drawFiles();

	// End of frame
	glutSwapBuffers();
}

//----------------------------------------------------------------------//

void processKeys (unsigned char key, int xmouse, int ymouse) {
	switch (key){

		// Mudar o objeto de sitio
		case 'w':   tx += 0.25; break;
		case 's':	tx -= 0.25; break;
		case 'q':	ty += 0.25; break;
		case 'e':	ty -= 0.25; break;
		case 'a':	tz += 0.25; break;
		case 'd':	tz -= 0.25; break;

		// Mudar a camera
			// Nao percebo porque e que ele abranda...
	    case 'u':	rx += 5.0; break;
		case 'j':	rx -= 5.0; break;
		case 'y':	ry += 5.0; break;
		case 'i':	ry -= 5.0; break;
		case 'h':	rz += 5.0; break;
		case 'k':	rz -= 5.0; break;

		// Ele trata de converter negativos sozinho
		case 'n':	ang += 5; break;
		case 'm':	ang -= 5; break;

		default:
         break;
	}
   glutPostRedisplay(); //request display() call ASAP
}

//----------------------------------------------------------------------//

void processSpecialKeys(int key, int xx, int yy) {

}

void processMouse (int button, int state, int x, int y){
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


//----------------------------------------------------------------------//

using namespace std;
using namespace pugi;

int main(int argc, char* argv[]){
    xml_document doc;

    xml_parse_result result = doc.load_file("../example.xml");
    if(!result){
        cout << result.description() << endl;
        return -1;
    }

    xml_node models = doc.child("scene");
    cout << models.name() << endl;
    
    for(xml_node model = models.first_child(); model; model = model.next_sibling()){

        cout << " " << model.name() << endl;
        
        for(xml_attribute attr = model.first_attribute(); attr; attr = attr.next_attribute()){
            
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

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouse);
    glutMotionFunc(mousePress);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}

/*
 * ofstream myfile;
 * myfile.open ("example.bin", ios::out);
 */
