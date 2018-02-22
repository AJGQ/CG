
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

//-------------------------------------------------------------------------------//

//-Transladacao-//
float tx = 0.0, ty = 0.0, tz = 0.0;

//-Rotacao-----//
float rx = 0.0, ry = 1.0, rz = 0.0;
int ang = 0;

//-Figura------//
int fig;

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

void drawPlaneXZ(float l, float cx=0, float cz=0) {
	glBegin(GL_TRIANGLES);

	//-Trngl 1-//
		glVertex3f(-l/2+cx, 0.0,-l/2+cz);
		glVertex3f(-l/2+cx, 0.0, l/2+cz);
		glVertex3f( l/2+cx, 0.0,-l/2+cz);

	//-Trngl 2-//
		glVertex3f( l/2+cx, 0.0,-l/2+cz);
		glVertex3f(-l/2+cx, 0.0, l/2+cz);
		glVertex3f( l/2+cx, 0.0, l/2+cz);

	glEnd();
}

//----------------------------------------------------------------------//

void drawBox(float x, float y, float z, float div, float cx=0, float cy=0, float cz=0, int wire=0) {

	// Nao sei se devemos fazer com triangulos e/ou fazer mais bonito (rotacoes)
	glBegin(GL_QUADS);

	//-Base Up---//
		glVertex3f(-x/2+cx, y/2+cy,-z/2+cz);
		glVertex3f(-x/2+cx, y/2+cy, z/2+cz);
		glVertex3f( x/2+cx, y/2+cy, z/2+cz);
		glVertex3f( x/2+cx, y/2+cy,-z/2+cz);

	//-Base Down-//
		glVertex3f( x/2+cx,-y/2+cy,-z/2+cz);
		glVertex3f( x/2+cx,-y/2+cy, z/2+cz);
		glVertex3f(-x/2+cx,-y/2+cy, z/2+cz);
		glVertex3f(-x/2+cx,-y/2+cy,-z/2+cz);

	//-Sides-----//
		glVertex3f(-x/2+cx,-y/2+cy,-z/2+cz);
		glVertex3f(-x/2+cx,-y/2+cy, z/2+cz);
		glVertex3f(-x/2+cx, y/2+cy, z/2+cz);
		glVertex3f(-x/2+cx, y/2+cy,-z/2+cz);

		glVertex3f( x/2+cx, y/2+cy,-z/2+cz);
		glVertex3f( x/2+cx,-y/2+cy,-z/2+cz);
		glVertex3f(-x/2+cx,-y/2+cy,-z/2+cz);
		glVertex3f(-x/2+cx, y/2+cy,-z/2+cz);

		glVertex3f( x/2+cx,-y/2+cy, z/2+cz);
		glVertex3f( x/2+cx,-y/2+cy,-z/2+cz);
		glVertex3f( x/2+cx, y/2+cy,-z/2+cz);
		glVertex3f( x/2+cx, y/2+cy, z/2+cz);

		glVertex3f(-x/2+cx, y/2+cy, z/2+cz);
		glVertex3f(-x/2+cx,-y/2+cy, z/2+cz);
		glVertex3f( x/2+cx,-y/2+cy, z/2+cz);
		glVertex3f( x/2+cx, y/2+cy, z/2+cz);

	glEnd();
}

//----------------------------------------------------------------------//

void drawSphere(float rad, int slic, int stks, float cx=0, float cy=0, float cz=0, int wire=0){

}

//----------------------------------------------------------------------//

void drawCone(float rad, float hgt, int slic, int stks, int wire=0){

}

//----------------------------------------------------------------------//

void drawTorus(float inrad, float outrad, int sid, int rng, int wire=0){

}

//----------------------------------------------------------------------//

// Por os outros? 6, 8, 12, 20 faces?

//----------------------------------------------------------------------//

void drawAxes(float cmp){
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
	glEnd();
}

//----------------------------------------------------------------------//

