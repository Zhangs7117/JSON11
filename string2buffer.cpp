#include "string2buffer.hpp"
using namespace json11;
using std::string;

int string2buffer (const std::string  &json, char* buffer, void* fmt){
    string err;
    const auto jsonparse = Json::parse(json, err);
    strcpy(buffer,jsonparse["name"].string_value().c_str());
    strcpy(buffer+25,jsonparse["id_number"].string_value().c_str());
    // std::cout<<err<<std::endl;
    if (err[0]=='\0') return 1;
    else return -1;
}