//
// Created by Ania Wójcik on 20.03.2018.
//

#ifndef JIMP_EXERCISES_TINYURL_H
#define JIMP_EXERCISES_TINYURL_H

#include <utility>
#include <string>
#include <array>
#include <memory>
#include <map>

namespace tinyurl {
    struct TinyUrlCodec{
        std::map<std::string, std::string> Map;
    };

    std::unique_ptr <TinyUrlCodec> Init();

    void NextHash(std::array<char, 6> *state);

    std::string Encode(const std::string &url, std::unique_ptr <TinyUrlCodec> *codec);

    std::string Decode(const std::unique_ptr <TinyUrlCodec> &codec, const std::string &hash);
}

#endif //JIMP_EXERCISES_TINYURL_H
