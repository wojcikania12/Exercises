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
        size_t match_index, regex_index = 0;
        std::regex pattern(R"(\{\{(\w*)\}\})");
        std::smatch found_match;
        regex_search(temp, found_match, pattern);
            match_index = temp.find(found_match[regex_index]);
                for (const auto &iterator : model) {
                    std::string str = found_match[(regex_index + 1)];
                    if (iterator.first == str) {
                        temp.replace(match_index, found_match[regex_index].length(), iterator.second);
                    } else {
                        temp.replace(match_index, found_match[regex_index].length(), "");
                    }
        }
        return temp;
    }
}
