#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "scene.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <map>
#include <stdio.h>

extern int trajetorias;
extern int loadTexture(string s);
extern map<string,int> texturesId;

char text[256] = "Nothing\n";
const char* picked = 0;
int code = 0;
map<int, const char*> codes;

extern Scene* scene;
//-Texto dos Objetos---//

const char* picking(int x, int y, float camX, float camY, float camZ) {

    printf("Is Here?1");
    int res[4];
    //Preparation
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
            0.0,0.0,0.0,
            0.0f,1.0f,0.0f);

    glDepthFunc(GL_LEQUAL);
    printf("Is Here?2");

    // draw
    scene->draw_picking();

    glDepthFunc(GL_LESS);

    //Tracking
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(x, viewport[3]- y, 1, 1,
            GL_RGBA, GL_UNSIGNED_BYTE, res);

    //Recover
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    printf("%s\n",codes[res[0]]);
    return codes[res[0]];
}

void renderText() {

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // set projection so that coordinates match window pixels
    gluOrtho2D(0, 800, 800, 0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);

    glPushMatrix();
    glLoadIdentity();
    glRasterPos2d(10, 20);
    // text position in pixels

    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

//-Model----------------------------------------------------------------------//
void getLightComponent(xml_node node, string s, float **mat){

    xml_attribute aux_r = node.attribute((s+"R").c_str());
    xml_attribute aux_g = node.attribute((s+"G").c_str());
    xml_attribute aux_b = node.attribute((s+"B").c_str());

    if(aux_r && aux_g && aux_b){
        *mat = new float[4];
        (*mat)[0] = aux_r ? aux_r.as_float() : 0.0f;
        (*mat)[1] = aux_g ? aux_g.as_float() : 0.0f;
        (*mat)[2] = aux_b ? aux_b.as_float() : 0.0f;
        (*mat)[3] = 1.0f;
    }
    else *mat=NULL;
}

Model::Model(xml_node node) {
    FILE* file;
    int i, total;
    float x, y, z;
    float *v, *n, *t;
    this->texture = NULL;

    file = fopen(node.attribute("file").as_string(), "r");

    if(node.attribute("texture")) this->texture = new string(node.attribute("texture").as_string());
    if(node.attribute("text")) this->text = node.attribute("text").as_string();
    if(this->texture) texturesId[*this->texture] = loadTexture(*this->texture);
    if(this->text) codes[code++] = this->text;
    getLightComponent(node, "amb", &this->amb);
    getLightComponent(node, "diff", &this->diff);
    getLightComponent(node, "spec", &this->spec);
    getLightComponent(node, "emi", &this->emi);

    if(!file) error("opening file");
    fscanf(file,"%d\n",&(this->N));

    this->index = 0;
    this->pos = new int[this->N];
    this->len = new int[this->N];
    this->typ = new char[this->N];

    for(i=0, total=0; i<this->N; i++) {
        fscanf(file,"%c%d\n", &typ[i], &len[i]);
        pos[i] = total;
        total += len[i];
    }

    v = new float[total * 3];
    n = new float[total * 3];
    t = new float[total * 2];

    for(i=0; fscanf(file,"%f:%f:%f\n",&x,&y,&z) != EOF; i++) {
        v[i*3 + 0] = x;
        v[i*3 + 1] = y;
        v[i*3 + 2] = z;

        fscanf(file,"%f:%f:%f\n",&x,&y,&z);
        n[i*3 + 0] = x;
        n[i*3 + 1] = y;
        n[i*3 + 2] = z;

        fscanf(file,"%f:%f\n",&x,&y);
        t[i*2 + 0] = x;
        t[i*2 + 1] = y;
    }

    glGenBuffers(1, &(this->vertexId));
    glGenBuffers(1, &(this->normalId));
    glGenBuffers(1, &(this->vertexTextureId));

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexId);
    glBufferData(GL_ARRAY_BUFFER, i * 3 * sizeof(float), v, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->normalId);
    glBufferData(GL_ARRAY_BUFFER, i * 3 * sizeof(float), n, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexTextureId);
    glBufferData(GL_ARRAY_BUFFER, i * 2 * sizeof(float), t, GL_STATIC_DRAW);

    free(v); free(n); free(t);
}

