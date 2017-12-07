#ifndef _PARSER_H_
#define _PARSER_H_

#include "stack.h"
#include <fstream>
#include "vector.h"
#include "engine.h"
#include "object.h"
#include "transformation.h"
#include <map>
#include "triangle.h"			// triangle
// [->> 
//  add include files for other objects
// <<-]

//! parser (all changes here)
class parser {
public:
    //! define pointer to function type
    typedef bool (*_p2f1)(engine&, std::ifstream&);
    typedef bool (*_p2f2)(std::ifstream&);

private:

    //! the map of functions for the objects
    static std::map<std::string, _p2f1> _obj_funcs;

    //! the map of functions for the lights
    static std::map<std::string, _p2f1> _light_funcs;

    //! the map of functions for the transformations
    static std::map<std::string, _p2f2> _trans_funcs;

    //! the map of functions for the head funcs
    static std::map<std::string, _p2f1> _head_funcs;

    //! to input the line
    static char __line[2000];
    static std::string __sline;

    //! the stack of transformations
    static stack<transformation> _transformations;

    //! read background
    static bool background(engine& __rt, std::ifstream& __ifile) {
        // get first line
        __ifile >> __sline;
        if (__sline != "[background]") {
            __sline = "token [background] expected";
            return false;
        }

        // get color
        __ifile >> __sline;
        if (__sline != "rgb") {
            __sline = "token rgb expected";
            return false;
        }
        vector<3> __color;
        __ifile >> __color[0];
        __ifile >> __color[1];
        __ifile >> __color[2];

        // get closure
        __ifile >> __sline;
        if (__sline != "[/background]") {
            __sline = "token [/background] expected";
            return false;
        }

        // set background
        __rt.backgroud_color() = __color;

        // success
        return true;
    }

    //! read camera
    static bool cam(engine& __rt, std::ifstream& __ifile) {
        // get first line
        __ifile >> __sline;
        if (__sline != "[camera]") {
            __sline = "token [camera] expected";
            return false;
        }

        // get atribute
        for (register unsigned short __i = 0; __i < 4; __i++) {
            __ifile >> __sline;
            if (__sline == "pos") {
                vector<4> __pos;
                __ifile >> __pos[0];
                __ifile >> __pos[1];
                __ifile >> __pos[2];
                __pos[3] = 1.0;
                __rt.cam().pos() = __pos;
            } else if (__sline == "dir") {
                vector<4> __dir;
                __ifile >> __dir[0];
                __ifile >> __dir[1];
                __ifile >> __dir[2];
                __dir[3] = 0.0;
                __rt.cam().dir() = __dir;
            } else if (__sline == "up") {
                vector<4> __up;
                __ifile >> __up[0];
                __ifile >> __up[1];
                __ifile >> __up[2];
                __up[3] = 0.0;
                __rt.cam().up() = __up;
            } else if (__sline == "fovy") {
                float __fovy;
                __ifile >> __fovy;
                __rt.cam().fovy() = __fovy;
            } else {
                __sline = "error while parsing camera expected";
                return false;
            }
        }

        // calculate right vector
        __rt.cam().calc_right();

        // get closure
        __ifile >> __sline;
        if (__sline != "[/camera]") {
            __sline = "token [/camera] expected";
            return false;
        }

        // success
        return true;
    }

//->> TRANSFORMATIONS

//! read translation
    static bool translation(std::ifstream& __ifile) {
        // read next word
        std::string __slinel;
        __ifile >> __slinel;
        if (__slinel != "dxdydz") {
            __sline = "token dxdydz expected";
            return false;
        }

        // transformations
        transformation __last;
        _transformations.top(__last);

        // read
        vector<3> __translate;
        __ifile >> __translate[0];
        __ifile >> __translate[1];
        __ifile >> __translate[2];
        transformation __new;
        __new.translate(__translate);

        // transform the new transformation
        __new.transform(__last);

        // push the transformation
        _transformations.push(__new);

        // success
        return true;
    }

    //! read rotation
    static bool rotation(std::ifstream& __ifile) {
        // the attributes
        std::string __slinel;
        vector<3> __axis;
        float __angle;

        // read next word
        for (register unsigned short __i = 0; __i < 2; __i++) {
            __ifile >> __slinel;
            if (__slinel == "angle")
                __ifile >> __angle;
            else if (__slinel == "axis") {
                __ifile >> __axis[0];
                __ifile >> __axis[1];
                __ifile >> __axis[2];
            } else {
                __sline = "error while parsing rotation";
                return false;
            }
        }

        // transformations
        transformation __last;
        _transformations.top(__last);

        // read
        transformation __new;
        __new.rotate(__angle, __axis);

        // transform the new transformation
        __new.transform(__last);

        // push the transformation
        _transformations.push(__new);

        // success
        return true;
    }

