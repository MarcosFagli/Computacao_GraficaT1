#include "cg2d.h"

//SetWord original para configurar a viewport
void SetWorld(float xmin, float xmax, float ymin, float ymax) {
 XWMax = xmax;
 XWMin = xmin;
 YWMax = ymax;
 YWMin = ymin;
 }

//CreateView é responsável pela criação da view 
viewport * CreateView(int xmin, int xmax, int ymin, int ymax) {
  viewport * view;
  
  view = (viewport *) malloc(sizeof(viewport));
  view->xmin = xmin;
  view->xmax = xmax;
  view->ymin = ymin;
  view->ymax = ymax;

  return view;
}

//SetPoint original
point * SetPoint(float x, float y, int color) {
  point * pnt;
  
  pnt = (point *) malloc(sizeof(point)); 
  pnt->x = x;
  pnt->y = y;
  pnt->color = color;
  
  return pnt;
  }

//Edição do SetPoint para SetHPoint com coordenadas homogeneas
hpoint * SetHPoint(float x, float y, float w, int color) {
  hpoint * pnt;
  
  pnt = (hpoint *) malloc(sizeof(hpoint)); 
  pnt->x = x/w;
  pnt->y = y/w;
  pnt->w = w;
  pnt->color = color;
  
  return pnt;
  }

//CreateObject original 
object * CreateObject(int numbers_of_points) {
  object * ob;
 
  ob = (object *) malloc(sizeof(object));
  ob->numbers_of_points = 0;
  ob->points = (point *) malloc(numbers_of_points*sizeof(point));
 
  return ob;
  }

//CreateObject modificado para hpoint
hObject * CreateHObject(int numbers_of_points) {
  hObject * ob;
 
  ob = (hObject *) malloc(sizeof(hObject));
  ob->numbers_of_points = 0;
  ob->points = (hpoint *) malloc(numbers_of_points*sizeof(hpoint));

  return ob;
  }

//SetObject original
int SetObject(point * pnt, object * ob) {
  ob->points[ob->numbers_of_points] = *pnt;
  ob->numbers_of_points = ob->numbers_of_points + 1;

  return 0;
  }

//SetObject modificado para homogeneo
int SetHObject(hpoint * pnt, hObject * ob) {
  ob->points[ob->numbers_of_points] = *pnt;
  ob->numbers_of_points = ob->numbers_of_points + 1;

  return 0;
  }

//ChangeColor original e nao sera modificada
object * ChangeColor(object * ob, int color) {
  object * oob;
  int i;
  
  oob = CreateObject(ob->numbers_of_points); 
  for(i=0;i<ob->numbers_of_points;i++) {
    SetObject(SetPoint(ob->points[i].x,ob->points[i].y,color),oob);    
    }
    
  return oob;  
  }

//CreatePalette original e nao sera modificado
palette * CreatePalette(int numbers_of_colors) {
  palette * pal;

  pal = (palette *) malloc(sizeof(palette));
  pal->numbers_of_colors = 0;
  pal->colors = (ColorValues *) malloc(numbers_of_colors*sizeof(ColorValues));
  
  return pal;
  }

//SetColor original e nao sera modificado
int SetColor(float red, float green, float blue, palette * pal) {
  pal->colors[pal->numbers_of_colors].red = red;
  pal->colors[pal->numbers_of_colors].green = green;
  pal->colors[pal->numbers_of_colors].blue = blue;
  pal->numbers_of_colors = pal->numbers_of_colors + 1;

  return 0;
  }
  
//GetColor original e nao sera modificado
ColorValues * GetColor(int value, palette * pal) {
 ColorValues * color;
 
 color = (ColorValues *) malloc(sizeof(ColorValues)); 
 color->red = pal->colors[value].red;
 color->green = pal->colors[value].green;
 color->blue = pal->colors[value].blue; 
 
 return color;
 }

//CreateBuffer original e nao sera modificado
bufferdevice * CreateBuffer(int maxx, int maxy) {
  bufferdevice * dev;
  
  dev = (bufferdevice *) malloc(sizeof(bufferdevice));
  dev->MaxX = maxx;
  dev->MaxY = maxy;
  dev->buffer = (int *) malloc(maxx*maxy*sizeof(int));
    
  return dev;
  }
  