void Model::draw_picking() {
    float color = code++ / 255.0f;
    int i, gl;
    glColor3f(color, color, color);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexId);
    glVertexPointer(3,GL_FLOAT,0,0);

    for(i=0; i<this->N; i++) {
        switch(this->typ[i]) {
            case 's' : gl = GL_TRIANGLE_STRIP;  break;
            case 'f' : gl = GL_TRIANGLE_FAN;    break;
            case 't' : gl = GL_TRIANGLES;       break;
            default  : error("array type bad specified");
        }
        glDrawArrays(gl, this->pos[i], this->len[i]);
    }

}

void Model::draw() {
    int i, gl;
    glPushAttrib(GL_LIGHTING_BIT);

    if(this->amb)  glMaterialfv(GL_FRONT, GL_AMBIENT,  this->amb );
    if(this->diff) glMaterialfv(GL_FRONT, GL_DIFFUSE,  this->diff);
    if(this->spec) glMaterialfv(GL_FRONT, GL_SPECULAR, this->spec);
    if(this->emi)  glMaterialfv(GL_FRONT, GL_EMISSION, this->emi );

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexId);
    glVertexPointer(3,GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER, this->normalId);
    glNormalPointer(GL_FLOAT,0,0);

    if(this->texture){
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexTextureId);
        glBindTexture(GL_TEXTURE_2D, texturesId[*this->texture]);
    	glTexCoordPointer(2,GL_FLOAT,0,0);
    }

    for(i=0; i<this->N; i++) {
        switch(this->typ[i]) {
            case 's' : gl = GL_TRIANGLE_STRIP;  break;
            case 'f' : gl = GL_TRIANGLE_FAN;    break;
            case 't' : gl = GL_TRIANGLES;       break;
            default  : error("array type bad specified");
        }
        glDrawArrays(gl, this->pos[i], this->len[i]);
    }

    if(this->texture) glBindTexture(GL_TEXTURE_2D, 0);
    glPopAttrib();
}

//-Translate------------------------------------------------------------------//

Translate::Translate(xml_node node) {
    //cout << "parse de Translate comecou" << endl;
    xml_attribute aux_time = node.attribute("time");
    xml_attribute aux_x    = node.attribute("X");
    xml_attribute aux_y    = node.attribute("Y");
    xml_attribute aux_z    = node.attribute("Z");

    this->time = aux_time ? aux_time.as_float() : 0.0f;
    this->x    = aux_x    ? aux_x.as_float()    : 0.0f;
    this->y    = aux_y    ? aux_y.as_float()    : 0.0f;
    this->z    = aux_z    ? aux_z.as_float()    : 0.0f;

    for(xml_node point = node.first_child(); point; point = point.next_sibling()) {
        if(strcmp(point.name(),"point") == 0) {
            aux_x = point.attribute("X");
            aux_y = point.attribute("Y");
            aux_z = point.attribute("Z");

            float* v = (float*)malloc(3*sizeof(float));
            v[0] = aux_x ? aux_x.as_float() : 0.0f;
            v[1] = aux_y ? aux_y.as_float() : 0.0f;
            v[2] = aux_z ? aux_z.as_float() : 0.0f;

            this->points.push_back(v);
        }else{
            error("O translate tem apenas nodes point");
        }
    }

    //cout << "parse de Translate acabou" << endl;
}

void Translate::draw_picking() {
    if (time == 0) {
        glTranslatef(this->x,this->y,this->z);
    } else {
        if(this->x != 0.0 || this->y != 0.0 || this->z != 0.0)
            glTranslatef(this->x,this->y,this->z);
        if(trajetorias){
            renderCatmullRomCurve(this->points);
        }

        startPath(this->points, this->time);
    }
}

