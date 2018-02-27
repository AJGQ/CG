
void createPlane    (vector<Vertex *>* ret);
void createBox      (vector<Vertex *>* ret, float x, float y, float z, int d=1);
void createSphere   (vector<Vertex *>* ret, int slices, int stacks);
void createCone     (vector<Vertex *>* ret, int slices, int stacks);

void createCylinder (vector<Vertex *>* ret, int slices);
void createN64      (vector<Vertex *>* ret);
