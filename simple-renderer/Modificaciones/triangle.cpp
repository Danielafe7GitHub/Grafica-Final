#include "triangle.h"
//Compilar : make 
//Ejecutar // ./raylite
// No incluir using namespace std; ->> std::

/*Definiendo las Regiones*/
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
 
/*Definiendo los límites de la Ventana*/
const int x_max = 600;
const int y_max = 398;
const int x_min = 0;
const int y_min = 0;
  
// constructor
triangle::triangle(matrix<4, 4>& __t, material &__material, vector<3> __v1, vector<3> __v2,
        vector<3> __v3) :
        object(__t, __material) {
    // initialize vertices
    _v1 = __v1;
    _v2 = __v2;
    _v3 = __v3;
}

/*Algoritmo: Ordenar Aristas*/
bool ordenVector (int i,int j) { return (i<j); }

/*Algoritmo: Asignar Códigos a los Vértices: TBRL*/
int computeCode(double x, double y) 
{
    int code = INSIDE; 
    if (x < x_min)       // a la izquierda del rectángulo
        code |= LEFT;
    else if (x > x_max)  // a la derecha del rectángulo
        code |= RIGHT;
    if (y < y_min)       // debajo del rectángulo
        code |= BOTTOM;
    else if (y > y_max)  // encima del rectángulo
        code |= TOP;
 
    return code;
}

/*Algoritmo: Cohen-Sutherland --> Retorna el Punto after clipping*/
void cohenSutherlandClip(double x1, double y1,double x2, double y2)
{
    // Calculamos los códigos de P1, P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
 
    // Al prncipio, la línea no es aceptada
    bool accept = false;
 
    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            // Si ambos cógidos son 0000: Completamente adentro
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            // Si al hacer AND es distinto de 0000: Completamente afuera
            break;
        }
        else
        {
            // Si al hacer AND es 0000: Parcialmente adentro
            int code_out;
            double x, y;
 
            // Al menos un punto final está fuera del rectángulo, lo escogemos
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;
 
            // Encontramos la intersección del punto con la región TBRL;
            // Fórmulas y = y1 + slope * (x - x1), x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP)
            {
                // el punto está sobre el rectángulo 
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                // el punto está debajo el rectángulo
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                // el punto está a la derecha del rectángulo
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                // el punto está a la izquierda del rectángulo
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }
 
            // Reemplazamos el punto afuera del rectángulo por el punto de intersección
            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept)
    {
      std::cout <<"Line accepted from " << x1 << ", "
             << y1 << " to "<< x2 << ", " << y2 << std::endl;
    }
    else
    std::cout << "Line rejected" << std::endl;
}

