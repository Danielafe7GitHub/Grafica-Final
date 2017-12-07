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
const int y_max = 399;
const int x_min = 1;
const int y_min = 1;
  
/*Se almacenan los Puntos del Triángulo/Polígono after Clipping*/
std::vector<vector<2>> polygonoPoitns; 
std::vector<vector<2>> afterClipping;  // Coordenadas puede usar este vector (contiene los nuevos ptos after Clipping)

/*Definiendo variables para colores After Interpolación*/
vector<3> c1,c2,c3; 
float alpha,theta,gammas,_r,_g,_b;

// constructor
triangle::triangle(matrix<4, 4>& __t, material &__material, vector<3> __v1, vector<3> __v2,
        vector<3> __v3) :
        object(__t, __material) {
    // initialize vertices
    _v1 = __v1;
    _v2 = __v2;
    _v3 = __v3;
}


/*Algoritmo: Asignar Códigos a los Vértices: TBRL*/
int triangle::calcularZona(double x, double y) 
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
void triangle::cohenSutherlandClip(double x1, double y1,double x2, double y2,unsigned int __w, unsigned int __h, float*& __color_buffer,std::vector<vector<2>>vertices)
{
    // Calculamos los códigos de P1, P2
    int code1 = calcularZona(x1, y1);
    int code2 = calcularZona(x2, y2);
 
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
                code1 = calcularZona(x1, y1); // Realizamos el procedimiento hasta que ambosp puntos esten en estado :0000 (completamente a dentro)
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = calcularZona(x2, y2);
            }
        }
    }
    if (accept)
    {
      // Si la línea es aceptada, se añade al vector polygonoPoints para realizar el cálculo del nuevo Polígono
      vector<2>__pv1,__pv2;
      __pv1[0] = x1; __pv1[1] = y1; __pv2[0] = x2; __pv2[1] = y2;
      polygonoPoitns.push_back(__pv1);  polygonoPoitns.push_back(__pv2); // Nuevos Puntos After Clipping
      //bresenham_line(__pv1,__pv2,__w,__h,__color_buffer,vertices,luz);

    }
    /*else
        std::cout << "Line rejected" << std::endl; // Ya no se dibuja esa línea*/
}

/*Algoritmo: Bresenham*/
void triangle::bresenham_line(vector<2> __pv1, vector<2> __pv2,unsigned int __w, unsigned int __h, float*& __color_buffer,std::vector<vector<2>>vertices,std::vector<vector<3>> luz)
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
    coorBaricentrias(x,y,vertices,0,luz);
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
          coorBaricentrias(x,y,vertices,0,luz);
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
          coorBaricentrias(x,y,vertices,0,luz);
          draw_point(__punto, __w, __h, __color_buffer); 
        }
      }

}

