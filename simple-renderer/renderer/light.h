#ifndef _LIGHT_H_
#define _LIGHT_H_

//! directional light
struct dlight {
    vector<4> _pos;
    vector<4> _dir;
    float _angle;
    vector<3> _color;
};

//! positional light
struct plight {
    vector<4> _pos;
    vector<3> _color;
};

#endif