/*Algoritmo: Bresenham*/
void triangle::bresenham_line(vector<2> __pv1, vector<2> __pv2,unsigned int __w, unsigned int __h, float*& __color_buffer)
{
    int x0 = __pv1[0]; int y0 = __pv1[1];
    int x1 = __pv2[0]; int y1 = __pv2[1];
    vector<2> __punto;
    
    int x; int y; int dx; int dy; int p; int incE; int incNE; int stepx; int stepy;
    dx = (x1 - x0);
    dy = (y1 - y0);

    if (dy < 0)
    { 
        dy = -dy; stepy = -1; 
    } 
    else stepy = 1;
    if (dx < 0)
    {
        dx = -dx; stepx = -1; 
    } 
    else stepx = 1;

    x = x0;
    y = y0;

    __punto[0] = x; __punto[1] = y;
    draw_point(__punto, __w, __h, __color_buffer); 

    /*Pendiente menor que 1*/
    if(dx>dy)
    {
        p = 2*dy - dx;
        incE = 2*dy;
        incNE = 2*(dy-dx);
        while (x != x1)
        {
          x = x + stepx;
          if (p <= 0)
          {
            p = p + incE;
          }
          else
          {
            y = y + stepy;
            p = p + incNE;
          }
          __punto[0] = x; __punto[1] = y;
          draw_point(__punto, __w, __h, __color_buffer); 
        }
      }
      /*Pendiente mayor e igual que 1*/
      else
      {
        p = 2*dx - dy;
        incE = 2*dx;
        incNE = 2*(dx-dy);
        while (y != y1)
        {
          y = y + stepy;
          if (p < 0)
          {
            p = p + incE;
          }
          else
          {
            x = x + stepx;
            p = p + incNE;
          }
          __punto[0] = x; __punto[1] = y;
          draw_point(__punto, __w, __h, __color_buffer); 
        }
      }

}
/*Algoritmo: Scanline*/
void triangle::scanLine(std::vector<std::pair <vector<2>,vector<2> >> aristas,unsigned int __w, unsigned int __h, float*& __color_buffer)
{
  //Eliminar Aristas Horizontales + PtomayorPtoMenor
  


  //Scan
  std::map <float,std::vector<int>,std::greater<int>> scan;
  bool add;
  vector<2> ptoInferior,ptoInferior2;  
  for(int i=0;i< aristas.size();i++)
  {      
      ptoInferior = aristas[i].first;         //Recorremos los PtosInferiores de las Aristas 
      for(int j=0;j<aristas.size();j++)
      {
          add = true;
          ptoInferior2 = aristas[j].first;
          if(ptoInferior2[1] == ptoInferior[1])
          {
              for (auto& x: scan) //Evitamos que coloque la misma arista 2 veces
              {
                  for(int k=0;k<x.second.size();k++)
                  {
                      if(j == x.second[k])
                      {
                        add = false; 
                        break;                  
                      } 
                  }

              }
              if(add) scan[ptoInferior[1]].push_back(j);                
          }
          
      }

  }

   /* std::cout<<"Scan: "<<std::endl;
    for (auto& x: scan) {
      std::cout << x.first << ": " ;        
        for(int i=0;i<x.second.size();i++)
        {
          std::cout <<x.second[i]<<" , ";
            
        }
        std::cout<<std::endl;
      }*/
  //EdgeTable
  std::vector<std::vector<float>> edgeTable; 
  std::vector<float> infoArista;
  for(int i=0;i<aristas.size();i++)
  {
    infoArista.push_back(i); //Indice de la Arista
    infoArista.push_back(aristas[i].first[0]); //primX
    infoArista.push_back(aristas[i].second[1]); //maxY 
    infoArista.push_back(aristas[i].second[0] - aristas[i].first[0]); //dx = ptosupe -ptoinfe
    infoArista.push_back(aristas[i].second[1] - aristas[i].first[1]); //dy = ptosupe -ptoinfe
    edgeTable.push_back(infoArista);
    infoArista.clear();
  }

  /*std::cout<<"Active Edge Table:"<<std::endl;         
  for(int i=0;i<edgeTable.size();i++)
  {
    std::cout<<"e"<<i+1<<" : "<<"primX: "<<edgeTable[i][1]<<"  maxY: "<<edgeTable[i][2]<<" dx: "<<edgeTable[i][3]<<" dy: "<<edgeTable[i][4]<<std::endl;
  }*/
  //Active Edge Table
  std::map <float,std::vector<int>,std::greater<int>>::iterator it = scan.begin();
  std::map <float,std::vector<int>,std::greater<int>>::iterator hasKey; 
  float t = it->first;
  vector<2> __pv1,__pv2;
  std::vector<std::vector<float>> edges;
  do
  {
    //Sacamos las Aristas de Scan con [t]
    hasKey = scan.find(t);
    if(hasKey != scan.end())
    {
      for(int i=0;i<scan.at(t).size();i++)
      {
        edges.push_back(edgeTable[scan.at(t)[i]]);
      }
    }
    
    //std::cout<<"T: "<<t<<std::endl;  
    //Ordenamos las Aristas por primX
    std::sort(edges.begin(), edges.end(),
    [](const std::vector<float>& a, const std::vector<float>& b) {
    return a[1] < b[1];
    });
    
    /*std::cout<<"Active Edge Table:"<<std::endl;         
    for(int i=0;i<edges.size();i++)
    {
      std::cout<<"e"<<i+1<<" : "<<"primX: "<<edges[i][1]<<"  maxY: "<<edges[i][2]<<" dx: "<<edges[i][3]<<" dy: "<<edges[i][4]<<std::endl;
    }*/
    //Pintamos las Aristas que tenemos, en todo poligono de dos en dos
    for(int i=0;i<=edges.size()-2;i+=2)
    {
      __pv1[0] = edges[i][1];   __pv1[1] = t;
      __pv2[0] = edges[i+1][1]; __pv2[1] = t;
      //std::cout<<"Se pinta de: "<<__pv1[0]<<" a: "<<__pv2[0]<<std::endl;
      //int a; std::cin>>a;
      bresenham_line(__pv1,__pv2,__w,__h,__color_buffer); //  __pv1 y __pv2
    }

    //Eliminamos
    int j = 0;
    bool continues = true;
    while(j<edges.size())
    {
      if((int)edges[j][2] == (int)t)
      {    
        //std::cout<<"Arista Ymax: "<<edges[j][2]<<"   t: "<<t<<std::endl;
        //int a; std::cin>>a;
        edges.erase(edges.begin()+j);
        continues = false;        
      }
      if(continues)j++;
      else 
      {
        continues = true;
        j = 0;
      }
    }
  
    //Para areglar: entran tres aristas: ver como pintas, no se elimina
    //Actualizamos Valores
    for(int i=0;i<edges.size();i++)
    {
      float primX = edges[i][1] - (edges[i][3]/edges[i][4]);
      edges[i][1] = primX;
    }
    t--;
  }
  while(edges.size()>0);
  
}



