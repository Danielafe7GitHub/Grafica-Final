#include "parser.h"

// instantiate
char parser::__line[2000] = "";
std::string parser::__sline = "";

// the map of functions for the objects
std::map<std::string, parser::_p2f1> parser::_obj_funcs;

// the map of functions for the lights
std::map<std::string, parser::_p2f1> parser::_light_funcs;

// the map of functions for the transformations
std::map<std::string, parser::_p2f2> parser::_trans_funcs;

// the map of functions for the head funcs
std::map<std::string, parser::_p2f1> parser::_head_funcs;

// the stack of transformations
stack<transformation> parser::_transformations;
