#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object.h"
#include <vector>
#include <map>
#include <iostream>
#include <utility>      
#include <deque>  
#include <algorithm> 
#include <math.h>  
//! triangle
class triangle: public object {
public:
    //! constructor
    triangle(matrix<4, 4>& __t, material &__material, vector<3> __v1, vector<3> __v2,
            vector<3> __v3);

    //! rasterize
    virtual bool rasterize(camera* __camera, unsigned short __w, unsigned short __h,
            vector<3> __ambient, dlight *__dlights, unsigned long __num_dlights, plight *__plights,
            unsigned long __num_plights, float*& __color_buffer, float*& __depth_buffer);

    //! draw_points
    void draw_point(vector<2> p, unsigned int __w, unsigned int __h, float*& __color_buffer);

    // !! bresenham line
    void bresenham_line(vector<2> __pv1, vector<2> __pv2,unsigned int __w, unsigned int __h, float*& __color_buffer,std::vector<vector<2>>,std::vector<vector<3>>); 

    // !! scan line
    void scanLine(std::vector<std::pair <vector<2>,vector<2> >> aristas,unsigned int __w, unsigned int __h, float*& __color_buffer);

    // !! scan line odd-even
    void odd_even(int,int,std::vector<vector<2>>,unsigned int __w, unsigned int __h, float*& __color_buffer,std::vector<vector<2>>,std::vector<vector<3>>);

    // !! clipping
    bool ordenVector(int i,int j);
    int calcularZona(double x, double y);
    void cohenSutherlandClip(double x1, double y1,double x2, double y2,unsigned int __w, unsigned int __h, float*& __color_buffer,std::vector<vector<2>>);

    // !! coordenadas baricéntricas
    void coorBaricentrias(float x, float y,std::vector<vector<2>>,bool,std::vector<vector<3>>);

    // !! iluminación
    std::vector<vector<3>> iluminacion(std::vector<vector<2>>vertices);

    /*Algoritmo: Vector Dirección*/
    vector<3> direccion(vector<3>pto1,vector<3>pto2 );
    /*Algoritmo: Normalizar un Vector*/
    vector<3> normalizar(vector<3>_vector);
    /*Algoritmo: Normal Triángulos*/
    vector<3> normalTriangulo(vector<3>v1,vector<3>v2,vector<3>v3);
    /*Algoritmo: Reflection Vector*/
    vector<3> reflection(vector<3>n,vector<3>l);
    vector<3> ambientL();
    /*Algoritmo: Diffuse Light*/
    vector<3> diffueseL(vector<3>n,vector<3>l);
    /*Algoritmo: Specular Light*/
    vector<3> specularL(vector<3>r,vector<3>v);




protected:
    //! vertex 1
    vector<3> _v1;

    //! vertex 2
    vector<3> _v2;

    //! vertex 3
    vector<3> _v3;
};

#endif