//CreateWindow original e nao sera modificado
window * CreateWindow(float xmin, float xmax, float ymin, float ymax) {
  window * win;

  win = (window *) malloc(sizeof(window));
  win->xmin = xmin;
  win->xmax = xmax;
  win->ymin = ymin;
  win->ymax = ymax;
  
  return win;
  }

//Sru2Srn original
point * Sru2Srn(point * ponto, window * janela) {
  point * np;

  np = (point *) malloc(sizeof(point));
  np->x = (ponto->x - janela->xmin)/(janela->xmax - janela->xmin);
  np->y = (ponto->y - janela->ymin)/(janela->ymax - janela->ymin);
  np->color = ponto->color;
  
  return np;  
  }

//Sru2Srn modificada para homogeneo
hpoint * Sru2SrnH(hpoint * ponto, window * janela) {
  hpoint * np;

  np = (hpoint *) malloc(sizeof(hpoint));
  np->x = (ponto->x - janela->xmin)/(janela->xmax - janela->xmin);
  np->y = (ponto->y - janela->ymin)/(janela->ymax - janela->ymin);
  np->w = ponto->w;
  np->color = ponto->color;
  
  return np;  
  }


//Srn2Srd original
point * Srn2Srd(point * ponto, bufferdevice * dev) {
  point * dpt;

  dpt = (point *) malloc(sizeof(point));
  dpt->x = round((ponto->x)*(dev->MaxX - 1));
  dpt->y = round((ponto->y)*(dev->MaxY - 1));
  dpt->color = ponto->color;
 
  return dpt;
  }

//Srn2Srd modificada para homogeneo
hpoint * Srn2SrdH(hpoint * ponto, viewport * view) {
  hpoint * dpt;

  dpt = (hpoint *) malloc(sizeof(hpoint));
  dpt->x = view->xmin + round((ponto->x)*(view->xmax - view->xmin) -1);
  dpt->y = view->ymin + round((ponto->y)*(view->ymax - view->ymin) -1);
  dpt->w = ponto->w;
  dpt->color = ponto->color;
 
  return dpt;
  }

//InWin original
int InWin(point * pt, window * win) {
  if ((pt->x >= win->xmin)&&(pt->x <= win->xmax)&&(pt->y >= win->ymin)&&(pt->y <= win->ymax)) return 1;
  else return 0;
  }

//InWin modificado para homogeneo
int InWinH(hpoint * pt, window * win) {
  if ((pt->x >= win->xmin)&&(pt->x <= win->xmax)&&(pt->y >= win->ymin)&&(pt->y <= win->ymax)) return 1;
  else return 0;
  }

//InterX originial
point * InterX(point * p1, point * p2, float x) {
 float a , b, aux;
 
 if (p2->x - p1->x) {
   a = (p2->y - p1->y)/(p2->x - p1->x);
   b = p1->y - a*p1->x;
   aux = a*x+b;
   }
 else aux = 1000000.0;  
 
 return SetPoint(x,aux,p1->color);
 }

//InterX modificado para homogeneo
hpoint * InterXH(hpoint * p1, hpoint * p2, float x) {
 float a , b, aux;
 
 if (p2->x - p1->x) {
   a = (p2->y - p1->y)/(p2->x - p1->x);
   b = p1->y - a*p1->x;
   aux = a*x+b;
   }
 else aux = 1000000.0;  
 
 return SetHPoint(x,aux,p1->w,p1->color);
 }

//InterY original
point * InterY(point * p1, point * p2, float y) {
 float a , b, aux;

 if (p2->x - p1->x) {
   a = (p2->y - p1->y)/(p2->x - p1->x);
   b = p1->y - a*p1->x;
   if (a) aux = (y-b)/a;
   else aux = 1000000.0;
   }
 else aux = p2->x;
 
 return SetPoint(aux,y,p1->color);
 }

//InterY modificado para homogeneo
hpoint * InterYH(hpoint * p1, hpoint * p2, float y) {
 float a , b, aux;

 if (p2->x - p1->x) {
   a = (p2->y - p1->y)/(p2->x - p1->x);
   b = p1->y - a*p1->x;
   if (a) aux = (y-b)/a;
   else aux = 1000000.0;
   }
 else aux = p2->x;
 
 return SetHPoint(aux,y,p1->w,p1->color);
 }

