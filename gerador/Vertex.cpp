
#include <string>
#include "generatorHeaders/Vertex.h"

using namespace std;

Vertex::Vertex(){
    this-> x = 0.0;
    this-> y = 0.0;
    this-> z = 0.0;
}

Vertex::Vertex(float x, float y, float z){
    this-> x = x;
    this-> y = y;
    this-> z = z;
}

Vertex* Vertex::plus(float x, float y, float z){
    return new Vertex(this->x+x, this->y+y, this->z+z);
}

string Vertex::toString(){
    string ret;
    ret = to_string(x) + "\t" + to_string(y) + "\t" + to_string(z) + "\n";

    return ret;
}

string Vertex::toGLString(){
    string ret;
    ret = "glVertex3f(" +to_string(x) + ",\t" + to_string(y) + ",\t" + to_string(z) + ");\n";

    return ret;
}
