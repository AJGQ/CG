#include <iostream>
#include <fstream>
#include <vector>
#include "Vertex.h"
#include "create.h"
#include <algorithm>

using namespace std;


int main(int argc, char** argv){
    string shape = argv[1];
    vector<Vertex*> vv;
    ofstream file(argv[2]);

    if      ( !shape.compare("plane")   && argc==3 )   vv = createPlane();
    else if ( !shape.compare("box")     && argc==7 )   vv = createBox(atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]));
    else if ( !shape.compare("cone")    && argc==7 )   vv = createCone(atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]));
    else if ( !shape.compare("sphere")  && argc==6 )   vv = createSphere(atof(argv[3]), atof(argv[4]), atof(argv[5]));
    else cout << "\e[1m\e[31mError:\e[0m\e[1m try man gerador\e[0m" << endl;

    for_each(vv.begin(), vv.end(), [&file](Vertex* v) { file << v->toGLString(); });
    //for_each(vv.begin(), vv.end(), [&file](Vertex* v) { file << v->toString(); });

    return 0;
}

