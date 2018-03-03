#include "parseXML.h"

extern vector<const char*> *fileName_models;

//----------------------------------------------------------------------//

void drawFile(const char* filePath){
    FILE* file;
    int i, cont, nbuff, *pos, *tot, *ind, j;
    char *typ;
    float x,y,z;
    fprintf(stderr, "ISTO FUNCIONA!! %s\n", filePath);
    if( !(file = fopen(filePath, "r")) ) error("opening file");

    fscanf(file,"%d",&nbuff);
    pos = (int*)malloc(nbuff * sizeof(int));
    tot = (int*)malloc(nbuff * sizeof(int));
    ind = (int*)malloc(nbuff * sizeof(int));
    typ = (char*)malloc(nbuff * sizeof(char));
    for(i=0, cont=0; i<nbuff; i++){
        fscanf(file,":%c%d", &typ[i], &tot[i]);
        pos[i] = cont;
        ind[i] = cont;
        cont += tot[i];
    }
    glGenBuffers(1, buffers);
    arrayFloat = (float *)(malloc(cont * 3 * sizeof(float)));
    while(fscanf(file,"%d:%f:%f:%f",&j,&x,&y,&z) != EOF){
        arrayFloat[ind[j]++] = x;
        arrayFloat[ind[j]++] = y;
        arrayFloat[ind[j]++] = z;
    }
    fclose(file);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER,  cont * 3 * sizeof(float), arrayFloat, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3,GL_FLOAT,0,0);
    for(i=0; i<nbuff; i++){
        switch(typ[i]){
            case 's' : glDrawArrays(GL_TRIANGLE_STRIP   , pos[i], tot[i]);
            case 'f' : glDrawArrays(GL_TRIANGLE_FAN     , pos[i], tot[i]);
            case 't' : glDrawArrays(GL_TRIANGLES        , pos[i], tot[i]);
            default  : error("array type bad specified");
        }
    }
}




//----------------------------------------------------------------------//

void drawFiles() {
    int i;
    for(i=0; i<fileName_models->size(); i++) {
        cout << "drawFiles: " << (*fileName_models)[i] << endl;
    }
}

//----------------------------------------------------------------------//


void parseXML(char *fileXML){
    int i;
    xml_document doc;
    xml_parse_result result;

    if( !(result = doc.load_file(fileXML)) ) error( result.description() );
    xml_node models = doc.child("scene");
//    cout << models.name() << endl;

    for(xml_node model = models.first_child(); model; model = model.next_sibling()){
//        cout << " " << model.name() << endl;
        for(xml_attribute attr = model.first_attribute(); attr; attr = attr.next_attribute()){
            fileName_models->push_back(attr.value());
//            cout << "  " << attr.name() << " = " << attr.value() << endl;
        }
    }
    cout << endl;
    for(i=0; i<fileName_models->size(); i++) {
        cout << "parser: " << (*fileName_models)[i] << endl;
    }
}


