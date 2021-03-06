//
// Created by Ania Wójcik on 11.04.2018.
//

#include "TextPool.h"
namespace pool{
    TextPool::TextPool(){}

    TextPool::TextPool(TextPool &&pointer){
        std::swap(words,pointer.words);
    }

    TextPool&TextPool::operator=(TextPool &&pointer){
        if (this == &pointer) {
            return *this;
        }
        else{
            words.clear();
            std::swap(words,pointer.words);
            return *this;
        }

    }

    TextPool::~TextPool(){
        words.clear();
    }

    TextPool::TextPool(const std::initializer_list<std::string> &elements_list){
        words = elements_list;
    }

    std::experimental::string_view TextPool::Intern(const std::string &str){
        bool found = false;
        std::string temp;
        std::string i;
        for(auto i : words){
            if(i == str){
                found = true;
                temp = i;
                break;
            }
        }
        if(found){
            return temp;
        }
        else {
            words.insert(str);
            return str;
        }
    }


    size_t TextPool::StoredStringCount() const{
        return words.size();
    }

}