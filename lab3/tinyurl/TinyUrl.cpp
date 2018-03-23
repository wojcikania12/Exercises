//
// Created by Ania Wójcik on 20.03.2018.
//

#include "TinyUrl.h"

namespace tinyurl{
    std::unique_ptr<TinyUrlCodec> Init(){
        std::unique_ptr <TinyUrlCodec> pointer = std::make_unique<TinyUrlCodec>();
        return pointer;
    }


void NextHash(std::array<char, 6> *state){
    int index = 5;
    for(index; index >= 0; --index){
        (*state)[index] += 1;
        if((*state)[index] == 'Z'+ 1){
            (*state)[index] = 'a';
            break;
        }
        else if((*state)[index] == '9'+ 1){
            (*state)[index] = 'A';
            break;
    }
        else if((*state)[index] == 'z'+ 1){
            (*state)[index] = '0';
            continue;
        }
        else {
            break;
        }
}}

std::string Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec) {
    std::string first_hash = "aaaaaa";
    std::string tinyurl;
    std::array<char, 6> new_hash;
    int index1 = 0;
    int index2 = 0;
    bool not_in_map = true;
    for (auto &i : codec->get()->Map) {
        if (i.second == url) {
            for (auto k : i.first) {
                new_hash[index1] = k;
                index1++;
            }
            not_in_map = false;
            break;
        }
    }
    if (not_in_map) {
        for (auto j : first_hash) {
            new_hash[index2] = j;
            index2++;
        }
        NextHash(&new_hash);
        for(auto l : new_hash){
            tinyurl += l;
        }
        codec->get()-> Map.emplace(tinyurl, url);
    }
    return tinyurl;
}

    std::string Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash) {
        std::string url;
        for(auto a: codec->Map){
            if(a.first==hash){
                url=a.second;
            }
        }
        return url;
    }
}