void Translate::draw() {
    if (time == 0) {
        glTranslatef(this->x,this->y,this->z);
    } else {
        if(this->x != 0.0 || this->y != 0.0 || this->z != 0.0)
            glTranslatef(this->x,this->y,this->z);
        if(trajetorias){
            renderCatmullRomCurve(this->points);
        }

        startPath(this->points, this->time);
    }
}

const char* Translate::testClass(){return "Translate";}
//-Rotate---------------------------------------------------------------------//

Rotate::Rotate(xml_node node) {
    //cout << "parse de Rotate comecou" << endl;
    xml_attribute aux_time  = node.attribute("time");
    xml_attribute aux_angle = node.attribute("angle");
    xml_attribute aux_x     = node.attribute("axisX");
    xml_attribute aux_y     = node.attribute("axisY");
    xml_attribute aux_z     = node.attribute("axisZ");

    this->time  = aux_time  ? aux_time.as_float()  : 0.0f;
    this->angle = aux_angle ? aux_angle.as_float() : 0.0f;
    this->x     = aux_x     ? aux_x.as_float()     : 0.0f;
    this->y     = aux_y     ? aux_y.as_float()     : 0.0f;
    this->z     = aux_z     ? aux_z.as_float()     : 0.0f;

    if(this->angle != 0.0 && this->time != 0.0){
        this->time  = (360.0/this->angle) * this->time;
        this->angle = 0.0;
    }
    //cout << "parse de Rotate acabou" << endl;
}

void Rotate::draw_picking() {
    if(this->time == 0.0){
        glRotatef(this->angle,this->x,this->y,this->z);
    } else {
        int globalTime = glutGet(GLUT_ELAPSED_TIME);
        int time = (int)(1000*this->time);
        int interval = globalTime % time;

        glRotatef(((float)interval/(float)time)*360.0 , this->x, this->y, this->z);
    }
}

void Rotate::draw() {
    if(this->time == 0.0){
        glRotatef(this->angle,this->x,this->y,this->z);
    } else {
        int globalTime = glutGet(GLUT_ELAPSED_TIME);
        int time = (int)(1000*this->time);
        int interval = globalTime % time;

        glRotatef(((float)interval/(float)time)*360.0 , this->x, this->y, this->z);
    }
}

const char* Rotate::testClass(){return "Rotate";}
//-Scale----------------------------------------------------------------------//

Scale::Scale(xml_node node) {
    //cout << "parse de Scale comecou" << endl;
    xml_attribute aux_x = node.attribute("X");
    xml_attribute aux_y = node.attribute("Y");
    xml_attribute aux_z = node.attribute("Z");

    this->x = aux_x ? aux_x.as_float() : 0.0f;
    this->y = aux_y ? aux_y.as_float() : 0.0f;
    this->z = aux_z ? aux_z.as_float() : 0.0f;
    //cout << "parse de Scale acabou" << endl;
}

void Scale::draw_picking() {
    glScalef(this->x,this->y,this->z);
}

void Scale::draw() {
    glScalef(this->x,this->y,this->z);
}

const char* Scale::testClass(){return "Scale";}
//-Color----------------------------------------------------------------------//

Color::Color(xml_node node) {
    //cout << "parse de Color comecou" << endl;
    xml_attribute aux_redVal = node.attribute("R");
    xml_attribute aux_greenVal = node.attribute("G");
    xml_attribute aux_blueVal = node.attribute("B");

    this->redVal = aux_redVal ? aux_redVal.as_float() : 0; //f
    this->greenVal = aux_greenVal ? aux_greenVal.as_float() : 0; //f
    this->blueVal = aux_blueVal ? aux_blueVal.as_float() : 0; //f
    //cout << "parse de Color acabou" << endl;
}

void Color::draw_picking() {}

void Color::draw() {
    glColor3f(this->redVal,this->greenVal,this->blueVal);
}

const char* Color::testClass(){return "Color";}
//-Light----------------------------------------------------------------------//

