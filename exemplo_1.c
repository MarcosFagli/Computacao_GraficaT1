
// gcc -c cg2d.c
// gcc exemplo_1.c -o exemplo_1 cg2d.o -lm -lX11 

#include "cg2d.h"

int main(int argc, char ** argv) {
  
  palette * palheta;
  bufferdevice * dispositivo;
  window * janela;
  viewport * view;
  viewport * view2;
  hObject * poligono1, * poligono2, * poligono3;
  
  SetWorld(-20, 10, -20, 15); // Define o tamanho do mundo  
  dispositivo = CreateBuffer(640,480); // cria um dispositivo
  
  palheta = CreatePalette(6);  
  SetColor(0,0,0,palheta);
  SetColor(1,0,0,palheta);
  SetColor(0,1,0,palheta);
  SetColor(0,0,1,palheta);
  SetColor(1,1,1,palheta);
  
  poligono1 = CreateHObject(5);
  poligono2 = CreateHObject(4);
  
  SetHObject(SetHPoint(-9.0,-8.0,1,1), poligono1);
  SetHObject(SetHPoint(-7.0,-3.0,1,1), poligono1);
  SetHObject(SetHPoint(-4.0,-4.0,1,1), poligono1);
  SetHObject(SetHPoint(-3.0,-6.0,1,1), poligono1);
  SetHObject(SetHPoint(-6.0,-9.0,1,1), poligono1);
  
  SetHObject(SetHPoint(-6.0,-2.0,1,3), poligono2);
  SetHObject(SetHPoint(-1.0,-2.0,1,3), poligono2);
  SetHObject(SetHPoint(-1.0,-6.0,1,3), poligono2);
  SetHObject(SetHPoint(-6.0,-6.0,1,3), poligono2);

  poligono3 = TransObj(poligono1, SetMatrixCis(0.5,0.0));
  
  //janela = CreateWindow(-8.0,5.0,-7.0,5.0); // define uma janela de visualização
  janela = CreateWindow(-10.0,0.0,-10.0,0.0);  

  //Criação da view que estará dentro da janela
  view = CreateView(0, 500, 0, 500);
  view2 = CreateView(20, 520, 20, 520);
  
  DrawObjectH(poligono1,janela,dispositivo, view); // desenha o poligono 1 dentro da janela no buffer do dispositivo 
  DrawObjectH(poligono2,janela,dispositivo, view); // desenha o poligono 2 dentro da janela no buffer do dispositivo
  DrawObjectH(poligono1,janela,dispositivo, view2); // desenha o poligono 1 dentro da janela no buffer do dispositivo 
  DrawObjectH(poligono2,janela,dispositivo, view2); // desenha o poligono 1 dentro da janela no buffer do dispositivo 
  
  Dump2X(dispositivo,palheta);
 
  return 0;
  }
