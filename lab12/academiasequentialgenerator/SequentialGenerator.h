//
// Created by Ania Wójcik on 31.05.2018.
//

#ifndef JIMP_EXERCISES_SEQUENTIALGENERATOR_H
#define JIMP_EXERCISES_SEQUENTIALGENERATOR_H

template <typename ID, typename SIPMLE_TYPE>
class SequentialIdGenerator {
    public:
    SequentialIdGenerator(){
        id = 0;
        first_id = true;
    }
    explicit SequentialIdGenerator(SIPMLE_TYPE argument){
        id = argument;
        first_id = true;
    }
    ~SequentialIdGenerator() = default;
    auto NextValue(){
        if(first_id){
            first_id =false;
            return int(id);
        }
        else {
            ++id;
            return int(id);
        }
    }
    private:
    SIPMLE_TYPE id;
    bool first_id;



};


#endif //JIMP_EXERCISES_SEQUENTIALGENERATOR_H