Light::Light(xml_node node) {
    xml_attribute aux_type = node.attribute("type");

    xml_attribute aux_x = node.attribute("posX");
    xml_attribute aux_y = node.attribute("posY");
    xml_attribute aux_z = node.attribute("posZ");

    xml_attribute aux_dx = node.attribute("dirX");
    xml_attribute aux_dy = node.attribute("dirY");
    xml_attribute aux_dz = node.attribute("dirZ");

    xml_attribute aux_exp = node.attribute("pExp");
    xml_attribute aux_cut = node.attribute("pCut");
    this->dir = NULL;

    this->pos[0] = aux_x ? aux_x.as_float() : 0.0f;
    this->pos[1] = aux_y ? aux_y.as_float() : 0.0f;
    this->pos[2] = aux_z ? aux_z.as_float() : 0.0f;

    if(!strncmp("POINT", aux_type.as_string(), 5)) this->pos[3] = 1;
    else if(!strncmp("DIRECTIONAL", aux_type.as_string(), 11)) this->pos[3] = 0;
    else if(!strncmp("SPOT", aux_type.as_string(), 4)){
        this->pos[3] = 1.0f;

        this->dir = new float[4];
        this->dir[0] = aux_dx ? aux_dx.as_float() : 0.0f;
        this->dir[1] = aux_dy ? aux_dy.as_float() : 0.0f;
        this->dir[2] = aux_dz ? aux_dz.as_float() : 0.0f;
        this->dir[3] = 0.0f;

        this->cutOff   = aux_cut ? new float(aux_cut.as_float()) : NULL;
        this->exponent = aux_exp ? new float(aux_exp.as_float()) : NULL;
    }
    getLightComponent(node, "amb", &this->amb);
    getLightComponent(node, "diff", &this->diff);
    getLightComponent(node, "spec", &this->spec);
    getLightComponent(node, "emi", &this->emi);
}


void Light::draw(int i) {
    glEnable(GL_LIGHT0+i);

    glLightfv(GL_LIGHT0+i, GL_POSITION, this->pos);
    if(this->dir){
        glLightfv(GL_LIGHT0+i, GL_SPOT_DIRECTION, this->dir);
        if(this->cutOff)   glLightf(GL_LIGHT0+i, GL_SPOT_CUTOFF,   *(this->cutOff));
        if(this->exponent) glLightf(GL_LIGHT0+i, GL_SPOT_EXPONENT, *(this->exponent));
    }

    if(this->amb)  glLightfv(GL_LIGHT0+i, GL_AMBIENT, this->amb);
    if(this->diff) glLightfv(GL_LIGHT0+i, GL_DIFFUSE, this->diff);
    if(this->spec) glLightfv(GL_LIGHT0+i, GL_SPECULAR, this->spec);
    if(this->emi)  glLightfv(GL_LIGHT0+i, GL_EMISSION, this->emi);

    /*if (this->pos[3] != 2) { // PESSIMO SO PARA TESTE: 2 -> SPOT
      glLightfv(GL_LIGHT0+i, GL_POSITION, this->pos);
    } else if(this->type){
        GLfloat* spot_dir = (GLfloat*) malloc(4*sizeof(GLfloat));
        GLfloat* spot_pos = (GLfloat*) malloc(4*sizeof(GLfloat));
        spot_dir[0] = (GLfloat)this->pos[0];
        spot_dir[1] = (GLfloat)this->pos[1];
        spot_dir[2] = (GLfloat)this->pos[2];
        spot_dir[3] = 0.0;
        spot_pos[0] = (GLfloat)this->pos[4];
        spot_pos[1] = (GLfloat)this->pos[5];
        spot_pos[2] = (GLfloat)this->pos[6];
        spot_pos[3] = 1.0;

        glLightfv(GL_LIGHT0+i, GL_SPOT_DIRECTION, spot_dir);
        glLightfv(GL_LIGHT0+i, GL_POSITION, spot_pos);
        if(this->cutOff)   glLightf(GL_LIGHT0+i, GL_SPOT_CUTOFF,   *(this->cutOff));
        if(this->exponent) glLightf(GL_LIGHT0+i, GL_SPOT_EXPONENT, *(this->exponent));

    }
*/
}