//DrawLine original
int DrawLine(point * p1, point * p2, window * win, bufferdevice * dev, int color) {
  float a, b;
  int i, j, aux;
  point * pn1, * pd1, * pn2, * pd2;
  
  pn1 = Sru2Srn(p1,win);
  pd1 = Srn2Srd(pn1,dev);
  pn2 = Sru2Srn(p2,win);
  pd2 = Srn2Srd(pn2,dev);
  
  if (pd1->x > pd2->x) {
    aux = pd1->x;
    pd1->x = pd2->x;
    pd2->x = aux;
    aux = pd1->y;
    pd1->y = pd2->y;
    pd2->y = aux;
    }

   i = pd1->x;
   j = pd1->y;
   
   if (pd1->x == pd2->x) {
     while (j < pd2->y) {
       dev->buffer[(dev->MaxY - j - 1) * dev->MaxX + i] = color;
       j++;
       }
     }
   else {
     a = (pd2->y - pd1->y)/(pd2->x - pd1->x);
     b = pd1->y - a*pd1->x;
     while (i < pd2->x) {
       dev->buffer[(dev->MaxY - j - 1) * dev->MaxX + i] = color;
       aux = j;
       j = round(a*(++i) + b);
       
       if (j > aux) {
	 while (aux < j) {
	   dev->buffer[(dev->MaxY - aux - 1) * dev->MaxX + i] = color; 
	   aux++;
	   }
         }
       if (j < aux) {
	 while (aux > j) { 
	   dev->buffer[(dev->MaxY - aux - 1) * dev->MaxX + i] = color;
	   aux--;
	   }
         }
        
       }
     }

  return 0;
  }

//DrawLine modificada para homogenea
int DrawLineH(hpoint * p1, hpoint * p2, window * win, bufferdevice * dev, viewport * view, int color) {
  float a, b;
  int i, j, aux;
  hpoint * pn1, * pd1, * pn2, * pd2;
  
  pn1 = Sru2SrnH(p1,win);
  pd1 = Srn2SrdH(pn1,view);
  pn2 = Sru2SrnH(p2,win);
  pd2 = Srn2SrdH(pn2,view);
  
  if (pd1->x > pd2->x) {
    aux = pd1->x;
    pd1->x = pd2->x;
    pd2->x = aux;
    aux = pd1->y;
    pd1->y = pd2->y;
    pd2->y = aux;
    }

   i = pd1->x;
   j = pd1->y;
   
   if (pd1->x == pd2->x) {
     while (j < pd2->y) {
       dev->buffer[(view->ymin + view->ymax - j) * dev->MaxX + i] = color;
       j++;
       }
     }
   else {
     a = (pd2->y - pd1->y)/(pd2->x - pd1->x);
     b = pd1->y - a*pd1->x;
     while (i < pd2->x) {
       dev->buffer[(view->ymin + view->ymax - j) * dev->MaxX + i] = color;
       aux = j;
       j = round(a*(++i) + b);
       
       if (j > aux) {
         while (aux < j) {
           dev->buffer[(view->ymin + view->ymax - aux) * dev->MaxX + i] = color; 
           aux++;
           }
         }
       if (j < aux) {
         while (aux > j) { 
           dev->buffer[(view->ymin + view->ymax - aux) * dev->MaxX + i] = color;
           aux--;
          }
         }
        
       }
     }

  return 0;
  }

//DrawObject original
int DrawObject(object * ob, window * win, bufferdevice * dev) {
  int i;
  float aux;
  point * p1, * p2, * paux;
  
  for(i=0;i<ob->numbers_of_points;i++) {
    p1 = SetPoint(ob->points[i].x,ob->points[i].y,ob->points[i].color);
    p2 = SetPoint(ob->points[(i+1)%ob->numbers_of_points].x,ob->points[(i+1)%ob->numbers_of_points].y,ob->points[(i+1)%ob->numbers_of_points].color);
    
    if (p1->y > p2->y) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      }   
    if ((p1->y < win->ymax)&&(p2->y > win->ymax)) {
      paux = InterY(p1,p2,win->ymax);
      if (InWin(paux,win)) {
        p2 = paux;
        } 
      }
    if ((p1->y < win->ymin)&&(p2->y > win->ymin)) {
      paux = InterY(p1,p2,win->ymin);
      if (InWin(paux,win)) {
        p1 = paux;
        } 
      }

    if (p1->x > p2->x) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      }      
    if ((p1->x < win->xmax)&&(p2->x > win->xmax)) {
      paux = InterX(p1,p2,win->xmax);
      if (InWin(paux,win)) {
        p2 = paux;
        } 
      }
    if ((p1->x < win->xmin)&&(p2->x > win->xmin)) {
      paux = InterX(p1,p2,win->xmin);
      if (InWin(paux,win)) {
        p1 = paux;
        } 
      }

    if ((InWin(p1,win))&&(InWin(p2,win))) DrawLine(p1,p2,win,dev,p1->color);
    }

  return 0;
  }

