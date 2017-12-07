#include <math.h>  

/*Algoritmo: Vector Dirección*/
void direccion(vector<3>pto1,vector<3>pto2 )
{
    //Coloca como pto1, a quien quieres apuntar
    vector<3> vecDir = pto1 - pto2;
}
/*Algoritmo: Normalizar un Vector*/
void normalizar(vector<3>_vector)
{
    float square = sqrt((_vector[0]*_vector[0]) + (_vector[1]*_vector[1]) + (_vector[2]*_vector[2]));
    vector<3> normalized = ((_vector[0] / square), (_vector[1] / square), (_vector[2] / square));
}

/*Algoritmo: Normal Triángulos*/
void normalTriangulo(vector<3>v1,vector<3>v2,vector<3>v3)
{
   
    vector<3>vector1 = v2 - v1;
    vector<3>vector2 = v3 - v1;
    vector<3>normal = (vector1[1]*vector2[2] - vector2[1]*vector1[2] , vector1[2]*vector2[0] - vector2[2]*vector1[0] , vector1[0]*vector2[1] - vector2[0]*vector1[1]) //    normal = (y1*z2 - y2*z1 , z1*x2 - z2*x1 , x1*y2 - x2*y1)
    normalizar(normal);
}

/*Algoritmo: Calucla centro de un triángulo*/
void coorBaricentricas(vector<3>v1,vector<3>v2,vector<3>v3)
{
    vector<3> centroide = ((v1[0]+v2[0]+v3[0])/3,(v1[1]+v2[1]+v3[1])/3,(v1[2]+v2[2]+v3[2])/3)
}

/*Algoritmo: Reflection Vector*/
void reflection(vector<3>n,vector<3>n )
{
    float escalar = (n[0]*l[0] + n[1]*l[1] + n[2]*l[2]) * 2; //Produncto punto de n * l = escalar    
    vector<3>r = escalar * (n - l);
}

//Serpian var Globales
void vectorPhongShaing()
{
    vector<3> centroide = coorBaricentricas();
    vector<3> n = normalTriangulo();
    vector<3> v = direccion(camara,centroide); //viewVector : that points in the direction of the viewer.
    vector<3> l = direccion(light,centroide);  //lightVector : that points towards the light source.    
    vector<3> r; // reflectionVector: that indicates the direction of pure reflection of the light vector.
}

/*Algoritmo: Ambient Light*/
void ambientL()
{
    vector<3> ka = (0.2,0.5,0.6); // coefficient of ambient reflection entre 0 y 1
    vector<3> la = (0.5,0.5,0.5) // light component consists of 3 color components
    vector<3> Ia = ka * la;
}


/*Algoritmo: Diffuse Light*/
void diffueseL(vector<3>n,vector<3>l)
{
    vector<3> kd = (0.2,0.5,0.6); // coefficient of ambient reflection entre 0 y 1
    vector<3> ld = (0.5,0.5,0.5) // light component consists of 3 color components
    float escalar = (n[0]*l[0] + n[1]*l[1] + n[2]*l[2]); //Produncto punto de n * l = escalar
    vector<3> Id = kd * escalar * ld;
}

/*Algoritmo: Specular Light*/
void specularL(vector<3>r,vector<3>v)
{
    int shinniness = 45;
    vector<3> ks = (0.2,0.5,0.6); // coefficient of ambient reflection entre 0 y 1
    vector<3> ls = (0.5,0.5,0.5) // light component consists of 3 color components
    float escalar = (r[0]*v[0] + r[1]*v[1] + r[2]*v[2]); //Produncto punto de r * v = (escalar) ^ shinniness 
    escalar = pow(escalar,shinniness)   ;
    vector<3> Is = ks * escalar * ls;
}
