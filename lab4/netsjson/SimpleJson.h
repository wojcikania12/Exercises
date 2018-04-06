//
// Created by Ania Wójcik on 04.04.2018.
//

#ifndef JIMP_EXERCISES_SIMPLEJSON_H
#define JIMP_EXERCISES_SIMPLEJSON_H

#include <experimental/optional>
#include <string>
#include <vector>
#include <map>
#include <sstream>

namespace nets {
    class JsonValue {
    public:
        JsonValue();
        JsonValue(std::string s_value);
        JsonValue(int i_value);
        JsonValue(double d_value);
        JsonValue(bool b_value);
        JsonValue(std::vector<JsonValue> vec);
        JsonValue(std::map<std::string,JsonValue> m);

        std::experimental::optional<JsonValue> ValueByName(const std::string &name) const;

        std::string ToString() const;

    private:
        std::string s;
        int i;
        double d;
        bool b;
        std::vector<JsonValue> v;
        std::map<std::string,JsonValue> map;
        int number;

    };
}


#endif //JIMP_EXERCISES_SIMPLEJSON_H
