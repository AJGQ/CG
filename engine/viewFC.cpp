
float M[16],P[16],A[16];

boolean tP(float x, float y, float z){
    float lx, ly, lz, lw, w=1;

    lx= A[0]*x + A[4]*y + A[8]*z  + A[12]*w;
    ly= A[1]*x + A[5]*y + A[9]*z  + A[13]*w;
    lz= A[2]*x + A[6]*y + A[10]*z + A[14]*w;
    lw= A[3]*x + A[7]*y + A[11]*z + A[15]*w;

    if (lx <- lw || lx > lw) return true;
    if (ly <- lw || ly > lw) return true;
    if (lz <- lw || lz > lw) return true;

    return false;
}


boolean testBox(float maxX, float minX, float maxY, float minY, float maxZ, float minZ){

    if ( tP(minX, minY, minZ) ) { return true; }
    if ( tP(minX, minY, maxZ) ) { return true; }
    if ( tP(minX, maxY, minZ) ) { return true; }
    if ( tP(minX, maxY, maxZ) ) { return true; }
    if ( tP(maxX, minY, minZ) ) { return true; }
    if ( tP(maxX, minY, maxZ) ) { return true; }
    if ( tP(maxX, maxY, minZ) ) { return true; }
    if ( tP(maxX, maxY, maxZ) ) { return true; }

    return false;
}

void drawBox(float maxX, float minX, float maxY, float minY, float maxZ, float minZ){

    glBegin(GL_LINE_STRIP);
    glVertex3f(maxX, maxY, maxZ);
    glVertex3f(maxX, maxY, minZ);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(minX, maxY, maxZ);
    glVertex3f(minX, maxY, minZ);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(maxX, minY, maxZ);
    glVertex3f(maxX, minY, minZ);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(minX, minY, maxZ);
    glVertex3f(minX, minY, minZ);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(maxX, maxY, maxZ);
    glVertex3f(maxX, minY, maxZ);
    glVertex3f(minX, minY, maxZ);
    glVertex3f(minX, maxY, maxZ);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(maxX, maxY, minZ);
    glVertex3f(maxX, minY, minZ);
    glVertex3f(minX, minY, minZ);
    glVertex3f(minX, maxY, minZ);
    glEnd();
}
