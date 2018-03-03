#include <string.h>
#include <iostream>
#include <fstream>
#include "create.h"
#include <algorithm>
#include <unistd.h>

using namespace std;

ofstream outputFile;

void error(string s){
        cout << "\e[1;31mError:\e[0;1m" + s +"\e[0m" << endl;
        _exit(-1);
}

int main(int argc, char** argv){

    if( argc >= 3 ){
        outputFile.open(argv[2]);

        //if      ( argc==3 && !strncmp("plane"   , argv[1], 5) ) { createPlane(argv); }
        //else if ( argc==7 && !strncmp("box"     , argv[1], 3) ) { createBox(argv); }
        //else if ( argc==6 && !strncmp("sphere"  , argv[1], 6) ) { createSphere(argv); }
        if ( argc==7 && !strncmp("cone"    , argv[1], 4) ) { createCone(argv); }
        //else if ( argc==6 && !strncmp("cylinder", argv[1], 4) ) { createCylinder(argv); }
        else error("try man generator");
    }

    else error("try man generator");

    return 0;
}
