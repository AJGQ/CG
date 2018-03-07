
#include "parseXML.h"
#include <stdlib.h>
//#include <unistd.h>

extern vector<const char*> fileNameModels;

//-----------------------------------------------------------------------------//

void drawFile(const char* filePath){

    FILE* file;
    int i, cont, nbuff, *pos, *tot;
    char *typ;
    float x,y,z;

    file = fopen(filePath, "r");
    if(!file) error("opening file");
    fscanf(file,"%d\n",&nbuff);

    //fprintf(stderr,"%d\n", nbuff);

    pos = (int*)malloc(nbuff * sizeof(int));
    tot = (int*)malloc(nbuff * sizeof(int));
    typ = (char*)malloc(nbuff * sizeof(char));

    for(i=0, cont=0; i<nbuff; i++){
        fscanf(file,"%c%d\n", &typ[i], &tot[i]);
        pos[i] = cont;
        cont += tot[i];
    //fprintf(stderr,"%c%d\n", typ[i], tot[i]);
    }

    glGenBuffers(1, buffers);
    arrayFloat = (float *)(malloc(cont * 3 * sizeof(float)));

    for(i=0; fscanf(file,"%f:%f:%f\n",&x,&y,&z) != EOF; i+=3){
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

    for(i=0; i<nbuff; i++){
    //fprintf(stderr,"%c\n", typ[i]);
    //fprintf(stderr,"%d:%d\n", pos[i], tot[i]);
        switch(typ[i]){
            case 's' : glDrawArrays(GL_TRIANGLE_STRIP   , pos[i], tot[i]); break;
            case 'f' : glDrawArrays(GL_TRIANGLE_FAN     , pos[i], tot[i]); break;
            case 't' : glDrawArrays(GL_TRIANGLES        , pos[i], tot[i]); break;
            default  : error("array type bad specified");
        }
    }
}

//-----------------------------------------------------------------------------//

void drawFiles() {
    int i;
    for(i=0; i<fileNameModels.size(); i++) {
        drawFile(fileNameModels[i]);
    }
}

//-----------------------------------------------------------------------------//

void parseXML(char *fileXML){
    int i, size, len;
    xml_document doc;
    xml_parse_result result;

    if( !(result = doc.load_file(fileXML)) ) error( result.description() );
    xml_node models = doc.child("scene");

    for(xml_node model = models.first_child(); model; model = model.next_sibling()){
        for(xml_attribute attr = model.first_attribute(); attr; attr = attr.next_attribute()){
            len = strlen(attr.value())+1;
            char *model = (char*)malloc(len);
            strncpy(model, attr.value(), len);
            fileNameModels.push_back(model);
        }
    }
}
