#include "camera_explorador.h"

float raio=20,angCam_h=0,angCam_v=0.5,angAux_h=0,angAux_v=0,x_tela,y_tela,look[]={0,0,0},avanco=0.5;

int estado_botao=0;


//Modo Explorador

void modo_explorador(){
    //Câmera em modo explorador
	gluLookAt(look[0]+(raio)*sin(angCam_h+angAux_h)*cos(angCam_v+angAux_v),look[1]+(raio)*sin(angCam_v+angAux_v),look[2]+(raio)*cos(angCam_h+angAux_h)*cos(angCam_v+angAux_v),
	          look[0], look[1], look[2],
              0.0f, 1.0f, 0.0f);
}

//Funçoes para o Rato
void rato_explorador(int botao, int estado, int x, int y){
    if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        estado_botao=1;
        x_tela = x;
        y_tela = y;
    }else if(botao == 3){
        raio = raio<1? 1: raio-0.3;
    }else if(botao == 4){
        raio += 0.3;
    }
    else{
        estado_botao=0;
    }
    //spherical2Cartesian();
    glutPostRedisplay();
}

void mov_rato_explorador(int x, int y){
    angCam_h -= ((float)(x - x_tela))/50;
    float aux = angCam_v + ((float)(y - y_tela))/50;
    if(aux<M_PI/2-0.1 && aux>-M_PI/2+0.1)   angCam_v = aux;
    else if( aux>=M_PI/2-0.1 )              angCam_v = M_PI/2-0.1;
    else                                    angCam_v = -M_PI/2+0.1;
    x_tela = x;
    y_tela = y;
    //spherical2Cartesian();
    glutPostRedisplay();
}

//Funçoes para o teclado
void teclado_normal_explorador(unsigned char tecla,int x, int y){
    switch (tecla) {
        case 'a':
            raio-=avanco;
            break;
        case 'd':
            raio+=avanco;
            break;
            
        default:
            break;
    }
  //  glutPostRedisplay();
}

void teclado_especial_explorador(int tecla,int x, int y){
    switch (tecla) {
        
        case GLUT_KEY_UP:
            if(angCam_v+0.05<M_PI_2)   //Para câmera não virar ao contrário
                angCam_v+=0.05;
            break;
        case GLUT_KEY_DOWN:
            if(angCam_v-0.05>-M_PI_2)  //Para câmera não virar ao contrário
                angCam_v-=0.05;
            break;
            
        case GLUT_KEY_LEFT:
            angCam_h-=0.05;
            break;
        case GLUT_KEY_RIGHT:
            angCam_h+=0.05;
            break;
            
        default:
            break;
    }
   // glutPostRedisplay();
}