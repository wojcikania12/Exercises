//
// Created by Ania Wójcik on 04.04.2018.
//

#include "SimpleJson.h"

namespace nets{
    JsonValue::JsonValue() {}
    JsonValue::JsonValue(std::string s_value){
        string_= std::move(s_value);
        number = 6;
    }
    JsonValue::JsonValue(int i_value){
        integer_=i_value;
        number =1;
    }
    JsonValue::JsonValue(double d_value){
        double_=d_value;
        number =2;
    }
    JsonValue::JsonValue(bool b_value){
        bool_=b_value;
        number =3;
    }
    JsonValue::JsonValue(std::vector<JsonValue> vec){
        vector_= std::move(vec);
        number = 4;
    }
    JsonValue::JsonValue(std::map<std::string,JsonValue> m){
        map_= std::move(m);
        number=5;
    }
    std::experimental::optional<JsonValue> JsonValue::ValueByName(const std::string &name) const{
        auto it=map_.find(name);
        if(it!=map_.end()) {
            return std::experimental::make_optional(it->second);
        }
        else {
            return {};
        }
    }

    std::string JsonValue::ToString() const {
        std::ostringstream output;
        std::string temp, temp2, temp3;
        std::string str;
        switch (number) {
            case 1:
                return std::to_string(integer_);
            case 2:
                output << double_;
                str = output.str();
                return str;
            case 3:
                if (!bool_) {
                    return "false";
                } else {
                    return "true";
                }
            case 4:
                temp = "[";
                for (auto i :vector_) {
                    temp += i.ToString();
                    temp += ", ";
                }
                temp = temp.erase(temp.length() - 2, 2) + "]";
                return temp;
            case 5:
                temp2 = '{';
                for (auto j:map_) {
                    temp2 += "\"";
                    for (auto i:j.first) {
                        if (i == '\\' || i == '\"') {
                            temp2 += '\\';
                        }
                        temp2 += i;
                    }
                    temp2 += "\": " + j.second.ToString() + ", ";
                }
                temp2 = temp2.substr(0, temp2.length() - 2) + '}';
                return temp2;
            case 6:
                temp3 += '\"';
                for (char i : string_) {
                    if (i == '\\' || i == '\"') {
                        temp3 += '\\';
                    }
                    temp3 += i;
                }
                temp3 += '\"';
                return temp3;
        }
    }
}