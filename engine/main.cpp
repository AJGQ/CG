#include <iostream>
#include <fstream>
#include <stdio.h>
#include "scene.h"
#include "camera_fps.h"
#include "camera_explorador.h"

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
GLuint normalBuff[1];
//float *arrayFloat=NULL;

//vector<const char*> fileNameModels;
Scene* scene;

//-Camera--------//
extern float raio;
float alpha = 0.0, beta = 0.0, radius = 20.0;
float camX, camY, camZ;
float mouX = 0.0, mouY = 0.0;
int tipo_camera=1;

//-Display-------//
int disMode = GL_FILL;
//int disColor = 0; //white
int axes = 0;
int trajetorias = 1;

//-FPS Counter---//
int frame = 0;
int timebase = 0;


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


//-----------------------------------------------------------------------------//

void drawAxes() {
    glBegin(GL_LINES);

    glColor3f(1, 0, 0); //-RED----//
    glVertex3f(0         , 0, 0);
    glVertex3f(0.5*raio, 0, 0);

    glColor3f(0, 1, 0); //-GREEN-//
    glVertex3f(0, 0         , 0);
    glVertex3f(0, 0.5*raio, 0);

    glColor3f(0, 0, 1); //-BLUE-//
    glVertex3f(0, 0, 0         );
    glVertex3f(0, 0, 0.5*raio);

    glColor3f(1, 1, 1); //-WHITE-//
    glEnd();
}



// -Menu de operação-----------------------------------------------------------//
void menu_op(int op){ // unsigned char op, int xx, int yy
    switch (op) {
        // Mudar o modo de display
        case 1: disMode = GL_POINT; break; // GL_POINT
        case 2: disMode = GL_LINE;  break; // GL_LINE
        case 3: disMode = GL_FILL;  break; // GL_FILL
        case 4: //modo fps
            glutKeyboardFunc(teclado_normal_fps);
            glutSpecialFunc(teclado_especial_fps);
            glutMouseFunc(rato_fps);
            glutMotionFunc(mov_rato_fps);
            tipo_camera = 2; 
            break;

        case 5: //modo explorador
            glutKeyboardFunc(teclado_normal_explorador);
            glutSpecialFunc(teclado_especial_explorador);
            glutMouseFunc(rato_explorador);
            glutMotionFunc(mov_rato_explorador);
            tipo_camera = 1; 
            break;

        case 6: axes = 1 - axes; break;
        case 7: trajetorias = 1 - trajetorias; break;

        default:
            break;
    }
    spherical2Cartesian();
    glPolygonMode(GL_FRONT, disMode);
    glutPostRedisplay();
}

//-Render----------------------------------------------------------------------//

void renderScene(void) {
    printFPS();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutPostRedisplay();

    glLoadIdentity();
    gluLookAt(
      camX, camY, camZ,
      0.0 , 0.0 , 0.0 ,
      0.0f, 1.0f, 0.0f);

    if (tipo_camera==1) { modo_explorador();}
    else if(tipo_camera==2) { modo_fps();}

    if (axes) { drawAxes(); }

    //
    //float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    //


    //setColor();
    scene->draw();
    glutSwapBuffers();
}

//-----------------------------------------------------------------------------//

int main(int argc, char** argv) {
    int Menu_Visual, Menu_Camera;

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

    // Default camera
    glutKeyboardFunc(teclado_normal_explorador);
    glutSpecialFunc(teclado_especial_explorador);
    glutMouseFunc(rato_explorador);
    glutMotionFunc(mov_rato_explorador);

    
    // Menu
        Menu_Visual=glutCreateMenu(menu_op);
        glutAddMenuEntry("GL POINT",1);
        glutAddMenuEntry("GL LINE",2);
        glutAddMenuEntry("GL FILL",3);
        glutAddMenuEntry("Mostra Eixos",6);
        glutAddMenuEntry("Mostra Trajetorias",7);
        
        Menu_Camera=glutCreateMenu(menu_op);
        glutAddMenuEntry("Modo FPS",4);
        glutAddMenuEntry("Modo Explorador",5);

         
        glutCreateMenu(menu_op);
        glutAddSubMenu("Visualizacao",Menu_Visual);
        glutAddSubMenu("Camera",Menu_Camera);

        //Activar pop-up Menu
        glutAttachMenu(GLUT_RIGHT_BUTTON);

    // OpenGL settings
#ifndef __APPLE__
    glewInit();
#endif
    glGenBuffers(1, buffers);
    glGenBuffers(1, normalBuff);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_RESCALE_NORMAL);

    spherical2Cartesian();

    // Enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