//DrawObject modificado para homogeneo
int DrawObjectH(hObject * ob, window * win, bufferdevice * dev, viewport * view) {
  int i;
  float aux;
  hpoint * p1, * p2, * paux;
  
  for(i=0;i<ob->numbers_of_points;i++) {
    p1 = SetHPoint(ob->points[i].x, ob->points[i].y, ob->points[i].w, ob->points[i].color);
    p2 = SetHPoint(ob->points[(i+1)%ob->numbers_of_points].x, ob->points[(i+1)%ob->numbers_of_points].y, ob->points[(i+1)%ob->numbers_of_points].w, ob->points[(i+1)%ob->numbers_of_points].color);
    
    if (p1->y > p2->y) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      }   
    if ((p1->y < win->ymax)&&(p2->y > win->ymax)) {
      paux = InterYH(p1,p2,win->ymax);
      if (InWinH(paux,win)) {
        p2 = paux;
        } 
      }
    if ((p1->y < win->ymin)&&(p2->y > win->ymin)) {
      paux = InterYH(p1,p2,win->ymin);
      if (InWinH(paux,win)) {
        p1 = paux;
        } 
      }

    if (p1->x > p2->x) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      }      
    if ((p1->x < win->xmax)&&(p2->x > win->xmax)) {
      paux = InterXH(p1,p2,win->xmax);
      if (InWinH(paux,win)) {
        p2 = paux;
        } 
      }
    if ((p1->x < win->xmin)&&(p2->x > win->xmin)) {
      paux = InterXH(p1,p2,win->xmin);
      if (InWinH(paux,win)) {
        p1 = paux;
        } 
      }

    if ((InWinH(p1,win))&&(InWinH(p2,win))) DrawLineH(p1,p2,win, dev, view,p1->color);
    }

  return 0;
  }

// Uma nova função para desenhar as bordas da viewport no monitor
int DrawViewPort(viewport * port, bufferdevice * dev, int color) {
  int i, j;

  for(i=port->xmin;i<port->xmax;i++) {
    dev->buffer[port->ymin * dev->MaxX + i] = color;
    dev->buffer[port->ymax * dev->MaxX + i] = color; 
    }

  for(j=port->ymin;j<=port->ymax;j++) {
    dev->buffer[j * dev->MaxX + port->xmin] = color;
    dev->buffer[j * dev->MaxX + port->xmax] = color; 
    }

  return 1;
  }

//DrawObject modificado para homogeneo incluindo cor
int DrawObjectHC(hObject * ob, window * win, bufferdevice * dev, viewport * view, int color) {
  int i;
  float aux;
  hpoint * p1, * p2, * paux;

  DrawViewPort(view,dev,1);
  
  for(i=0;i<ob->numbers_of_points;i++) {
    p1 = SetHPoint(ob->points[i].x, ob->points[i].y, ob->points[i].w, ob->points[i].color);
    p2 = SetHPoint(ob->points[(i+1)%ob->numbers_of_points].x, ob->points[(i+1)%ob->numbers_of_points].y, ob->points[(i+1)%ob->numbers_of_points].w, ob->points[(i+1)%ob->numbers_of_points].color);
    
    if (p1->y > p2->y) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      }   
    if ((p1->y < win->ymax)&&(p2->y > win->ymax)) {
      paux = InterYH(p1,p2,win->ymax);
      if (InWinH(paux,win)) {
        p2 = paux;
        } 
      }
    if ((p1->y < win->ymin)&&(p2->y > win->ymin)) {
      paux = InterYH(p1,p2,win->ymin);
      if (InWinH(paux,win)) {
        p1 = paux;
        } 
      }

    if (p1->x > p2->x) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      }      
    if ((p1->x < win->xmax)&&(p2->x > win->xmax)) {
      paux = InterXH(p1,p2,win->xmax);
      if (InWinH(paux,win)) {
        p2 = paux;
        } 
      }
    if ((p1->x < win->xmin)&&(p2->x > win->xmin)) {
      paux = InterXH(p1,p2,win->xmin);
      if (InWinH(paux,win)) {
        p1 = paux;
        } 
      }

    if ((InWinH(p1,win))&&(InWinH(p2,win))) DrawLineH(p1,p2,win, dev, view, color);
    }

  return 0;
  }

