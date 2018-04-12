//
// Created by Ania Wójcik on 11.04.2018.
//

#ifndef JIMP_EXERCISES_TEXTPOOL_H
#define JIMP_EXERCISES_TEXTPOOL_H
#include <initializer_list>
#include <string>
#include <experimental/string_view>
#include <set>
#include <vector>
#include <iostream>

namespace pool{
    class TextPool{
    public:
        TextPool();
        TextPool(TextPool &&pointer);
        TextPool &operator=(TextPool &&pointer);
        TextPool(const std::initializer_list<std::string> &elements_list);
        ~TextPool();
        std::experimental::string_view Intern(const std::string &str);
        size_t StoredStringCount() const;
    private:
        std::set<std::string> words;
    };
}


#endif //JIMP_EXERCISES_TEXTPOOL_H
