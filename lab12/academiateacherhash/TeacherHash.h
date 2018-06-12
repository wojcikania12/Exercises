//
// Created by Ania Wójcik on 01.06.2018.
//

#ifndef JIMP_EXERCISES_TEACHERHASH_H
#define JIMP_EXERCISES_TEACHERHASH_H
#include <string>
#include <functional>

namespace academia{


    class TeacherId{
    public:
        friend class Teacher;
        TeacherId(int id_){
            id = id_;
        };
        operator int() const {
            return id;
        };
    private:
        int id;
    };


    class Teacher{
    public:
       Teacher(TeacherId id_, const std::string &name_, const std::string &department_):id{id_}{
           name = name_;
           department = department_;
       }
        std::string Name()const{
            return name;
        }
        std::string Department()const{
            return department;
        }
        TeacherId Id()const{
            return id;
        }
        operator int(){
            return id.id;
        }
        bool operator==(Teacher other_teacher) const {
            return (id.id==other_teacher.id.id && name==other_teacher.name && department==other_teacher.department);
        }

        bool operator!=(Teacher other_teacher) const {
            return (id.id!=other_teacher.id.id || name!=other_teacher.name || department!=other_teacher.department);
        }
    private:
        std::string name;
        std::string department;
        TeacherId id;

    };

    class TeacherHash{
    public:
        size_t operator()(const Teacher &argument)const{
            size_t hash = std::hash<int>()(argument.Id()) ^ std::hash<std::string>()(argument.Name()) ^
                    std::hash<std::string>()(argument.Department());
            return hash;
        }

    };



}



#endif //JIMP_EXERCISES_TEACHERHASH_H