void drawCylinder(float rad, float hgt, int sl, float cx=0, float cy=0, float cz=0, int wire=0) {

	// Depois preciamos de ver como organisar as cores
	glBegin(GL_TRIANGLES);

	for (int x = 0; x < sl; x++){
	  //-Base Down---//
			glVertex3f( rad*sin((x+1)*(M_PI*2/sl))+cx,-1.0*hgt/2+cy, rad*cos((x+1)*(M_PI*2/sl))+cz);
			glVertex3f( rad*sin(  x  *(M_PI*2/sl))+cx,-1.0*hgt/2+cy, rad*cos(  x  *(M_PI*2/sl))+cz);
			glVertex3f( 0.0                       +cx,-1.0*hgt/2+cy, 0.0*rad                   +cz);

	  //-Base Up-----//
			glVertex3f( 0.0                       +cx, 1.0*hgt/2+cy, 0.0*rad                   +cz);
			glVertex3f( rad*sin(  x  *(M_PI*2/sl))+cx, 1.0*hgt/2+cy, rad*cos(  x  *(M_PI*2/sl))+cz);
			glVertex3f( rad*sin((x+1)*(M_PI*2/sl))+cx, 1.0*hgt/2+cy, rad*cos((x+1)*(M_PI*2/sl))+cz);

		//-Trngl Down--//
			glVertex3f(rad*sin((x+1)*(M_PI*2/sl))+cx,-1.0*hgt/2+cy, rad*cos((x+1)*(M_PI*2/sl))+cz);
			glVertex3f(rad*sin(  x  *(M_PI*2/sl))+cx, 1.0*hgt/2+cy, rad*cos(  x  *(M_PI*2/sl))+cz);
			glVertex3f(rad*sin(  x  *(M_PI*2/sl))+cx,-1.0*hgt/2+cy, rad*cos(  x  *(M_PI*2/sl))+cz);

		//-Trngl Up---//
			glVertex3f(rad*sin((x+1)*(M_PI*2/sl))+cx, 1.0*hgt/2+cy, rad*cos((x+1)*(M_PI*2/sl))+cz);
			glVertex3f(rad*sin(  x  *(M_PI*2/sl))+cx, 1.0*hgt/2+cy, rad*cos(  x  *(M_PI*2/sl))+cz);
			glVertex3f(rad*sin((x+1)*(M_PI*2/sl))+cx,-1.0*hgt/2+cy, rad*cos((x+1)*(M_PI*2/sl))+cz);
	}

	glEnd();
}

//----------------------------------------------------------------------//

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0 ,5.0 ,5.0 ,
		        0.0 ,0.0 ,0.0 ,
			      0.0f,1.0f,0.0f);

	glTranslatef(tx,ty,tz);
	glRotatef(ang,rx,ry,rz);

	//drawBox(3,3,3,3);
	drawAxes(2);
	//drawCone(3,3,3,3);
	//drawSphere(3,30,30,3);


	switch (fig){ // Nao funciona :(
		case '1': drawPlaneXZ(0,0,0); break;
		case '2': drawBox(0,0,0,0); break;
		case '3': drawSphere(0,0,0); break;
		case '4': drawCone(0,0,0,0); break;
		case '5': drawCylinder(0,0,0); break;
		// ...

		default:
				 break;
	}

	// End of frame
	glutSwapBuffers();
}

//----------------------------------------------------------------------//

void processKeys (unsigned char key, int xmouse, int ymouse) {
	switch (key){

		// Era suposto dar para mudar a figura para testar mas nao funciona...
		case '1': fig = 1; break;
		case '2': fig = 2; break;
		case '3': fig = 3; break;
		case '4': fig = 4; break;
		case '5': fig = 5; break;

		// Mudar o objeto de sitio
		case 'w': tx += 0.25; break;
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

//----------------------------------------------------------------------//

int main(int argc, char **argv) {

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

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}

/*
 TODO:
	- Figuras que faltam;
	- Ver os wires/cores;
	- N64;
*/
