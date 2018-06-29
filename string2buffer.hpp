#include <cassert>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include "json11.hpp"

// struct jsonfmt {
//     std::string *key_val;
//     int *key_len;
//     int key_num;
// };



int string2buffer (const std::string  &json_in, const std::string  &json_out, char*& buffer, int*& len);

// int getfmt (const std::string  &json, struct jsonfmt * fmt);

std::string readFileIntoString(const char * filename);