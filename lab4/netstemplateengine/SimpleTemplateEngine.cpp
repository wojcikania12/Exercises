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
        int match_index;
        std::regex pattern(R"(\{\{(\w*)\}\})");
        std::smatch found_match;
        while(regex_search(temp, found_match, pattern)){
            for(auto i : found_match){
                match_index = temp.find(i.str());
                while(match_index != std::string::npos) {
                    for (auto iterator = model.begin(); iterator != model.end(); ++iterator)
                        if (iterator->first == i.str()) {
                            std::string temp_str = i.str();
                            temp.replace(match_index, temp_str.length(), iterator->second);
                        }
                        else{
                            temp.replace(match_index, i.length(), "");
                        }
                }
            }

        }
        return temp;
    }
}