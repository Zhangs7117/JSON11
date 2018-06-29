#include "string2buffer.hpp"
using namespace json11;
using std::string;



int string2buffer (const std::string  &json_in,const std::string  &json_out, char*& buffer, int *& locs){
    
    string err;
    const auto jsonparse_in = Json::parse(json_in, err);
    std::map<std::string, Json> json_obj = jsonparse_in.object_items();
    std::map<std::string, Json>::iterator iter;

    int key_num = json_obj.size();  
    int loc = 0;
    int buffer_len = 0;
    
    for (iter = json_obj.begin();iter != json_obj.end(); iter++ ){
        buffer_len += iter->second.number_value();
    }

    buffer = new char[buffer_len];
    locs = new int [key_num];

    const auto jsonparse_out = Json::parse(json_out, err);
    int i=0;
    for (iter = json_obj.begin();iter != json_obj.end(); iter++ ){
        strcpy((buffer+loc),jsonparse_out[iter->first].string_value().c_str());
        locs[i] = loc;
        loc = loc + iter->second.number_value();
        i++;
    }

    return key_num;
}

/////////////////////////////////////////////////////////////////
//when u want to divide the function
/////////////////////////////////////////////////////////////////
// int getfmt (const std::string  &json, struct jsonfmt * fmt){
//     string err;
//     const auto jsonparse = Json::parse(json, err);
    
//     std::map<std::string, Json> json_obj = jsonparse.object_items();
//     std::map<std::string, Json>::iterator iter;
    
//     fmt->key_num = json_obj.size();
//     fmt->key_len = new int [fmt->key_num];
//     fmt->key_val = new string [fmt->key_num];
//     int loc = 0;
//     for (iter = json_obj.begin();iter != json_obj.end(); iter++ ){
//         fmt->key_val[loc] = iter->first;
//         fmt->key_len[loc] = iter->second.number_value();
//         std::cout<<iter->first<<" : "<<iter->second.number_value()<<std::endl;
//         loc++;
//     }
    
//     if (err[0]=='\0') return 1;
//     else return -1;
// }


string readFileIntoString(const char * filename)
{
std::ifstream ifile(filename);

//read in the stream
std::ostringstream buf;
char ch;
while(buf&&ifile.get(ch))
buf.put(ch);

//return the str
return buf.str();
}