/*Algortimos: Scanline Odd-Even*/
void triangle::odd_even(int numVertices, int dimension, std::vector<vector<2>> puntos,unsigned int __w, unsigned int __h, float*& __color_buffer,std::vector<vector<2>>vertices,std::vector<vector<3>> luz)
{
    int a [numVertices+1][dimension]; // two dimensional array to store the polyg on vertices. 
    float b [numVertices][4]; // two dimensional array to store the Edges-Table. 
    float slope [numVertices]; // one dimensional array to store the slop. 

    // Metemos nuestos vertices en una Tabla de vertices : Ojo coloca los vertices en Orden
    for (int row=0; row<numVertices;row++) 
    { 
        for (int col=0; col< dimension; col++) 
        {
            a[row][col] = puntos[row][col];
        }
       
    }
    // Añadimos el primer vertice a la última posicion: 
    a[numVertices][0] = puntos[0][0];
    a[numVertices][1] = puntos[0][1];

    /*for(int i=0;i<numVertices+1;i++)
    {
        std::cout<<a[i][0]<<"   "<<a[i][1]<<std::endl;
    }*/
    // Armamos Edge Table : Value y-max
    for(int i=0;i<numVertices;i++)
    {
        if (a[i][1] > a[i+1][1]){ 
            b[i][1] = a[i][1];} 
        else 
            b[i][1] = a[i+1][1];
    }

    // Armamos Edge Table : Value y-min && Value Prim x
    for(int i=0;i<numVertices;i++)
    {
        if (a[i][1] < a[i+1][1])
        {                    
            b[i][2]=a[i][0]; 
            b[i][0] = a[i][1];
        } 
        else
        { 
            b[i][2]=a[i+1][0]; 
            b[i][0] = a[i+1][1];
        } 
    }  
  
        
    // Armamos Edge Table : Value  slope: 1/m=(x2-x1) / (y2-y1)
    for(int i=0;i<numVertices;i++)
    {
        int dy=a[i+1][1]-a[i][1]; 
        int dx=a[i+1][0]-a[i][0];
        slope[i]=   ((float)dx/(float)dy); // inversa de la pendiente
        b[i][3] = slope[i];
    }  

     // Imprimiendo Edge Table
     /*std::cout<<"************Origin Edge Table*****************************************"<<std::endl;
     for(int i=0;i<numVertices;i++)
     {
         std::cout<<b[i][0]<<"   "<<b[i][1]<<"   "<<b[i][2]<<"   "<<b[i][3]<<std::endl;
     }*/
     
    //  Edge table, pasamos todo a un vector
    std::vector<std::vector<float>> eTable; 
    std::vector<float> aux;   
    for(int i=0; i<numVertices;i++)
    {
        aux.push_back(b[i][0]);
        aux.push_back(b[i][1]);
        aux.push_back(b[i][2]);
        aux.push_back(b[i][3]);
        eTable.push_back(aux);
        aux.clear();
    }
   
    /*std::cout<<"************New Vector Edge Table*****************************************"<<std::endl;
    for(int i=0;i<eTable.size();i++)
    {
        std::cout<<eTable[i][0]<<"   "<<eTable[i][1]<<"   "<<eTable[i][2]<<"    "<<eTable[i][3]<<std::endl;
    }*/
    // Ordenamos Edge Tablde de Y-min 
    float swap,swapsl;
    for (int c = 0; c < ( eTable.size() - 1 ); c++)
    { 
        for (int d = 0; d < (eTable.size() - c - 1); d++)
        { 
          if (((eTable[d][0]> eTable[d+1][0])||(eTable[d][1]>eTable[d+1][1] ))|| ((eTable[d][0]==eTable[d+1][0])&&(eTable[d][2]> eTable[d+1][2])  )) 
          { 
            swap = eTable[d][0]; 
            eTable[d][0] = eTable[d+1][0]; 
            eTable[d+1][0] = swap; 
            swap = eTable[d][1]; 
            eTable[d][1] = eTable[d+1][1]; 
            eTable[d+1][1] = swap; 
            swap = eTable[d][2]; 
            eTable[d][2] = eTable[d+1][2]; 
            eTable[d+1][2] = swap; 
            swapsl= slope[d]; 
            slope[d]=slope[d+1]; 
            slope[d+1]=swapsl;  
          } 
        }
    } 

    // Asignamos nuevas inversas en orden 
    for(int i=0;i<eTable.size();i++)
        eTable[i][3] = slope[i];

    //Eliminamos Aristas con m=0
    std::vector<std::vector<float>> eTableAux;
    aux.clear();
    for(int i=0; i<eTable.size();i++)
    {
        if(eTable[i][0] != eTable[i][1])
        //if(b[i][4] != 0)
        {
            aux.push_back(eTable[i][0]);
            aux.push_back(eTable[i][1]);
            aux.push_back(eTable[i][2]);
            aux.push_back(eTable[i][3]);
            eTableAux.push_back(aux);
            aux.clear();
        }
    }
    eTable = eTableAux;
    eTableAux.clear();
   
    //std::vector<std::vector<float>> eTable;
    /*for(int i=0;i<numVertices;i++)
    {
        aux.push_back(edgeTable[i][0]);aux.push_back(edgeTable[i][1]);aux.push_back(edgeTable[i][2]);aux.push_back(edgeTable[i][3]);
        eTable.push_back(aux);
        aux.clear();
    }*/

     // Imprimiendo Edge Table
     /*std::cout<<"************Edge Table non-M && Order by Min_Y*****************************************"<<std::endl;
     for(int i=0;i<eTable.size();i++)
     {
         std::cout<<eTable[i][0]<<"   "<<eTable[i][1]<<"   "<<eTable[i][2]<<"   "<<eTable[i][3]<<std::endl;
     }*/
     
    // Generando Active Table
    std::vector<std::vector<float>> cc;
    std::vector<std::vector<float>> ccAux;
    std::vector<std::vector<float>> drwline;
    

    int scaline = eTable[0][0]; /*this represents the first scan-line (the minimum value of y)*/
    //while(eTable.size()>0)  //Fix >=0?? o solo >
    if(scaline > 0)
    {
        do
        {
            //std::cout<<"---------------------------------------------------------->Scanline "<<scaline<<std::endl;
            // Creando Active Table
            for (int ii =0; ii<eTable.size(); ii++)
            { 
               if(eTable[ii][0] == scaline) 
               { 
                  aux.push_back(eTable[ii][1]); 
                  aux.push_back(eTable[ii][2]); 
                  aux.push_back(eTable[ii][3]); 
                  cc.push_back(aux);
                  aux.clear();
               } 
               else
               {
                aux.push_back(eTable[ii][0]); 
                aux.push_back(eTable[ii][1]); 
                aux.push_back(eTable[ii][2]); 
                aux.push_back(eTable[ii][3]); 
                eTableAux.push_back(aux);
                aux.clear();
    
               }
            } 
            
            // Re ordena Active Table                 
            for (int i=0; i< cc.size() -1 ; i++){ 
                if (cc[i][1] > cc[i+1][1])
                { 
                    float swap=cc[i][0]; 
                    cc[i][0]=cc[i+1][0]; 
                    cc[i+1][0]=swap; 
                    swap=cc[i][1]; 
                    cc[i][1]=cc[i+1][1]; 
                    cc[i+1][1]=swap; 
                    swap=cc[i][2]; 
                    cc[i][2]=cc[i+1][2]; 
                    cc[i+1][2]=swap; 
                    }
            }   
    
            // Se actualiza Edge Table
            eTable = eTableAux;
            eTableAux.clear();
            // Imprimiendo Edge Table (Lo que queda)
            /*std::cout<<"************Global Edge Table*****************************************"<<std::endl;
            for(int i=0;i<eTable.size();i++)
            {
                std::cout<<eTable[i][0]<<"   "<<eTable[i][1]<<"   "<<eTable[i][2]<<"   "<<eTable[i][3]<<std::endl;
            }*/
    
            // Imprimiendo Active Table
            /*std::cout<<"****************Active Table*************************************"<<std::endl;
            for(int i=0;i< cc.size();i++)
            {
                std::cout<<cc[i][0]<<"    "<<cc[i][1]<<"  "<<cc[i][2]<<std::endl;
            }*/
    
            // Añade Tabla de Dibujo
            int min_y = scaline;
            int max_y = cc[0][0];
            for(int i = 0;i<cc.size();i++)
            {
                if(cc[i][0]<max_y)
                    max_y = cc[i][0];
            }
            for (int scan=min_y; scan<max_y; scan++){ 
                if (cc[0][0]!=scan){ 
                    for (int i=0;i<cc.size();i+=2)
                    { 
                        aux.push_back(cc[i][1]);   
                        aux.push_back(scan);                  
                        aux.push_back(cc[i+1][1]);      
                        aux.push_back(scan); 
                        drwline.push_back(aux);                  
                        aux.clear();
                    }
                }
            // Actualiza Active Table
            for (int i=0;i<cc.size();i++)
                cc[i][1]=cc[i][1]+cc[i][2]; 
                        
            // Re ordena Active Table                 
            for (int i=0; i< cc.size() -1 ; i++){ 
                if (cc[i][1] > cc[i+1][1])
                { 
                    float swap=cc[i][0]; 
                    cc[i][0]=cc[i+1][0]; 
                    cc[i+1][0]=swap; 
                    swap=cc[i][1]; 
                    cc[i][1]=cc[i+1][1]; 
                    cc[i+1][1]=swap; 
                    swap=cc[i][2]; 
                    cc[i][2]=cc[i+1][2]; 
                    cc[i+1][2]=swap; 
                    }
                }            
            }      
    
            // Acabó scanline [i] --> Elimina los que no van 
            for(int i=0;i< cc.size();i++)
            {
                if(cc[i][0] != max_y)
                {
                    ccAux.push_back(cc[i]);
                }
                    
            }
            cc = ccAux;
            ccAux.clear();
    
            // Imprimiendo Draw Table
            /*std::cout<<"*********************Draw Table********************************"<<std::endl;
            for(int i=0;i< drwline.size();i++)
            {
                std::cout<<drwline[i][0]<<"    "<<drwline[i][1]<<"  "<<drwline[i][2]<<"   "<<drwline[i][3]<<std::endl;
            }*/            
    
            // Imprimiendo Update Active Table 
            /*std::cout<<"*********************Update Active Table********************************"<<std::endl;
            for(int i=0;i< cc.size();i++)
            {
                std::cout<<cc[i][0]<<"    "<<cc[i][1]<<"  "<<cc[i][2]<<std::endl;
            }*/ 
            scaline = max_y;
    
    
        }
        while(cc.size()>0);
    

    }
    
    
    //Teniendo los Puntos , a dibujar!
    vector<2> __pv1,__pv2;
    for(int i=0;i<drwline.size();i++)
    {
        __pv1[0] = drwline[i][0];
        __pv1[1] = drwline[i][1];
        __pv2[0] = drwline[i][2];
        __pv2[1] = drwline[i][3];
        bresenham_line(__pv1,__pv2,__w,__h,__color_buffer,vertices,luz);
    }
   
     

   
}