//Rotate original
object * Rotate(object * ob, float theta) {
  object * oob;
  int i;
  float phi;
  
  phi = (theta*PI)/180.0;
  oob = CreateObject(ob->numbers_of_points); 
  for(i=0;i<ob->numbers_of_points;i++) {
    SetObject(SetPoint((ob->points[i].x)*cos(phi)-(ob->points[i].y)*sin(phi),(ob->points[i].x)*sin(phi)+(ob->points[i].y)*cos(phi),ob->points[i].color),oob);    
    }
    
  return oob;
  }

//Rotate modificado para homogenea
hObject * RotateH(hObject * ob, float theta) {
  hObject * oob;
  int i;
  float phi;
  
  phi = (theta*PI)/180.0;
  oob = CreateHObject(ob->numbers_of_points); 
  for(i=0;i<ob->numbers_of_points;i++) {
    SetHObject(SetHPoint((ob->points[i].x)*cos(phi)-(ob->points[i].y)*sin(phi),(ob->points[i].x)*sin(phi)+(ob->points[i].y)*cos(phi), ob->points[i].w, ob->points[i].color),oob);    
    }
    
  return oob;
  }
  
object * Translate(object * ob, float x, float y) {
  object * oob;
  int i;
  
  oob = CreateObject(ob->numbers_of_points); 
  for(i=0;i<ob->numbers_of_points;i++) {
    SetObject(SetPoint(ob->points[i].x + x,ob->points[i].y + y,ob->points[i].color),oob);    
    }
    
  return oob;
  }

object * Scale(object * ob, float sx, float sy) {
  object * oob;
  int i;
  
  oob = CreateObject(ob->numbers_of_points); 
  for(i=0;i<ob->numbers_of_points;i++) {
    SetObject(SetPoint(sx*(ob->points[i].x),sy*(ob->points[i].y),ob->points[i].color),oob);    
    }
    
  return oob;  
  }

//Implementação da função de cisalhamento
hmatrix * SetMatrixCis(float Sx, float Sy) {
	hmatrix * m;

	m = (hmatrix *) malloc(sizeof(hmatrix));
	 
	m->a11 = 1.0;  m->a12 = Sx;   m->a13 = 0;
	m->a21 = Sy;   m->a22 = 1.0;  m->a23 = 0;
	m->a31 = 0.0;  m->a32 = 0.0;  m->a33 = 1.0;

	printf("Passou\n");

	return m;
}

//Transformação do objeto para aplicar operações como de cisalhamento
hObject * TransObj(hObject * ob, hmatrix * m) {
  int i;
  hObject * obj;
  hpoint * p, * pt;

  obj = CreateHObject(ob->numbers_of_points);
  
  for(i=0;i<ob->numbers_of_points;i++) {
     p = SetHPoint(ob->points[i].x,ob->points[i].y,ob->points[i].w,ob->points[i].color);
     pt = LinearTransf(m,p);
     SetHObject(SetHPoint(pt->x,pt->y,pt->w,pt->color),obj);
     }

  return obj;
  }

hpoint * LinearTransf(hmatrix * m, hpoint * p) {
  hpoint * pt;
  
  pt = (hpoint *) malloc(sizeof(hpoint));
  
  pt->x = m->a11*p->x + m->a12*p->y + m->a13*p->w;
  pt->y = m->a21*p->x + m->a22*p->y + m->a23*p->w;
  pt->w = m->a31*p->x + m->a32*p->y + m->a33*p->w;
  pt->color = p->color;
  
  return pt;
  }

