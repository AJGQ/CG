#include "camera_fps.h"

float px=0,py=0,pz=0, angCamFPS_h=0, angCamFPS_v=0, x_telaFPS,y_telaFPS,velocidade_FPS=1;
int estado_botaoFPS=0;
//-Display-------//


void modo_fps(){
    
    //Câmera em modo explorador
	gluLookAt(px,py,pz,
	          px+sin(angCamFPS_h)*cos(angCamFPS_v), py+sin(angCamFPS_v), pz+cos(angCamFPS_h)*cos(angCamFPS_v),
              0.0f, 1.0f, 0.0f);
}


void mov_rato_fps(int x, int y){
    float teste;
    
    if(estado_botaoFPS){
        if(x_telaFPS!=x){
            angCamFPS_h+= (x_telaFPS-x)*0.002;
            x_telaFPS=x;
        }
        
        if(y_telaFPS!=y){
            teste= (y-y_telaFPS)*0.002;
            if(teste+angCamFPS_v>-M_PI_2 && teste+angCamFPS_v<M_PI_2 ){
                angCamFPS_v-=teste;
                y_telaFPS=y;
            }
        }
    }
    
   // printf("H: %f -- V: %f -- %f,%f,%f\n",angCamFPS_h,angCamFPS_v,px,py,pz);
   // glutPostRedisplay();

}

void rato_fps(int botao, int estado, int x, int y){
    if (botao==GLUT_LEFT_BUTTON){
        if (estado==GLUT_DOWN){
            estado_botaoFPS=1;
            x_telaFPS=x;
            y_telaFPS=y;
        }else
            estado_botaoFPS=0;
    }/*else{
        if (estado==GLUT_DOWN)
            do_Picking(x, y);
        
    }*/
    
        
}


void teclado_especial_fps(int tecla,int x, int y){
    switch (tecla) {
        case GLUT_KEY_UP:
            if(angCamFPS_v+0.05<M_PI_2)   //Para câmera não virar ao contrário
                angCamFPS_v+=0.05;
            break;
        case GLUT_KEY_DOWN:
           if(angCamFPS_v-0.05>-M_PI_2)  //Para câmera não virar ao contrário
                angCamFPS_v-=0.05;
            break;
            
        case GLUT_KEY_LEFT:
            angCamFPS_h+=0.05;
            break;
        case GLUT_KEY_RIGHT:
            angCamFPS_h-=0.05;
            break;
            
        default:
            break;
    }
   // glutPostRedisplay();
}

void teclado_normal_fps(unsigned char tecla,int x, int y){
    switch (tecla) {
        case 'd':
            px+=velocidade_FPS*sin(angCamFPS_h-M_PI_2);
            pz+=velocidade_FPS*cos(angCamFPS_h-M_PI_2);
            break;
        case 'a':
            px+=velocidade_FPS*sin(angCamFPS_h+M_PI_2);
            pz+=velocidade_FPS*cos(angCamFPS_h+M_PI_2);
            break;
        case 'w':
            px+=velocidade_FPS*sin(angCamFPS_h);
            pz+=velocidade_FPS*cos(angCamFPS_h);
            py+=velocidade_FPS*sin(angCamFPS_v);
            break;
        case 's':
            px-=velocidade_FPS*sin(angCamFPS_h);
            pz-=velocidade_FPS*cos(angCamFPS_h);
            py-=velocidade_FPS*sin(angCamFPS_v);
            break;
        
            
        default:
            break;
    }
 //   glutPostRedisplay();

}
