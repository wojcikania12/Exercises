//
// Created by Ania Wójcik on 04.04.2018.
//

#include "SimpleJson.h"

namespace nets{
    JsonValue::JsonValue() {}
    JsonValue::JsonValue(std::string s_value){
        s=s_value;
        number = 6;
    }
    JsonValue::JsonValue(int i_value){
        i=i_value;
        number =1;
    }
    JsonValue::JsonValue(double d_value){
        d=d_value;
        number =2;
    }
    JsonValue::JsonValue(bool b_value){
        b=b_value;
        number =3;
    }
    JsonValue::JsonValue(std::vector<JsonValue> vec){
        v=vec;
        number = 4;
    }
    JsonValue::JsonValue(std::map<std::string,JsonValue> m){
        map=m;
        number=5;
    }
    std::experimental::optional<JsonValue> JsonValue::ValueByName(const std::string &name) const{
        auto it=map.find(name);
        if(it!=map.end()) {
            return std::experimental::make_optional(it->second);
        }
        else {
            return {};
        }
    }

    std::string JsonValue::ToString() const{
        std::ostringstream output;
        std::string temp,temp2,temp3;
        std::string str;
        switch(number){
            case 1:
                return std::to_string(i);
                ;
            case 2:
                output << d;
                str = output.str();
                return str;

            case 3:
                if(b== false){
                    return "false";
                }
                else{
                    return "true";
                }

            case 4:
                temp = "[";
                for(auto i :v){
                    temp += i.ToString();
                    temp += ", ";
                }
                temp = temp.erase(temp.length()-2,2) + "]";
                return temp;
            case 5:
                temp2 = "{";
                for (auto j:map) {
                    temp2 += "\"";
                    for (auto i:j.first) {
                        if (i == '\\' || i == '\"') {
                            temp2 += '\\';
                        }
                    }
                    temp2 += j.first + "\": " + j.second.ToString() + ", ";

                    }
                temp2 = temp2.substr(0, temp2.length() - 2) + "}";
                return temp2;
            case 6:
                temp3="\"";
                for(int i=0;i<s.size();++i){
                    if(s[i]=='\\' ||s[i]=='\"'){
                        temp3+='\\' ;
                    }
                    temp3 += s[i];
                }
                temp3+="\"";
                return temp3;

        }
    }

}