hmatrix * ComposeMatrix(hmatrix * m1, hmatrix * m2) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = m1->a11*m2->a11 + m1->a12*m2->a21 + m1->a13*m2->a31;
  m->a12 = m1->a11*m2->a12 + m1->a12*m2->a22 + m1->a13*m2->a32;
  m->a13 = m1->a11*m2->a13 + m1->a12*m2->a23 + m1->a13*m2->a33;
  
  m->a21 = m1->a21*m2->a11 + m1->a22*m2->a21 + m1->a23*m2->a31;
  m->a22 = m1->a21*m2->a12 + m1->a22*m2->a22 + m1->a23*m2->a32;
  m->a23 = m1->a21*m2->a13 + m1->a22*m2->a23 + m1->a23*m2->a33;
  
  m->a31 = m1->a31*m2->a11 + m1->a32*m2->a21 + m1->a33*m2->a31;
  m->a32 = m1->a31*m2->a12 + m1->a32*m2->a22 + m1->a33*m2->a32;
  m->a33 = m1->a31*m2->a13 + m1->a32*m2->a23 + m1->a33*m2->a33;
  
  return m;
  }

hmatrix * SetRotMatrix(float th) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = cos((th*PI)/180.0); m->a12 = (-1.0)*sin((th*PI)/180.0); m->a13 = 0.0;
  m->a21 = sin((th*PI)/180.0); m->a22 = cos((th*PI)/180.0);        m->a23 = 0.0;
  m->a31 = 0.0;                m->a32 = 0.0;                       m->a33 = 1.0;
  
  return m;
  }

hmatrix * SetSclMatrix(float sx, float sy) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = sx;  m->a12 = 0.0;  m->a13 = 0.0;
  m->a21 = 0.0; m->a22 = sy;   m->a23 = 0.0;
  m->a31 = 0.0; m->a32 = 0.0;  m->a33 = 1.0;
  
  return m;
  }



hmatrix * SetSftMatrix(float dx, float dy) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = 1.0;  m->a12 = 0.0;  m->a13 = dx;
  m->a21 = 0.0;  m->a22 = 1.0;  m->a23 = dy;
  m->a31 = 0.0;  m->a32 = 0.0;  m->a33 = 1.0;
  
  return m;  
  }

ColorValues * RGB2HSV(ColorValues * rgb) {
  float r, g, b, h, s, v, max, min;
  ColorValues * hsv;
  
  r = rgb->red;
  g = rgb->green;
  b = rgb->blue;
  
  if ((r>=g)&&(r>=b)) max = r;
  if ((g>=r)&&(g>=b)) max = g;
  if ((b>=g)&&(b>=r)) max = b;
  
  if ((r<=g)&&(r<=b)) min = r;
  if ((g<=r)&&(g<=b)) min = g;
  if ((b<=g)&&(b<=r)) min = b;
  
  v = max;
  
  s = (max-min)/max;
  
  if ((max==r)&&(g>=b)) h = 60.0 * (g-b)/(max-min);
  if ((max==r)&&(g<b)) h = 60.0 * (g-b)/(max-min) + 360;
  if (max==g) h = 60.0 * (b-r)/(max-min) + 120;
  if (max==b) h = 60.0 * (r-g)/(max-min) + 240; 
  
  hsv = (ColorValues *) malloc(sizeof(ColorValues));
  
  hsv->red = h;
  hsv->green = s;
  hsv->blue = v;
  
  return hsv;
  }

hObject * RotObj(hObject * obj, hmatrix * m) {
  hObject * oob;
  int i;
  
  oob = CreateHObject(obj->numbers_of_points); 
  for(i=0;i<obj->numbers_of_points;i++) {
    SetHObject(LinearTransf(m, &(obj->points[i])),oob);    
    }
    
  return oob;
  }

hObject * SclObj(hObject * obj, hmatrix * m) {
  hObject * oob;
  int i;
  
  oob = CreateHObject(obj->numbers_of_points); 
  for(i=0;i<obj->numbers_of_points;i++) {
    SetHObject(LinearTransf(m, &(obj->points[i])),oob);    
    }
    
  return oob;
  }

