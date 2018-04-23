
#include "scene.h"
#include <stdlib.h>
#include <iostream>

//-Model----------------------------------------------------------------------//

Model::Model(xml_node node) {
    FILE* file;
    int i, total;
    float x, y, z;

    file = fopen(node.attribute("file").as_string(), "r");
    
    //strcpy((char*)this->file, node.attribute("file").as_string());
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
    this->arrayFloat = new float[total * 3];
    while(fscanf(file,"%f:%f:%f\n",&x,&y,&z) != EOF) {
        this->arrayFloat[this->index++] = x;
        this->arrayFloat[this->index++] = y;
        this->arrayFloat[this->index++] = z;
    }
}

void Model::draw() {
    int i, gl;
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, this->index * 3 * sizeof(float), this->arrayFloat, GL_STATIC_DRAW);
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

//-Translate------------------------------------------------------------------//

Translate::Translate(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Translate::Translate(xml_node node) {
    //cout << "parse de Translate comecou" << endl;
    xml_attribute aux_x = node.attribute("X");
    xml_attribute aux_y = node.attribute("Y");
    xml_attribute aux_z = node.attribute("Z");

    this->x = aux_x ? aux_x.as_float() : 0.0f;
    this->y = aux_y ? aux_y.as_float() : 0.0f;
    this->z = aux_z ? aux_z.as_float() : 0.0f;
    //cout << "parse de Translate acabou" << endl;
}

void Translate::draw() {
    glTranslatef(this->x,this->y,this->z);
}

//-Rotate---------------------------------------------------------------------//

Rotate::Rotate(float time, float angle, float x, float y, float z) {
    this->time = time;
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
}

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
        int intervalo = globalTime % time;

        glRotatef(((float)intervalo/(float)time)*360.0 , this->x, this->y, this->z);
    }
}

//-Scale----------------------------------------------------------------------//

Scale::Scale(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

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

Color::Color(float redVal, float greenVal, float blueVal) {
    this->redVal = redVal;
    this->greenVal = greenVal;
    this->blueVal = blueVal;
}

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
    glColor3ub(this->redVal,this->greenVal,this->blueVal);
}

//-Models---------------------------------------------------------------------//

Models::Models(std::vector<Model*> models) {
    this->models = models;
}

Models::Models(xml_node node) {
    for(xml_node trans = node.first_child(); trans; trans = trans.next_sibling()) {
        this->models.push_back(new Model(trans));
    }
}

void Models::draw() {
    for(int i = 0; i<models.size();i++) {
        this->models[i]->draw();
    }
}

//-Group----------------------------------------------------------------------//

Group::Group(std::vector<PhysicScene*> transforms) {
    this->transforms = transforms;
}

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

Scene::Scene(Group* group) {
    this->group = group;
}

Scene::Scene(const char* xml_file) {
    //cout << "parse de Scene comecou" << endl;
    xml_document doc;
    xml_parse_result result;

    if( !(result = doc.load_file(xml_file)) ) {
        std::cout << "XML [" << xml_file << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (xml_file + result.offset) << "]\n\n";
    }
    xml_node models = doc.child("scene");

    this->group = new Group(models.first_child());
    //cout << "parse de Scene acabou" << endl;
}

void Scene::draw() {
    this->group->draw();
}