float formula(float x, float y, vector<2>pa, vector<2>pb)
{
  return (pa[1] - pb[1]) * x + (pb[0] - pa[0]) * y + pa[0]*pb[1] - pb[0]*pa[1];
}

/*Algortimos: Coordenadas Baricéntricas*/
void triangle::coorBaricentrias(float x, float y,std::vector<vector<2>>vertices, bool flag,std::vector<vector<3>> luz)
{
    // p1, p2, p3 Los tres vértives 'ORIGINALES' del triángulo
    vector<2>p1 = vertices[0]; vector<2>p2 = vertices[1]; vector<2>p3 = vertices[2];
    
    // Con el flag revisa si es Interpolación de color o Iluminación.
    if(flag)
    {
        c1[0] = 1.0; c1[1] = 0.0; c1[2] = 0.0;  // Rojo
        c2[0] = 0.0; c2[1] = 1.0; c2[2] = 0.0;  // Verde
        c3[0] = 0.0; c3[1] = 0.0; c3[2] = 1.0;  // Azul
    }
    else
    {
        // Aquí ya no tenemos el color de vértice, sino la iluminación calculada en cada uno
        c1[0] = luz[0][0]; c1[1] = luz[0][1]; c1[2] = luz[0][2];  // Luz V1
        c2[0] = luz[1][0]; c2[1] = luz[1][1]; c2[2] = luz[1][2];  // Luz V2
        c3[0] = luz[2][0]; c3[1] = luz[2][1]; c3[2] = luz[2][2];  // Luz V3
    }
    

    alpha =  formula(x, y, p2, p3) / formula(p1[0], p1[1], p2, p3);
    theta =  formula(x, y, p3, p1) / formula(p2[0], p2[1], p3, p1);
    gammas = formula(x, y, p1, p2) / formula(p3[0], p3[1], p1, p2);
    _r = c1[0] * alpha + c2[0] * theta +  c3[0] * gammas;
    _g = c1[1] * alpha + c2[1] * theta +  c3[1] * gammas;
    _b = c1[2] * alpha + c2[2] * theta +  c3[2] * gammas;

     // Actualizando colores
    _material._color[0] = _r;
    _material._color[1] = _g;
    _material._color[2] = _b;
   
}








