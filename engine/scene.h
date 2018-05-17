
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


extern void error(const char *s);

class PhysicScene{
  public:
    virtual void draw() = 0;
};

class Model {
  public:
    GLuint vertexId, normalId, vertexTextureId, textureId;
    int N, index;
    float *amb, *diff, *spec, *emi;
    string *texture;
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

class Light{
  public:
    float pos[4], *dir, *diff, *spec, *amb, *emi;
    float *cutOff, *exponent;
    Light(xml_node);
    void draw(int);
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

class Lights : public PhysicScene{
    vector<Light*> vlights;
  public:
    Lights(xml_node);
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
    Lights* lights;
  public:
    Scene(const char* xml_file);
    void draw();
};

#endif
