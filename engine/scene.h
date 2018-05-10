
#ifndef SCENE_H
#define SCENE_H

#include "pugixml-1.8/src/pugixml.hpp"
#include "catmull.h"
#include <unistd.h>
#include <string.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace pugi;
using namespace std;

extern GLuint buffers[1];
extern GLuint normalBuff[1];

extern void error(const char *s);

class PhysicScene{
  public:
    //virtual ~PhysicScene() = 0;
    virtual void draw() = 0;
};

class Model {
  public:
    int N;
    int index;
    float *arrayFloat;
    float *arrayNormal;
    int *pos, *len;
    char *typ;
    Model(xml_node);
    void draw();
};

class Translate : public PhysicScene{
    vector<float*> points;
    float time, x, y, z;
  public:
    Translate(xml_node);
    void draw();
};

class Rotate : public PhysicScene{
    float angle, time;
    float x, y, z;
  public:
    Rotate(xml_node);
    void draw();
};

class Scale : public PhysicScene{
    float x, y, z;
  public:
    Scale(xml_node);
    void draw();
};

class Color : public PhysicScene{
    float redVal, greenVal, blueVal;
  public:
    Color(xml_node);
    void draw();
};

class Models : public PhysicScene{
    vector<Model*> models;
  public:
    Models(xml_node);
    void draw();
};

class Group : public PhysicScene{
    vector<PhysicScene*> transforms;
  public:
    Group(xml_node);
    void draw();
};

class Scene {
    Group* group;
  public:
    Scene(const char* xml_file);
    void draw();
};

#endif
