#ifndef PARSE_XML_H
#define PARSE_XML_H 

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include "pugixml-1.8/src/pugixml.hpp"
#include <unistd.h>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;
using namespace pugi;

extern float *arrayFloat;
extern GLuint buffers[1];

extern void error(const char *s);
void parseXML(char *fileXML);
void drawFiles();

#endif
