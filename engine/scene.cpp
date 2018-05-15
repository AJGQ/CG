#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "scene.h"
#include "catmull.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <map>
#include <stdio.h>

extern int trajetorias;
extern int loadTexture(string s);
extern map<string,int> texturesId;



//-Model----------------------------------------------------------------------//
void getMat(xml_node node, string s, float **mat){

    xml_attribute aux_r = node.attribute((s+"R").c_str());
    xml_attribute aux_g = node.attribute((s+"G").c_str());
    xml_attribute aux_b = node.attribute((s+"B").c_str());

    if(aux_r && aux_g && aux_b){
        *mat = new float[4];
        (*mat)[0] = aux_r.as_float();
        (*mat)[1] = aux_g.as_float();
        (*mat)[2] = aux_b.as_float();
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
    if(this->texture) texturesId[*this->texture] = loadTexture(*this->texture);
    getMat(node, "amb", &this->amb); 
    getMat(node, "diff", &this->diff);
    getMat(node, "spec", &this->spec);
    getMat(node, "emi", &this->emi);
    
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

void Model::draw() {
    int i, gl;
    glPushAttrib(GL_LIGHTING_BIT);

    if(this->amb)  glMaterialfv(GL_FRONT, GL_AMBIENT, this->amb);
    if(this->diff) glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diff);
    if(this->spec) glMaterialfv(GL_FRONT, GL_SPECULAR, this->spec);
    if(this->emi)  glMaterialfv(GL_FRONT, GL_EMISSION, this->emi); 

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

void Translate::draw() {
    if (time == 0) {
        glTranslatef(this->x,this->y,this->z);
    } else { 
        if(this->x != 0.0 || this->y != 0.0 || this->z != 0.0)
            glTranslatef(this->x,this->y,this->z);
        if(trajetorias)
            renderCatmullRomCurve(this->points);

        startPath(this->points, this->time);
    }
}

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

void Scale::draw() {
    glScalef(this->x,this->y,this->z);
}

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

void Color::draw() {
    glColor3f(this->redVal,this->greenVal,this->blueVal);
}

//-Light----------------------------------------------------------------------//
 
Light::Light(xml_node node) {
    xml_attribute aux_type = node.attribute("type");
    xml_attribute aux_x = node.attribute("posX");
    xml_attribute aux_y = node.attribute("posY");
    xml_attribute aux_z = node.attribute("posZ");

    if(!strncmp("POINT", aux_type.as_string(), 5)) this->pos[3] = 1;
    else if(!strncmp("DIRECTIONAL", aux_type.as_string(), 11)) this->pos[3] = 0;  

    this->pos[0] = aux_x ? aux_x.as_float() : 0.0f;
    this->pos[1] = aux_y ? aux_y.as_float() : 0.0f;
    this->pos[2] = aux_z ? aux_z.as_float() : 0.0f;

}


void Light::draw(int i) {
    glEnable(GL_LIGHT0+i);
    glLightfv(GL_LIGHT0+i, GL_POSITION, this->pos);
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

void Models::draw() {
    for(int i = 0; i<models.size();i++) {
        this->models[i]->draw();
    }
}

//-Lights----------------------------------------------------------------------//

Lights::Lights(xml_node node) {
    for(xml_node trans = node.first_child(); trans; trans = trans.next_sibling()) {
        if(!strcmp(trans.name(),"light")) { this->vlights.push_back(new Light(trans)); }
        else cout << "Erro no formato do xml, foi lido: " << trans.name() << endl; 
    }
}

void Lights::draw(){
    for(int i = 0; i<vlights.size(); i++) this->vlights[i]->draw(i);
}

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

        }else{
            cout << "Erro no formato do xml, foi lido: " << trans.name() << endl;
        }
    }
    //cout << "parse de Group acabou" << endl;
}

void Group::draw() {
    glPushMatrix();
    for(int i = 0; i<transforms.size(); i++) {
        this->transforms[i]->draw();
    }
    glPopMatrix();
}
//-Scene----------------------------------------------------------------------//

Scene::Scene(const char* xml_file) {
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

void Scene::draw() {
    if(this->lights != NULL){
        this->lights->draw();
        glEnable(GL_LIGHTING);
    }
    this->group->draw();
}