/*Algoritmo: Vector Dirección*/
vector<3> triangle::direccion(vector<3>pto1,vector<3>pto2 )
{
    //Coloca como pto1, a quien quieres apuntar
    vector<3> vecDir; vecDir[0] = pto1[0] - pto2[0]; vecDir[1] = pto1[1] - pto2[1]; vecDir[2] = pto1[2] - pto2[2];
    return normalizar(vecDir);
}
/*Algoritmo: Normalizar un Vector*/
vector<3> triangle::normalizar(vector<3>_vector)
{
    float square = sqrt((_vector[0]*_vector[0]) + (_vector[1]*_vector[1]) + (_vector[2]*_vector[2]));
    vector<3> normalized; normalized[0] = (_vector[0] / square); normalized[1] =(_vector[1] / square); normalized[2] = (_vector[2] / square);
    return normalized;
}

/*Algoritmo: Normal Triángulos*/
vector<3> triangle::normalTriangulo(vector<3>v1,vector<3>v2,vector<3>v3)
{
   
    vector<3>vector1 = v1 - v3;  // Cambio
    vector<3>vector2 = v2 - v3;
    vector<3>normal; normal[0] = vector1[1]*vector2[2] - vector2[1]*vector1[2];  normal[1] =vector1[2]*vector2[0] - vector2[2]*vector1[0];  normal[2] = vector1[0]*vector2[1] - vector2[0]*vector1[1]; //    normal = (y1*z2 - y2*z1 , z1*x2 - z2*x1 , x1*y2 - x2*y1)
    vector<3> n = normalizar(normal);
    return n;
}

