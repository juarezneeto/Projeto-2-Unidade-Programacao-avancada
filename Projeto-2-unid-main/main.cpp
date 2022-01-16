#include <iostream>
#include <fstream>
#include "sculptor.h"
#include "voxel.h"
using namespace std;

int main(void)
{
    //esfera e elipse
  sculptor esferaelipsoide(40,40,40);
    esferaelipsoide.putSphere(20,20,20,10);
    esferaelipsoide.writeOFF((char*)"Esfera.off");
    esferaelipsoide.putEllipsoid(20,20,20,15,10,7);
    esferaelipsoide.writeOFF((char*)"Elipsoide.off");

//pato donald
  sculptor pato(200,200,200);
    //cabeça
    pato.setColor(1,1,1,1);
    pato.putBox(30,45,30,45,30,45);
    //chapeu preto
    pato.setColor(0,0,0,1);
    pato.putBox(30,45,45,48,30,45);
    //chapeu azul
    pato.setColor(0.11,0.56,1,1);//azul claro
    pato.putBox(30,45,48,51,30,45);
    //corpo azul
    pato.setColor(0.11,0.56,1,1);
    pato.putBox(30,45,20,30,30,45);
    //corpo branco
    pato.setColor(1,1,1,1);
    pato.putBox(30,45,10,20,30,45);
    //pé 1
    pato.setColor(1,0.54,0,1);//laranja
    pato.putBox(33,36,0,10,34,39);
    pato.putBox(33,36,0,3,38,44);
    //pé 2
    pato.setColor(1,0.54,0,1);//laranja
    pato.putBox(39,42,0,10,34,39);
    pato.putBox(39,42,0,3,38,44);
    //bico
    pato.setColor(1,0.54,0,1);//laranja
    pato.cutBox(30,45,30,34,39,45);
    pato.putBox(30,45,30,34,39,49);
    //olhos
    pato.setColor(0,0,0,1);
    pato.cutBox(32,36,35,39,44,45);
    pato.putBox(32,36,35,39,44,45);
    pato.cutBox(39,43,35,39,44,45);
    pato.putBox(39,43,35,39,44,45);
    
    //braço direito
          //parte azul
          pato.setColor(0.11,0.56,1,1);
          pato.putBox(45,49,20,30,35,40);
          //parte amarela
          pato.setColor(1,1,0,1);
          pato.putBox(45,49,16,20,35,40);
          //parte branca
          pato.setColor(1,1,1,1);
          pato.putBox(45,49,12,16,35,40);
    //braço esquerdo
          //parte azul
          pato.setColor(0.11,0.56,1,1);
          pato.putBox(26,30,20,30,35,40);
          //parte amarela
          pato.setColor(1,1,0,1);
          pato.putBox(26,30,16,20,35,40);
           //parte branca
          pato.setColor(1,1,1,1);
         pato.putBox(26,30,12,16,35,40);

  
  //gravata
   pato.setColor(1,0,0,1); //vermelho
   pato.cutBox(35,40,26,30,44,45);
   pato.putBox(35,40,26,30,44,45);

   //rabo
    pato.setColor(1,1,1,1);
    pato.putBox(33,42,10,14,27,30);
   
   //aba do boné
    pato.setColor(0,0,0,1);
    pato.putBox(34,41,50,51,26,32);

    pato.writeOFF((char*)"Pato.off");

    
    return 0;
}