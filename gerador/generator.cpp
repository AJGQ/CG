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
    else if ( !strncmp("box"     , argv[1], 3) && argc==7 ) { createBox(&vv, atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5])); }
    else if ( !strncmp("sphere"  , argv[1], 6) && argc==6 ) { createSphere(&vv, atof(argv[2]), atoi(argv[3]), atoi(argv[4])); }
    else if ( !strncmp("cone"    , argv[1], 4) && argc==7 ) { createCone(&vv, atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5])); }
    else if ( !strncmp("cylinder", argv[1], 4) && argc==6 ) { createCylinder(&vv, atof(argv[2]), atof(argv[3]), atoi(argv[4])); }

    else cout << "\e[1;31mError:\e[0;1m try man generator\e[0m" << endl;

    ofstream file(argv[argc-1]);
    for_each(vv.begin(), vv.end(), [&file](Vertex* v) { file << v->toString(); });

    return 0;
}
