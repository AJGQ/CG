
#include <string.h>
#include <unistd.h>
#include "create.h"

FILE *outputFile;

void error(const char* s){
  fprintf(stderr,"\e[1;31mError:\e[0;1m%s\e[0m\n", s); _exit(-1);
}

int main(int argc, char** argv){

  outputFile = fopen(argv[argc-1],"w");

  if     (argc==3 && !strncmp("plane"     , argv[1], 5 )) createPlane(argv); 
  else if(argc==7 && !strncmp("box"       , argv[1], 3 )) createBox(argv); 
  else if(argc==7 && !strncmp("inv_box"   , argv[1], 7 )) createBox(argv, -1); 
  else if(argc==6 && !strncmp("sphere"    , argv[1], 6 )) createSphere(argv); 
  else if(argc==6 && !strncmp("inv_sphere", argv[1], 10)) createSphere(argv, -1); 
  else if(argc==7 && !strncmp("cone"      , argv[1], 4 )) createCone(argv); 
  else if(argc==7 && !strncmp("cylinder"  , argv[1], 8 )) createCylinder(argv); 
  else if(argc==7 && !strncmp("torus"     , argv[1], 5 )) createTorus(argv); 
  else if(argc==5 && !strncmp("bezier"    , argv[1], 6 )) createBezier(argv);
  else error("try man generator");

  return 0;
}
