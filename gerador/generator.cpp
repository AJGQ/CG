
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "generatorHeaders/Vertex.h"
#include "generatorHeaders/create.h"
#include <algorithm>

using namespace std;

float alpha  = -1;
float beta   = -1;
float radius = -1;
float height = -1;

int main(int argc, char** argv){
    vector<Vertex*> vv;

    if      ( !strncmp("plane"   , argv[1], 5) && argc==3 ) { createPlane(&vv); }
    else if ( !strncmp("box"     , argv[1], 3) && argc==7 ) { createBox(&vv, atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6])); }
    else if ( !strncmp("sphere"  , argv[1], 6) && argc==6 ) { radius = atof(argv[3]); createSphere(&vv, atof(argv[4]), atof(argv[5])); }
    else if ( !strncmp("cone"    , argv[1], 4) && argc==7 ) { radius = atof(argv[3]); height = atof(argv[4]); createCone(&vv, atof(argv[5]), atoi(argv[6])); }

    else if ( !strncmp("cylinder", argv[1], 4) && argc==6 ) { radius = atof(argv[3]); height = atof(argv[4]); createCylinder(&vv, atoi(argv[5])); }

    else cout << "\e[1;31mError:\e[0;1m try man generator\e[0m" << endl;

    ofstream file(argv[2]);
    for_each(vv.begin(), vv.end(), [&file](Vertex* v) { file << v->toGLString(); });
    //for_each(vv.begin(), vv.end(), [&file](Vertex* v) { file << v->toString(); });

    return 0;
}
