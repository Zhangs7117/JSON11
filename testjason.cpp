/*
 * Beginning of standard source file, which makes use of the customizations above.
 */
#include <cassert>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include "json11.hpp"
#include <type_traits>
#include <fstream>
#include "string2buffer.hpp"

using namespace json11;
using std::string;

// int string2buffer (const string json, char* buffer){
//     string err;
//     const auto jsonparse = Json::parse(json, err);
//     strcpy(buffer,jsonparse["name"].string_value().c_str());
//     strcpy(buffer+25,jsonparse["id_number"].string_value().c_str());
//     // std::cout<<err<<std::endl;
//     if (err[0]=='\0') return 1;
//     else return -1;
// }


string readFileIntoString(const char * filename)
{
std::ifstream ifile(filename);
//将文件读入到ostringstream对象buf中
std::ostringstream buf;
char ch;
while(buf&&ifile.get(ch))
buf.put(ch);
//返回与流对象buf关联的字符串
return buf.str();
}

int main(int argc, char **argv) {
    const string simple_test = 
    R"({"name":"姓名为","sex":"性别","nation":"民族","birthday":"出生年月日如:20170310","address":"住址","id_number":"623023199312125202",
            "authority": "签发机关","validity":"有效期限如：20170310-20370310","id_image": "身份证头像Base64编码字符串"})";
    char filename[] = "a.json"; 
    const string file_test = readFileIntoString(filename);
    int err = 0;
    // char buf[25];
    char *buf = new char [50];
    void * fmt;
    err = string2buffer(file_test,buf,fmt);
    std::cout<<err<<'\n';
    std::cout<<buf<<'\n';
    if((buf+25)[0] == '\0') std::cout<<"right"<<std::endl;
    std::cout<<buf+25<<'\n';
    delete buf;
    return 0;
}

