#include <string>
#include <fstream>

using namespace std;


class Vertex{
    public:
        float x;
        float y;
        float z;

        Vertex();
        Vertex(float x, float y, float z);

        Vertex* plus(float x=0, float y=0, float z=0);

        string toString();
        string toGLString();
};
