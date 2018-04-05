//
// Created by Ania Wójcik on 04.04.2018.
//

#include "SimpleTemplateEngine.h"
namespace nets {
    View::View(const std::string &phrase) {
        input = phrase;
    }

    std::string View::Render(const std::unordered_map<std::string, std::string> &model) const {
        std::string temp = input;
        size_t match_index;
        std::regex pattern(R"(\{\{(\w*)\}\})");
        std::smatch found_match;
        regex_search(temp, found_match, pattern);
        bool flag = true;
        while(flag) {
            match_index = temp.find(found_match[0]);
            if(match_index!= std::string::npos) {
                for (const auto &iterator : model) {
                    if (iterator.first == found_match[1]) {
                        temp.replace(match_index, found_match[0].length(), iterator.second);
                    } else {
                        temp.replace(match_index, found_match[0].length(), "");
                    }
                }
            }
                else{
                   break;
                }
            flag =regex_search(temp, found_match, pattern);
        }
        return temp;

    }
}