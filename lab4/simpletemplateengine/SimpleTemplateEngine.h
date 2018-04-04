//
// Created by Ania Wójcik on 04.04.2018.
//

#ifndef JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#define JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#include <string>
#include <unordered_map>
#include <regex>
#include <iostream>
namespace nets{
    class View{
    public:
        View(const std::string &input);
        std:: string Render(const std::unordered_map<std::string, std::string>&model)const;

    private:
        std::string input;

    };
}




#endif //JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