/*Algoritmo: Reflection Vector*/
vector<3> triangle::reflection(vector<3>n,vector<3>l )
{
    float escalar = (n[0]*l[0] + n[1]*l[1] + n[2]*l[2]) * 2; //Produncto punto de n * l = escalar    
    vector<3> r ; r[0] = escalar * (n[0] - l[0]); r[1] = escalar * (n[1] - l[1]); r[2] = escalar * (n[2] - l[2]);
    return r;
}


/*Algoritmo: Ambient Light*/
vector<3> triangle::ambientL()
{
    vector<3> ka; ka[0] = 0.7;  ka[1] = 0.7; ka[2] = 0.7;// coefficient of ambient reflection entre 0 y 1
    vector<3> la; la[0] = 0.0;  la[1] = 0.0; la[2] = 0.3; // light component consists of 3 color components
    vector<3> Ia; Ia[0] = ka[0] * la[0];  Ia[1] = ka[1] * la[1]; Ia[2] = ka[2] * la[2];
    return Ia;
}


/*Algoritmo: Diffuse Light*/
vector<3> triangle::diffueseL(vector<3>n,vector<3>l)
{
    vector<3> kd; kd[0] = 0.8;  kd[1] = 0.5; kd[2] = 0.9; // coefficient of ambient reflection entre 0 y 1
    vector<3> ld; ld[0] = 6.5;  ld[1] = 6.5; ld[2] = 6.0; // light component consists of 3 color components
    float escalar = (n[0]*l[0] + n[1]*l[1] + n[2]*l[2]); //Produncto punto de n * l = escalar
    if(escalar < 0) escalar = 0;
    vector<3> Id; Id[0] = kd[0] * ld[0] * escalar;  Id[1] = kd[1] * ld[1] * escalar; Id[2] = kd[2] * ld[2] * escalar;
    return Id;
}

/*Algoritmo: Specular Light*/
vector<3> triangle::specularL(vector<3>r,vector<3>v)
{
    int shinniness = 45;
    vector<3> ks; ks[0] = 0.2;  ks[1] = 0.5; ks[2] = 0.6; // coefficient of ambient reflection entre 0 y 1
    vector<3> ls; ls[0] = 0.0;  ls[1] = 0.0; ls[2] = 6.6; // light component consists of 3 color components
    float escalar = (r[0]*v[0] + r[1]*v[1] + r[2]*v[2]); //Produncto punto de r * v = (escalar) ^ shinniness 
    escalar = pow(escalar,shinniness);
    vector<3> Is; Is[0] = ks[0] * ls[0] * escalar;  Is[1] = ks[1] * ls[1] * escalar; Is[2] = ks[2] * ls[2] * escalar;
    return Is;
}


