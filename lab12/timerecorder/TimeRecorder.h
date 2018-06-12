//
// Created by Ania Wójcik on 31.05.2018.
//

#ifndef JIMP_EXERCISES_TIMERECORDER_H
#define JIMP_EXERCISES_TIMERECORDER_H

#include <chrono>
#include <utility>
#include <iostream>
#include <ctime>
#include <ratio>

namespace profiling{

    template <typename T>
    auto TimeRecorder(T argument){
        std::chrono::high_resolution_clock::time_point start , end;
        start = std::chrono::high_resolution_clock::now();
        auto argument_result = argument();
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double,std::milli> duration_ = end - start;
        auto result = std::make_pair(argument_result , duration_.count());
        return result;
    }
}


#endif //JIMP_EXERCISES_TIMERECORDER_H