    //! read scale
    static bool scale(std::ifstream& __ifile) {
        // read next word
        std::string __slinel;
        __ifile >> __slinel;
        if (__slinel != "sxsysz") {
            __sline = "token sxsysz expected";
            return false;
        }

        // transformations
        transformation __last;
        _transformations.top(__last);

        // read
        vector<3> __scale;
        __ifile >> __scale[0];
        __ifile >> __scale[1];
        __ifile >> __scale[2];
        transformation __new;
        __new.scale(__scale);

        // transform the new transformation
        __new.transform(__last);

        // push the transformation
        _transformations.push(__new);

        // success
        return true;
    }

    //! read transformation
    static bool trans(engine& __rt, std::ifstream& __ifile) {
        // read next word
        std::string __slinel;
        __ifile >> __slinel;
        if (__slinel != "name") {
            __sline = "token name expected";
            return false;
        }

        // call the function
        __ifile >> __slinel;
        if (!(*_trans_funcs[__slinel])(__ifile))
            return false;

        // success
        return true;
    }

    //! read transformation
    static bool transend(engine& __rt, std::ifstream& __ifile) {
        // pop the transformation
        transformation __dummy;
        _transformations.pop(__dummy);

        return true;
    }

//->>  OBJECTS

//! read triangle
    static bool triangles(engine& __rt, std::ifstream& __ifile) {
        // the attributes
        std::string __slinel;
        material __material;
        vector<3> __v1, __v2, __v3;

        // get atribute
        for (register unsigned short __i = 0; __i < 6; __i++) {
            __ifile >> __slinel;
            if (__slinel == "vertices") {
                __ifile >> __v1[0];
                __ifile >> __v1[1];
                __ifile >> __v1[2];

                __ifile >> __v2[0];
                __ifile >> __v2[1];
                __ifile >> __v2[2];

                __ifile >> __v3[0];
                __ifile >> __v3[1];
                __ifile >> __v3[2];
            } else if (__slinel == "refractive")
                __ifile >> __material._refractive;
            else if (__slinel == "reflective")
                __ifile >> __material._reflective;
            else if (__slinel == "shinniness")
                __ifile >> __material._shininness;
            else if (__slinel == "ior")
                __ifile >> __material._ior;
            else if (__slinel == "rgb") {
                __ifile >> __material._color[0];
                __ifile >> __material._color[1];
                __ifile >> __material._color[2];
                __material._color[3] = 1.f; // opaque
            } else {
                __sline = "error while parsing triangle";
                return false;
            }
        }

        // transformations
        transformation __last;
        _transformations.top(__last);

        // new triangle
        matrix<4, 4> __temp = __last.t();
        triangle *__triangle = new triangle(__temp, __material, __v1, __v2, __v3);

        // add object
        __rt.add_object((object*) __triangle);

        // success
        return true;
    }

    //! read object
    static bool obj(engine& __rt, std::ifstream& __ifile) {
        // read next word
        std::string __slinel;
        __ifile >> __slinel;
        if (__slinel != "name") {
            __sline = "token name expected";
            return false;
        }

        // call the function
        __ifile >> __slinel;
        if (!(*_obj_funcs[__slinel])(__rt, __ifile))
            return false;

        // read next word
        __ifile >> __slinel;
        if (__slinel != "[/object]") {
            __sline = "token [/object] expected";
            return false;
        }

        // success
        return true;
    }

//->>  LIGHTS

    //! read light
    static bool ambient(engine& __rt, std::ifstream& __ifile) {
        // get atribute
        std::string __slinel;
        __ifile >> __slinel;
        if (__slinel != "rgb") {
            __sline = "token rgb expected";
            return false;
        }

        // get color
        vector<3> __color;
        __ifile >> __color[0];
        __ifile >> __color[1];
        __ifile >> __color[2];

        // add light
        __rt.ambient() = __color;

        // success
        return true;
    }

    //! read light
    static bool point(engine& __rt, std::ifstream& __ifile) {
        // get atribute
        std::string __slinel;
        __ifile >> __slinel;
        if (__slinel != "rgb") {
            __sline = "token rgb expected";
            return false;
        }

        // get color
        vector<3> __color;
        __ifile >> __color[0];
        __ifile >> __color[1];
        __ifile >> __color[2];

        // add light
        plight *__light = new plight;
        __light->_color = __color;
        __light->_pos[0] = 0.0;
        __light->_pos[1] = 0.0;
        __light->_pos[2] = 0.0;
        __light->_pos[3] = 1.0;

        // set position
        transformation __trans;
        _transformations.top(__trans);
        __trans.apply(__light->_pos);
        __rt.add_point_light(__light);

        // success
        return true;
    }

