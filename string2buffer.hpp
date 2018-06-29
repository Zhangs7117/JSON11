#include <cassert>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include "json11.hpp"

int string2buffer (const std::string  &json, char* buffer, void* fmt);