//Centralizar objetos
void ObjCenter(int nObjects, hObject ** objs, window * win){

  int xMax = -10000000;
  int xMin = 10000000;
  int yMax = -10000000;
  int yMin = 10000000;

  int xCenter = (win->xmax + win->xmin)/2;
  int yCenter = (win->ymax + win->ymin)/2;
  int xObjCenter;
  int yObjCenter;
  int dx, dy;
  hmatrix * matrixTransf;
  int i, j;

  for(i = 0; i < nObjects; i++){
    for(j = 0; j < objs[i]->numbers_of_points; j++){
      if(objs[i]->points[j].x > xMax){
        xMax = objs[i]->points[j].x;
      }
      if(objs[i]->points[j].x < xMin){
        xMin = objs[i]->points[j].x;
      }
      if(objs[i]->points[j].y > yMax){
        yMax = objs[i]->points[j].y;
      }
      if(objs[i]->points[j].y < xMin){
        yMin = objs[i]->points[j].y;
      }
    }
  }

  xObjCenter = (xMax + xMin)/2;
  yObjCenter = (yMax + yMin)/2;
  dx = xCenter - xObjCenter;
  dy = yCenter - yObjCenter;

  matrixTransf = SetSftMatrix(dx, dy);
  for(i = 0; i < nObjects; i++){
    objs[i] = TransObj(objs[i], matrixTransf);
  }
}


ColorValues * HSV2RGB(ColorValues * hsv) {
  float r, g, b, h, s, v, f, p, q, t;
  ColorValues * rgb;
  int hi;
  
  h = hsv->red;
  s = hsv->green;
  v = hsv->blue; 
  
  rgb = (ColorValues *) malloc(sizeof(ColorValues));
  
  if (s==0) {
    rgb->red = v;
    rgb->green = v;
    rgb->blue = v;
    }
  else {
    hi = ((int)floor(h/60.0)) % 6;
    f = h/60.0 - hi;
    p = v*(1.0-s);
    q = v*(1.0-f*s);
    t = v*(1.0-(1.0-f)*s);
    if (hi==0) {
      rgb->red = v;
      rgb->green = t;
      rgb->blue = p;
      }
    if (hi==1) {
      rgb->red = q;
      rgb->green = v;
      rgb->blue = p;
      }
    if (hi==2) {
      rgb->red = p;
      rgb->green = v;
      rgb->blue = t;
      }
    if (hi==3) {
      rgb->red = p;
      rgb->green = q;
      rgb->blue = v;
      }
    if (hi==4) {
      rgb->red = t;
      rgb->green = p;
      rgb->blue = v;
      }
    if (hi==5) {
      rgb->red = v;
      rgb->green = p;
      rgb->blue = q;
      }       
    }
  
  return rgb;
  }

int Dump2X(bufferdevice * dev, palette * pal) {
  Display               * display;
  XImage                * ximage;
  Window                window;
  XEvent                an_event;
  GC                    gc;
  Visual                * visual;
  XGCValues             values;
  int                   m, n, screen, dplanes;
  int                   width, height, ret = 1;
  ColorValues           * cor;
  
  width = dev->MaxX;
  height = dev->MaxY; 

  if ((display = XOpenDisplay(NULL)) == NULL) ret = 0;
  else {  
    screen = DefaultScreen(display);
    dplanes = DisplayPlanes(display,screen);   
    visual = XDefaultVisual(display,screen);
  
    if (!(window=XCreateSimpleWindow(display,RootWindow(display,screen),0,0,width,height,1,BlackPixel(display,screen),WhitePixel(display,screen)))) ret = 0;
    else {
      XSelectInput(display, window, EventMask);
      XStoreName(display, window, "Monitor Virtual");
      gc = XCreateGC(display, window, 0, &values);
  
      XMapWindow(display,window);
      XSync(display,False);
  
      ximage = XCreateImage(display,visual,dplanes,ZPixmap,0,malloc(width*height*sizeof(int)),width,height,8,0);

      for(m=0;m<height;m++) {
        for(n=0;n<width;n++) {
          cor = GetColor(dev->buffer[m*width+n],pal);
          ximage -> data[(m*4)*width+n*4] = (char) round((cor->blue)*255);
          ximage -> data[(m*4)*width+n*4+1] = (char) round((cor->green)*255);
          ximage -> data[(m*4)*width+n*4+2] = (char) round((cor->red)*255);
          ximage -> data[(m*4)*width+n*4+3] = (char) 0;
          }
        }

      XPutImage(display,window,gc,ximage,0,0,0,0,width,height);

      /* Trata os eventos */
      while(1) {
      XNextEvent(display, &an_event);
      switch(an_event.type) {
	case Expose:
             	XPutImage(display,window,gc,ximage,0,0,0,0,width,height);
                break;
	/* outros eventos ... */
           }
        }

      }
    }
 
  return ret;
  }

