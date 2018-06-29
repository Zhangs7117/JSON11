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

int main(int argc, char **argv) {
    // const string simple_test = 
    // R"({"name":"姓名为","sex":"性别","nation":"民族","birthday":"出生年月日如:20170310","address":"住址","id_number":"623023199312125202",
    //         "authority": "签发机关","validity":"有效期限如：20170310-20370310","id_image": "身份证头像Base64编码字符串"})";
    char filename_out[] = "a.json";
    char filename_in[]  = "b.json"; 
    const string file_test_out = readFileIntoString(filename_out);
    const string file_test_in = readFileIntoString(filename_in);
    int keynum = 0;

    char *buf;
    int *len;
    keynum = string2buffer(file_test_in,file_test_out,buf,len);
    for (int i=0;i<keynum;i++){
        std::cout<<buf+len[i]<<std::endl;
    }
    delete []buf;
    delete []len;
    return 0;
}

