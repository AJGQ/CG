#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "picking.h"
#include "scene.h"
#include <stdio.h>

extern Scene* scene;
//-Texto dos Objetos---//

int picking(int x, int y, float camX, float camY, float camZ) {

    int res[4];
    //Preparation
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
            0.0,0.0,0.0,
            0.0f,1.0f,0.0f);

    glDepthFunc(GL_LEQUAL);

    // draw
    scene->draw();

    glDepthFunc(GL_LESS);

    //Tracking
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(x, viewport[3]- y, 1, 1,
            GL_RGBA, GL_UNSIGNED_BYTE, res);

    //Recover
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    return res[0];
}

void renderText() {

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // set projection so that coordinates match window pixels
    gluOrtho2D(0, 800, 800, 0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);

    glPushMatrix();
    glLoadIdentity();
    glRasterPos2d(10, 20);
    // text position in pixels

    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