//-Models---------------------------------------------------------------------//

Models::Models(xml_node node) {
    for(xml_node trans = node.first_child(); trans; trans = trans.next_sibling()) {
        if(strcmp(trans.name(),"model") == 0) {
            this->models.push_back(new Model(trans));
        }else{
            error("O models tem apenas nodes model");
        }
    }
}

void Models::draw_picking() {
    for(int i = 0; i<models.size();i++) {
        this->models[i]->draw_picking();
    }
}

void Models::draw() {
    for(int i = 0; i<models.size();i++) {
        this->models[i]->draw();
    }
}

const char* Models::testClass(){return "Models";}
//-Lights----------------------------------------------------------------------//

Lights::Lights(xml_node node) {
    for(xml_node trans = node.first_child(); trans; trans = trans.next_sibling()) {
        if(!strcmp(trans.name(),"light")) { this->vlights.push_back(new Light(trans)); }
        else cout << "Erro no formato do xml, foi lido: " << trans.name() << endl;
    }
}

void Lights::draw_picking(){}

void Lights::draw(){
    for(int i = 0; i<vlights.size(); i++){
        this->vlights[i]->draw(i);
    }
}

const char* Lights::testClass(){return "Lights";}
//-Group----------------------------------------------------------------------//

Group::Group(xml_node node) {
    //cout << "parse de Group comecou" << endl;
    for(xml_node trans = node.first_child(); trans; trans = trans.next_sibling()) {
        if(strcmp(trans.name(),"translate") == 0) {
            this->transforms.push_back(new Translate(trans));

        }else if(strcmp(trans.name(),"rotate") == 0) {
            this->transforms.push_back(new Rotate(trans));

        }else if(strcmp(trans.name(),"scale") == 0) {
            this->transforms.push_back(new Scale(trans));

        }else if(strcmp(trans.name(),"color") == 0) {
            this->transforms.push_back(new Color(trans));

        }else if(strcmp(trans.name(),"models") == 0) {
            this->transforms.push_back(new Models(trans));

        }else if(strcmp(trans.name(),"group") == 0) {
            this->transforms.push_back(new Group(trans));

        }else if(strcmp(trans.name(),"lights") == 0) {
            this->transforms.push_back(new Lights(trans));

        }else{
            cout << "Erro no formato do xml, foi lido: " << trans.name() << endl;
        }
    }
    //cout << "parse de Group acabou" << endl;
}

void Group::draw_picking() {
    glPushMatrix();
    for(int i = 0; i<transforms.size(); i++) {
        if(strcmp(transforms[i]->testClass(), "Lights") != 0)
            this->transforms[i]->draw_picking();
    }
    glPopMatrix();
}

const char* Group::testClass(){return "Group";}

void Group::draw() {
    glPushMatrix();
    for(int i = 0; i<transforms.size(); i++) {
        this->transforms[i]->draw();
    }
    glPopMatrix();
}
//-Scene----------------------------------------------------------------------//

Scene::Scene(const char* xml_file) {
    code = 0;
    //cout << "parse de Scene comecou" << endl;
    xml_document doc;
    xml_parse_result result;
    this->lights =  NULL;

    if( !(result = doc.load_file(xml_file)) ) {
        std::cout << "XML [" << xml_file << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (xml_file + result.offset) << "]\n\n";
    }
    xml_node models = doc.child("scene");

    for(xml_node trans = models.first_child(); trans; trans = trans.next_sibling()) {
        if(!strncmp("lights", trans.name(), 6)) this->lights = new Lights(trans);
        else if(!strncmp("group", trans.name(), 5)) this->group = new Group(trans);
        //this->group = new Group(models.first_child());
    }
    //cout << "parse de Scene acabou" << endl;
}

void Scene::draw_picking() {
    code = 0;
    this->group->draw_picking();
}

void Scene::draw() {
    if(this->lights != NULL){
        this->lights->draw();
        glEnable(GL_LIGHTING);
    }
    this->group->draw();
    renderText();
}
