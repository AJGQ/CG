#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "catmull.h"

#define POINT_COUNT 4
#define TOTAL_POINTS 100

//-Translacao ao longo do tempo------------------------------------------------//

void cross(float *a, float *b, float *res) {
	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
    res[3] = 0;
}

void normalize(float *a) {
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
    a[3] = 1;
}

void multVectorMatrix(float *v, float *m, float *res) {
	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[k * 4 + j];
		}
	}
}

void multMatrixMatrix(float* m1, float* m2, float *res){
    for(int i = 0; i<4; i++){
        multVectorMatrix(m1 + i*4, m2, res + i*4);
    }
}

void getCatmullRomPoint(float t,
                        float *p0, float *p1, float *p2, float *p3,
                        float *pos, float *deriv) {

	// catmull-rom matrix
	float m[16] =  {
        -0.5f,  1.5f, -1.5f,  0.5f,
	    1.0f , -2.5f,  2.0f, -0.5f,
		-0.5f,  0.0f,  0.5f,  0.0f,
		0.0f ,  1.0f,  0.0f,  0.0f
    };

	// Compute A = M * P
	float P[16] = {
        p0[0], p0[1], p0[2], 1,
        p1[0], p1[1], p1[2], 1,
        p2[0], p2[1], p2[2], 1,
        p3[0], p3[1], p3[2], 1
    };

    float A[16];
    multMatrixMatrix(m,P,A);

	// Compute pos = T * A
    float T[4] = {t*t*t, t*t, t, 1};
    multVectorMatrix(T, A, pos);

	// compute deriv = T' * A
    //float T_[4] = {3*t*t, 2*t, 1, 0};
    //multVectorMatrix(T_, A, deriv);
}

void getGlobalCatmullRomPoint(std::vector<float*> p, float gt, float *pos, float *deriv) {

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT;
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void renderCatmullRomCurve(std::vector<float*> p) {
    glBegin(GL_LINE_LOOP);
    float t;
    float pos[3];
    float deriv[3];
    for(int i= 0; i<TOTAL_POINTS; i++){
        t = ((float)i)/TOTAL_POINTS;
        getGlobalCatmullRomPoint(p, t, pos, deriv);
        glVertex3f(pos[0],pos[1],pos[2]);
    }

    glEnd();
// desenhar a curva usando segmentos de reta - GL_LINE_LOOP
}

void startPath(std::vector<float*> p, float time){
    int globalTime = glutGet(GLUT_ELAPSED_TIME);
    int timeMS = (int)(1000*time);
    int interval = globalTime % timeMS;
    float t = ((float)interval)/timeMS; // t in [0-1[

    float pos[3] = {0,0,0};
    float deriv[3] = {1,0,0};
    float up[3] = {0,1,0};
    float Z[3] = {0,0,1};

    getGlobalCatmullRomPoint(p, t, pos, deriv);
    normalize(deriv);

    cross(deriv, up, Z);
    normalize(Z);

    cross(Z, deriv, up);
    normalize(up);

    float m[16] = {deriv[0], deriv[1], deriv[2], 0 ,
                   up[0]   , up[1]   , up[2]   , 0 ,
                   Z[0]    , Z[1]    , Z[2]    , 0 ,
                   pos[0]  , pos[1]  , pos[2]  , 1 };

    glMultMatrixf(m);

}

