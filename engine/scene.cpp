
#include "scene.h"
#include <stdlib.h>
#include <iostream>

//-Model----------------------------------------------------------------------//

Model::Model(const char* file) {
   this->file = file;
}

Model::Model(xml_node node) {
    //cout << "parse de Model comecou" << endl;
    this->file = (char*)malloc(50*sizeof(char));
    strcpy((char*)this->file, node.attribute("file").as_string());

    //cout << "parse de Model acabou" << endl;
}

void Model::doit() {

    FILE* file;
    int i, cont, nbuff, *pos, *tot;
    char *typ;
    float x,y,z;
    float redVal, greenVal, blueVal;

    file = fopen(this->file, "r");
    if(!file) {
        cout << "this->file: " << this->file << "file: " << file << endl;
        error("opening file");
    }
    fscanf(file,"%d\n",&nbuff);

    //fprintf(stderr,"%d\n", nbuff);

    pos = (int*)malloc(nbuff * sizeof(int));
    tot = (int*)malloc(nbuff * sizeof(int));
    typ = (char*)malloc(nbuff * sizeof(char));

    for(i=0, cont=0; i<nbuff; i++) {
        fscanf(file,"%c%d\n", &typ[i], &tot[i]);
        pos[i] = cont;
        cont += tot[i];
        //fprintf(stderr,"%c%d\n", typ[i], tot[i]);
    }

    glGenBuffers(1, buffers);
    arrayFloat = (float *)(malloc(cont * 3 * sizeof(float)));

    for(i=0; fscanf(file,"%f:%f:%f\n",&x,&y,&z) != EOF; i+=3) {
        //fprintf(stderr,"%f:%f:%f\n", x, y, z);
        arrayFloat[i] = x;
        arrayFloat[i+1] = y;
        arrayFloat[i+2] = z;
    }
    fclose(file);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,  cont * 3 * sizeof(float), arrayFloat, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    glVertexPointer(3,GL_FLOAT,0,0);

    for(i=0; i<nbuff; i++) {
        //fprintf(stderr,"%c\n", typ[i]);
        //fprintf(stderr,"%d:%d\n", pos[i], tot[i]);
        switch(typ[i]) {
            case 's' : glDrawArrays(GL_TRIANGLE_STRIP   , pos[i], tot[i]); break;
            case 'f' : glDrawArrays(GL_TRIANGLE_FAN     , pos[i], tot[i]); break;
            case 't' : glDrawArrays(GL_TRIANGLES        , pos[i], tot[i]); break;
            default  : error("array type bad specified");
        }
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

void Translate::doit() {
    glTranslatef(this->x,this->y,this->z);
}

//-Rotate---------------------------------------------------------------------//

Rotate::Rotate(float angle, float x, float y, float z) {
   this->angle = angle;
   this->x = x;
   this->y = y;
   this->z = z;
}

Rotate::Rotate(xml_node node) {
    //cout << "parse de Rotate comecou" << endl;
    xml_attribute aux_angle = node.attribute("angle");
    xml_attribute aux_x     = node.attribute("axisX");
    xml_attribute aux_y     = node.attribute("axisY");
    xml_attribute aux_z     = node.attribute("axisZ");

    this->angle = aux_angle ? aux_angle.as_float() : 0.0f;
    this->x     = aux_x     ? aux_x.as_float()     : 0.0f;
    this->y     = aux_y     ? aux_y.as_float()     : 0.0f;
    this->z     = aux_z     ? aux_z.as_float()     : 0.0f;
    //cout << "parse de Rotate acabou" << endl;
}

void Rotate::doit() {
    glRotatef(this->angle,this->x,this->y,this->z);
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

void Scale::doit() {
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

void Color::doit() {
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

void Models::doit() {
    for(int i = 0; i<models.size();i++) {
        this->models[i]->doit();
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

void Group::doit() {
    glPushMatrix();
    for(int i = 0; i<transforms.size(); i++) {
        this->transforms[i]->doit();
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

void Scene::doit() {
    this->group->doit();
}
