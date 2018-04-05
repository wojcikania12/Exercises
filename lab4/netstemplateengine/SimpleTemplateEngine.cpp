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
        bool flag = false;
        bool replaced = false;
        match_index = temp.find(found_match[0]);
        while(true) {
            bool replaced = false;
            if(match_index!= std::string::npos) {
                for (auto iterator : model) {
                    if (iterator.first == found_match[1]) {
                        temp.replace(match_index, found_match[0].length(), iterator.second);
                        replaced = true;
                        break;
                    }
                }
                if(!replaced){
                    temp.replace(match_index, found_match[0].length(), "");
                    replaced = false;
                }
            }
                flag = regex_search(temp, found_match, pattern);
                if(flag){
                    match_index = temp.find(found_match[0]);
                }
                else if(flag!=true)break;

    }
        return temp;
}
}