    //! read light
    static bool spot(engine& __rt, std::ifstream& __ifile) {
        // new light
        std::string __slinel;
        dlight *__light = new dlight;

        // get atribute
        for (register unsigned short __i = 0; __i < 3; __i++) {
            __ifile >> __slinel;
            if (__slinel == "rgb") {
                vector<3> __rgb;
                __ifile >> __rgb[0];
                __ifile >> __rgb[1];
                __ifile >> __rgb[2];
                __light->_color = __rgb;
            } else if (__slinel == "dir") {
                vector<4> __dir;
                __ifile >> __dir[0];
                __ifile >> __dir[1];
                __ifile >> __dir[2];
                __dir[3] = 0.0;
                __light->_dir = __dir;
            } else if (__slinel == "angle") {
                float __angle;
                __ifile >> __angle;
                __light->_angle = __angle;
            } else {
                __sline = "error while parsing spot light";
                return false;
            }
        }

        // the position of the light
        __light->_pos[0] = 0.0;
        __light->_pos[1] = 0.0;
        __light->_pos[2] = 0.0;
        __light->_pos[3] = 1.0;
        transformation __trans;
        _transformations.top(__trans);
        __trans.apply(__light->_pos);

        // transform direction
        __trans.apply(__light->_dir);

        // add light
        __rt.add_directional_light(__light);

        // success
        return true;
    }

    //! read light
    static bool directional(engine& __rt, std::ifstream& __ifile) {
        // new light
        std::string __slinel;
        dlight *__light = new dlight;

        // get atribute
        for (register unsigned short __i = 0; __i < 2; __i++) {
            __ifile >> __slinel;
            if (__slinel == "rgb") {
                vector<3> __rgb;
                __ifile >> __rgb[0];
                __ifile >> __rgb[1];
                __ifile >> __rgb[2];
                __light->_color = __rgb;
            } else if (__slinel == "dir") {
                vector<4> __dir;
                __ifile >> __dir[0];
                __ifile >> __dir[1];
                __ifile >> __dir[2];
                __dir[3] = 0.0;
                __light->_dir = __dir;
            } else {
                __sline = "error while parsing directional light";
                return false;
            }
        }

        // the position of the light
        __light->_pos[0] = 0.0;
        __light->_pos[1] = 0.0;
        __light->_pos[2] = 0.0;
        __light->_pos[3] = 1.0;
        transformation __trans;
        _transformations.top(__trans);
        __trans.apply(__light->_pos);

        // transform direction
        __trans.apply(__light->_dir);

        // add light
        __rt.add_directional_light(__light);

        // success
        return true;
    }

    //! read light
    static bool lit(engine& __rt, std::ifstream& __ifile) {
        // read next word
        std::string __slinel;
        __ifile >> __slinel;
        if (__slinel != "name") {
            __sline = "token name expected";
            return false;
        }

        // call the function
        __ifile >> __slinel;
        if (!(*_light_funcs[__slinel])(__rt, __ifile))
            return false;

        // read next word
        __ifile >> __slinel;
        if (__slinel != "[/light]") {
            __sline = "token [/light] expected";
            return false;
        }

        // success
        return true;
    }

public:
    //! constructor
    static void init() {
        _obj_funcs["triangle"] = &triangles;

        _light_funcs["ambient"] = &ambient;
        _light_funcs["point"] = &point;
        _light_funcs["spot"] = &spot;
        _light_funcs["directional"] = &directional;

        _trans_funcs["translate"] = &translation;
        _trans_funcs["rotate"] = &rotation;
        _trans_funcs["scale"] = &scale;

        _head_funcs["[transformation]"] = &trans;
        _head_funcs["[/transformation]"] = &transend;
        _head_funcs["[object]"] = &obj;
        _head_funcs["[light]"] = &lit;

        transformation __identity;
        _transformations.push(__identity);
    }

    //! parse the file
    static bool parse(engine& __rt, std::string __scene_file, std::string &__errormsg) {
        // init
        std::string __slinel;
        init();

        // open file
        std::ifstream __ifile(__scene_file.c_str(), std::ios::in);

        // check if open
        if (!__ifile) {
            __errormsg = "cannot open file";
            return false;
        }

        // read background
        if (!background(__rt, __ifile)) {
            __ifile.close();
            __errormsg = __sline;
            return false;
        }

        // read camera
        if (!cam(__rt, __ifile)) {
            __ifile.close();
            __errormsg = __sline;
            return false;
        }

        // read next word
        __ifile >> __slinel;

        // repeat
        while (__slinel != "[end]" && __slinel != "") {
            // call the right function
            if (!(*_head_funcs[__slinel])(__rt, __ifile)) {
                __errormsg = __sline;
                return false;
            }

            // read next word
            __ifile >> __slinel;
        }

        // if no end token was found
        if (__slinel == "") {
            __errormsg = "passed file end without finding token [end]";
            return false;
        }

        // close file
        __ifile.close();

        // success
        return true;

    }
};

#endif
