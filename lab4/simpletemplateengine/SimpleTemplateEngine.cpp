//
// Created by Ania Wójcik on 31.03.2018.
//

#include "SimpleTemplateEngine.h"
namespace nets {
    using std::string;

    View(const std::string &phrase) {
        input = phrase;
    }

    string Render(const std::unordered_map<std::string, std::string> &model) const {
        string temp = input;
        int match_index;
        std::regex pattern("\\{\\{(\\w*)\\}\\}");
        smatch found_match;
        while(regex_search(temp, found_match, pattern)){
        for(auto i : found_match){
            match_index = temp.find(i.str());
            while(match_index != string::npos) {
                for (iterator = model.begin(); iterator != model.end(); ++iterator)
                    if (iterator->first == i.str()) {
                        string temp_str = i.str();
                        temp.replace(match_index, temp_str.length(), iterator->second);
                    }
                else{
                        temp.replace(match_index, temp_str.length(), "");
                    }
            }
            }

        }
        return temp;
    }
}