// rasterize
bool triangle::rasterize(camera* __camera, unsigned short __w, unsigned short __h,
        vector<3> __ambient, dlight *__dlights, unsigned long __num_dlights, plight *__plights,
        unsigned long __num_plights, float*& __color_buffer, float*& __depth_buffer) {
    //<<TODO>> transform, lit, project, rasterize, calculate final color and depth

    // initialize color buffer
    __color_buffer = new float[__w * __h * 4];

    // initialize depth buffer
    __depth_buffer = new float[__w * __h];

    // model transform
    vector<4> __v1;
    __v1[0] = _v1[0];
    __v1[1] = _v1[1];
    __v1[2] = _v1[2];
    __v1[3] = 1.0;
    vector<4> __v2;
    __v2[0] = _v2[0];
    __v2[1] = _v2[1];
    __v2[2] = _v2[2];
    __v2[3] = 1.0;
    vector<4> __v3;
    __v3[0] = _v3[0];
    __v3[1] = _v3[1];
    __v3[2] = _v3[2];
    __v3[3] = 1.0;
    __v1 = _t * __v1;
    __v2 = _t * __v2;
    __v3 = _t * __v3;

    // world
    matrix<4, 4> __ww;
    __ww[0][0] = __camera->right()[0];
    __ww[1][0] = __camera->right()[1];
    __ww[2][0] = __camera->right()[2];
    __ww[0][1] = __camera->up()[0];
    __ww[1][1] = __camera->up()[1];
    __ww[2][1] = __camera->up()[2];
    __ww[0][2] = __camera->dir()[0];
    __ww[1][2] = __camera->dir()[1];
    __ww[2][2] = __camera->dir()[2];

    // world transform
    __v1 = __ww * (__v1 - __camera->pos());
    __v2 = __ww * (__v2 - __camera->pos());
    __v3 = __ww * (__v3 - __camera->pos());

    // orthogonal projection
    vector<2> __pv1;
    __pv1[0] = __v1[0];
    __pv1[1] = __v1[1];
    vector<2> __pv2;
    __pv2[0] = __v2[0];
    __pv2[1] = __v2[1];
    vector<2> __pv3;
    __pv3[0] = __v3[0];
    __pv3[1] = __v3[1];

    
   

    // simulating a frustrum
    __pv1[0] += 5.f;
    __pv1[0] *= __w / 10.f;
    __pv1[1] += 5.f;
    __pv1[1] *= __h / 10.f;
    __pv2[0] += 5.f;
    __pv2[0] *= __w / 10.f;
    __pv2[1] += 5.f;
    __pv2[1] *= __h / 10.f;
    __pv3[0] += 5.f;
    __pv3[0] *= __w / 10.f;
    __pv3[1] += 5.f;
    __pv3[1] *= __h / 10.f;

    //Poligono Ejemplo
    /*
    vector<2> __pv4,__pv5,__pv6;
    __pv1[0] = 100; __pv1[1]  = 300;
    __pv2[0] = 150; __pv2[1]  = 70;
    __pv3[0] = 300; __pv3[1]  = 150;
    __pv4[0] = 420; __pv4[1]  = 70;
    __pv5[0] = 480; __pv5[1]  = 200;
    __pv6[0] = 400; __pv6[1]  = 300;

    bresenham_line(__pv1,__pv2,__w,__h,__color_buffer);
    bresenham_line(__pv2,__pv3,__w,__h,__color_buffer);
    bresenham_line(__pv3,__pv4,__w,__h,__color_buffer);
    bresenham_line(__pv4,__pv5,__w,__h,__color_buffer);
    bresenham_line(__pv5,__pv6,__w,__h,__color_buffer);
    bresenham_line(__pv1,__pv6,__w,__h,__color_buffer);
    std::pair<vector<2>,vector<2>> e1,e2,e3,e4,e5,e6;
    e1 = std::make_pair(__pv1,__pv2);
    e2 = std::make_pair(__pv3,__pv2);
    e3 = std::make_pair(__pv3,__pv4);
    e4 = std::make_pair(__pv5,__pv4);
    e5 = std::make_pair(__pv6,__pv5);
    e6 = std::make_pair(__pv1,__pv6);
    std::vector<std::pair < vector<2>,vector<2> >> aristas;
    aristas.push_back(e1);aristas.push_back(e2);aristas.push_back(e3);aristas.push_back(e4);aristas.push_back(e5);//aristas.push_back(e6);
    scanLine(aristas,__w, __h, __color_buffer);*/

    /*__pv1[0] = 600; __pv1[1]  = 398;
    __pv2[0] = 0; __pv2[1]  = 398;
    __pv3[0] = 300; __pv3[1]  = 0;
    std::cout<<"Probando L1: "<<std::endl;
    cohenSutherlandClip(-5,370,-5,15);
    std::cout<<"Probando L2: "<<std::endl;
    cohenSutherlandClip(-5,370,30,30);
    std::cout<<"Probando L3: "<<std::endl;
    cohenSutherlandClip(30,30,-5,15);*/

    std::cout<<"******************************************* "<<std::endl;
    std::cout<<"Ptos: "<<__pv1[0]<<" "<<__pv1[1]<<std::endl;
    std::cout<<"Ptos: "<<__pv2[0]<<" "<<__pv2[1]<<std::endl;
    std::cout<<"Ptos: "<<__pv3[0]<<" "<<__pv3[1]<<std::endl;

    bresenham_line(__pv1,__pv2,__w,__h,__color_buffer); //  __pv1 y __pv2
    bresenham_line(__pv1,__pv3,__w,__h,__color_buffer); //  __pv1 y __pv3
    bresenham_line(__pv2,__pv3,__w,__h,__color_buffer); //  __pv2 y __pv3

    //Armamos las Aristas, ptoInferio, pto Superios ; ptoInfer : pto con coorY mayor
    std::pair<vector<2>,vector<2>> e1,e2,e3;
    if(__pv2[1] > __pv1[1]) e1 = std::make_pair(__pv2,__pv1);
    else e1 = std::make_pair(__pv1,__pv2); 
    if(__pv3[1] > __pv1[1]) e2 = std::make_pair(__pv3,__pv1);
    else e2 = std::make_pair(__pv1,__pv3);
    if(__pv3[1] > __pv2[1]) e3 = std::make_pair(__pv3,__pv2);
    else e3 = std::make_pair(__pv2,__pv3);

    std::vector<std::pair < vector<2>,vector<2> >> aristas;
    aristas.push_back(e1);aristas.push_back(e2);aristas.push_back(e3);
    scanLine(aristas,__w, __h, __color_buffer);
    // everything is alright
    return true;
}

void triangle::draw_point(vector<2> p, unsigned int __w, unsigned int __h, float*& __color_buffer) {
    int __x = p[0];
    int __y = p[1];
    __color_buffer[(__y * __w + __x) * 4 + 0] = _material._color[0];
    __color_buffer[(__y * __w + __x) * 4 + 1] = _material._color[1];
    __color_buffer[(__y * __w + __x) * 4 + 2] = _material._color[2];
    __color_buffer[(__y * __w + __x) * 4 + 3] = _material._color[3];
}