/*Algortimos: Iluminación - input: vertices Originales para hallar su normal */
std::vector<vector<3>> triangle::iluminacion(std::vector<vector<2>>vertices)
{
    std::vector<vector<3>> coefIlumuniacion;
    vector<3> coeficientes;
    /*Calculando Iluminación para el V1*/

    // Calculamos la Intensidad de Ambiente
    vector<3> ambiente = ambientL();

    // Calculamos la Intensidad Difusa
    vector<3> l; l[0] = 0; l[1] = 0; l[2] = 35;
    vector<3> v; v[0] = 0; v[1] = 0; v[2] = 60;
 
    vector<3> vertices1; vertices1[0] = vertices[0][0]; vertices1[1] = vertices[0][1]; vertices1[2] = 1; 
    vector<3> vertices2; vertices2[0] = vertices[1][0]; vertices2[1] = vertices[1][1]; vertices2[2] = 1;
    vector<3> vertices3; vertices3[0] = vertices[2][0]; vertices3[1] = vertices[2][1]; vertices3[2] = 1;

    vector<3> pto; pto[0] = vertices1[0]; pto[1] = vertices1[1]; pto[2] = vertices1[2]; 

    vector<3> normal = normalTriangulo(vertices1,vertices2,vertices3);
    vector<3> light = direccion(l,pto);
    vector<3> difuso = diffueseL(normal,light);

    // Calculamos la Intensidad Especular
    vector<3> reflexion = reflection(normal,light);
    vector<3> view = direccion(view,pto);
    vector<3> specular = specularL(reflexion,view);

    // Calculamos la suma de Ia + Id + Is

    _r = ambiente[0] + difuso[0] + specular[0];
    _g = ambiente[1] + difuso[1] + specular[1];
    _b = ambiente[2] + difuso[2] + specular[2];

    coeficientes[0] = _r; coeficientes[1] = _g; coeficientes[2] = _b;  coefIlumuniacion.push_back(coeficientes);


    /*Calculando Iluminación para el V2*/
    pto[0] = vertices2[0]; pto[1] = vertices2[1]; pto[2] = vertices2[2];
    // Calculamos la Intensidad Difusa
    light = direccion(l,pto);
    difuso = diffueseL(normal,light);

    // Calculamos la Intensidad Especular
    reflexion = reflection(normal,light);
    view = direccion(view,pto);
    specular = specularL(reflexion,view);

    // Calculamos la suma de Ia + Id + Is

    _r = ambiente[0] + difuso[0] + specular[0];
    _g = ambiente[1] + difuso[1] + specular[1];
    _b = ambiente[2] + difuso[2] + specular[2];

    coeficientes[0] = _r; coeficientes[1] = _g; coeficientes[2] = _b;  coefIlumuniacion.push_back(coeficientes);


    /*Calculando Iluminación para el V3*/
    pto[0] = vertices3[0]; pto[1] = vertices3[1]; pto[2] = vertices3[2];
    // Calculamos la Intensidad Difusa
    light = direccion(l,pto);
    difuso = diffueseL(normal,light);

    // Calculamos la Intensidad Especular
    reflexion = reflection(normal,light);
    view = direccion(view,pto);
    specular = specularL(reflexion,view);

    // Calculamos la suma de Ia + Id + Is

    _r = ambiente[0] + difuso[0] + specular[0];
    _g = ambiente[1] + difuso[1] + specular[1];
    _b = ambiente[2] + difuso[2] + specular[2];

    coeficientes[0] = _r; coeficientes[1] = _g; coeficientes[2] = _b;  coefIlumuniacion.push_back(coeficientes);

    return coefIlumuniacion;
}



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

    // view transform
    __v1 = __ww * (__v1 - __camera->pos());
    __v2 = __ww * (__v2 - __camera->pos());
    __v3 = __ww * (__v3 - __camera->pos());

    // perspective matriz

    float ar = __w / __h;
    float zNear = 10;
    float zFar = 1000;
    float zRange = zNear - zFar;
    float fov = 30;  // A más ángulo, + lejano se verá
    float pi =  3.14159265;
    float fovtoRadian =( fov * pi / 180.0 ); // Convertimos el angulo fov en radianes
    float tanHalfFOV = tanf(fovtoRadian / 2.0);
    matrix<4, 4> __pp;

    __pp[0][0] = 1.0f / (tanHalfFOV * ar);
    __pp[0][1] = 0.0f;
    __pp[0][2] = 0.0f;
    __pp[0][3] = 0.0f;

    __pp[1][0] = 0.0f;
    __pp[1][1] = 1.0f / tanHalfFOV;
    __pp[1][2] = 0.0f;
    __pp[1][3] = 0.0f;

    __pp[2][0] = 0.0f;
    __pp[2][1] = 0.0f;
    __pp[2][2] = (-zNear - zFar) / zRange;
    __pp[2][3] = 2.0f * zFar * zNear / zRange;

    __pp[3][0] = 0.0f;
    __pp[3][1] = 0.0f;
    __pp[3][2] = 1.0f;
    __pp[3][3] = 0.0f;


    // perspective transform
    vector<4> __pp1; vector<4> __pp2; vector<4> __pp3;
    __pp1 = __pp * (__v1);
    __pp2 = __pp * (__v2);
    __pp3 = __pp * (__v3);

    // de device coordinates a normal device coordinates
    __pp1[0] = __pp1[0] / __pp1[3]; // (x/w)...Normalizando x
    __pp1[1] = __pp1[1] / __pp1[3];
    __pp1[2] = __pp1[2] / __pp1[3];
    __pp1[3] = __pp1[3] / __pp1[3];


    __pp2[0] = __pp2[0] / __pp2[3]; 
    __pp2[1] = __pp2[1] / __pp2[3];
    __pp2[2] = __pp2[2] / __pp2[3];
    __pp2[3] = __pp2[3] / __pp2[3];


    __pp3[0] = __pp3[0] / __pp3[3]; 
    __pp3[1] = __pp3[1] / __pp3[3];
    __pp3[2] = __pp3[2] / __pp3[3];
    __pp3[3] = __pp3[3] / __pp3[3];


    // Escalamos los valores del cubo unitario
    vector<2> __pv1;
    __pv1[0] = __pp1[0];
    __pv1[1] = __pp1[1];
    vector<2> __pv2;
    __pv2[0] = __pp2[0];
    __pv2[1] = __pp2[1];
    vector<2> __pv3;
    __pv3[0] = __pp3[0];
    __pv3[1] = __pp3[1];

    __pv1[0] += 1.f;
    __pv1[0] *= __w / 2.f;
    __pv1[1] += 1.f;
    __pv1[1] *= __h / 2.f;
    __pv2[0] += 1.f;
    __pv2[0] *= __w / 2.f;
    __pv2[1] += 1.f;
    __pv2[1] *= __h / 2.f;
    __pv3[0] += 1.f;
    __pv3[0] *= __w / 2.f;
    __pv3[1] += 1.f;
    __pv3[1] *= __h / 2.f;







    // orthogonal projection
    /*vector<2> __pv1;
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
    __pv3[1] *= __h / 10.f;*/


    
    
    // Empezamos con el Rasterizado!!!
    std::vector<vector<2>> puntos;  // Conservamos los vértices Originales del Triángulo
    puntos.push_back(__pv1);
    puntos.push_back(__pv2);
    puntos.push_back(__pv3);
    
   // Obtenidos los vértices, hallamos la iluminación
   std::vector<vector<3>> luz = iluminacion(puntos);      

    // Realizamos algoritmo de Clipping
    cohenSutherlandClip(__pv1[0],__pv1[1],__pv2[0],__pv2[1],__w,__h,__color_buffer,puntos);
    cohenSutherlandClip(__pv1[0],__pv1[1],__pv3[0],__pv3[1],__w,__h,__color_buffer,puntos);
    cohenSutherlandClip(__pv2[0],__pv2[1],__pv3[0],__pv3[1],__w,__h,__color_buffer,puntos);

    // Recalculamos los puntos (almacenados en PolygonoPoints) After Clipping 
    afterClipping.push_back(polygonoPoitns[0]); 
    bool flag = 1;
    for(int i=1;i<polygonoPoitns.size();i++)
    {
        for(int j=0;j<afterClipping.size();j++)
        {
            // Evita que se agreque el mismo punto
            if(afterClipping[j][0] == polygonoPoitns[i][0] && afterClipping[j][1] == polygonoPoitns[i][1] )
                flag = 0;
        }
        if(flag == 1)
            afterClipping.push_back(polygonoPoitns[i]);
        flag = 1;
    }

    std::vector<vector<2>> afterClippingAux; 
    if(afterClipping.size() != 1 )
    {
        // odd_enven espera puntos contínuos (par-impar), se hace un cambio de posiciones si el polígono es un cuadrilatero        
        if(afterClipping.size() == 4 )
        {
           
            afterClippingAux.push_back(afterClipping[0]);
            afterClippingAux.push_back(afterClipping[1]);
            afterClippingAux.push_back(afterClipping[3]);
            afterClippingAux.push_back(afterClipping[2]);    
            afterClipping = afterClippingAux;
        }
          
        // Rellenamos el Nuevo Polígono (Se le pasan, los vértices originales para la Interpolación - Iluminación)
        odd_even(afterClipping.size(), 2,afterClipping,__w,__h,__color_buffer,puntos,luz);
                
    }    
    afterClipping.clear(); polygonoPoitns.clear(); afterClippingAux.clear();



    
   
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

