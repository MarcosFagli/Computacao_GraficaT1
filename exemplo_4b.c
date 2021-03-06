
// gcc -c cg2d.c
// gcc exemplo_4b.c -o exemplo_4b cg2d.o -lm -lX11 

#include "cg2d.h"

int main(int argc, char ** argv) {
  
  palette * palheta;
  bufferdevice * dispositivo;
  window * janela;
  viewport * view;
  viewport * view2;
  hObject ** objetos; 
  hObject * poligono1, * poligono2, * poligono3;
  hmatrix * matrixRot; 
  hmatrix * matrixTransf; 
  hmatrix * matrixScale; 
  int nObjects = 2;
  float dx, dy, sx, sy;
  float theta = 45;
  
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
  poligono3 = CreateHObject(5);
  
  SetHObject(SetHPoint(-9.0,-8.0,1,1), poligono1);
  SetHObject(SetHPoint(-7.0,-3.0,1,1), poligono1);
  SetHObject(SetHPoint(-4.0,-4.0,1,1), poligono1);
  SetHObject(SetHPoint(-3.0,-6.0,1,1), poligono1);
  SetHObject(SetHPoint(-6.0,-9.0,1,1), poligono1);
  
  SetHObject(SetHPoint(-6.0,-2.0,1,3), poligono2);
  SetHObject(SetHPoint(-1.0,-2.0,1,3), poligono2);
  SetHObject(SetHPoint(-1.0,-6.0,1,3), poligono2);
  SetHObject(SetHPoint(-6.0,-6.0,1,3), poligono2);
  
  SetHObject(SetHPoint(-9.0,-8.0,1,2), poligono3);
  SetHObject(SetHPoint(-7.0,-3.0,1,2), poligono3);
  SetHObject(SetHPoint(-4.0,-4.0,1,2), poligono3);
  SetHObject(SetHPoint(-3.0,-6.0,1,2), poligono3);
  SetHObject(SetHPoint(-6.0,-9.0,1,2), poligono3);

  //Define uma janela de visualização como no enunciado
  //janela = CreateWindow(-2.0,2.0,-2.0,2.0);  
  janela = CreateWindow(-6.0,0.0,-5.0,0.0);  

  //Criação da view que estará dentro da janela como no enunciado
  view = CreateView(170, 470, 140, 340);


  //Aloca memoria para o array de objects
  objetos = (hObject **) malloc(sizeof(hObject *));
  for(int i = 0; i < nObjects; i++){
    objetos[i] = (hObject *) malloc(sizeof(hObject));
  }
  objetos[0] = poligono1;
  objetos[1] = poligono2;
  ObjCenter(nObjects, objetos, janela);
  poligono1 = objetos[0];
  poligono2 = objetos[1];

  //Como no caso anterior, quando se realiza a rotação, a mesma é executada em torno da origem, assim temos que ajustar, realizando as seguintes operações: mudança de coordenada para a origem; rotacionar; e por fim outra mudandça de coordenadas para podermos visualizar as alterações de rotação
  dx = 2.0;
  dy = 2.0;
  matrixTransf = SetSftMatrix(dx, dy);
  matrixRot = SetRotMatrix(theta);
  poligono3 = TransObj(poligono3, matrixTransf);
  poligono3 = RotObj(poligono3, matrixRot);

  dx = 6;
  dy = -0.5;
  matrixTransf = SetSftMatrix(dx, dy);
  poligono3 = TransObj(poligono3, matrixTransf);

  //Ajustando as imagens para o nova janela solicitada
  sx = 0.2;
  sy = 0.2;
  matrixScale = SetSclMatrix(sx, sy);
  poligono1  = SclObj(poligono1, matrixScale);
  poligono2  = SclObj(poligono2, matrixScale);
  poligono3  = SclObj(poligono3, matrixScale);


  //Desenhando os objetos
  DrawObjectH(poligono1,janela,dispositivo, view); // desenha o poligono 1 dentro da janela no buffer do dispositivo 
  DrawObjectH(poligono2,janela,dispositivo, view); // desenha o poligono 2 dentro da janela no buffer do dispositivo
  DrawObjectH(poligono3,janela,dispositivo, view); // desenha o poligono 2 dentro da janela no buffer do dispositivo
  
  Dump2X(dispositivo,palheta);
 
  return 0;
  }
