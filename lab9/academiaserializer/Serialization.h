//
// Created by Ania Wójcik on 13.05.2018.
//

#ifndef JIMP_EXERCISES_SERIALIZATION_H
#define JIMP_EXERCISES_SERIALIZATION_H
#include<iostream>
#include<vector>
#include <string>
#include <experimental/optional>
namespace academia{

    class Serializer;

    class Serializable{
    public:
        virtual void Serialize(Serializer *s)const{};
    };

    class Room:public Serializable{
    public:
        enum class Type{
            COMPUTER_LAB,
            LECTURE_HALL,
            CLASSROOM
        };
        std::string TypeToString(Room::Type type)const;
        Room()= default;
        Room(int id, std::string number,Type type);
        ~Room() = default;
        void Serialize(Serializer *s)const override ;

    protected:
        int room_id;
        Type room_type;
        std::string room_number;
    };

    class Building:public Serializable{
    public:
        Building()= default;
        Building(int id, std::string number,const std::vector<Room> &value);
        ~Building() = default;
        void Serialize(Serializer *s)const override ;
        int Id() const;

    protected:
        int building_id;
        std::string building_number;
        std::vector<Room> all_rooms;
        std::vector<std::reference_wrapper<const Serializable>> wrap_rooms;
    };


    class Serializer: public Serializable{
    public:
        Serializer() = default;
        Serializer(std::ostream *out){
            outstr =out;
        };
        ~Serializer() = default;
        virtual void IntegerField(const std::string &field_name, int value) =0;
        virtual void DoubleField(const std::string &field_name, double value)=0;
        virtual void StringField(const std::string &field_name, const std::string &value)=0;
        virtual void BooleanField(const std::string &field_name, bool value)=0;
        virtual void SerializableField(const std::string &field_name, const academia::Serializable &value)=0;
        virtual void ArrayField(const std::string &field_name,
                                const std::vector<std::reference_wrapper<const academia::Serializable>> &value)=0;
        virtual void Header(const std::string &object_name)=0;
        virtual void Footer(const std::string &object_name)=0;

        std::ostream *outstr;
    };

    class XmlSerializer: public Serializer{
    public:
        XmlSerializer()= default;
        ~XmlSerializer()= default;
        XmlSerializer(std::ostream *out){
            outstr = out;
        }

        void IntegerField(const std::string &field_name, int value) override ;
        void DoubleField(const std::string &field_name, double value)override ;
        void StringField(const std::string &field_name, const std::string &value)override ;
        void BooleanField(const std::string &field_name, bool value)override ;
        void SerializableField(const std::string &field_name, const academia::Serializable &value)override ;
        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value)override ;
        void Header(const std::string &object_name)override ;
        void Footer(const std::string &object_name)override ;



    };
    class JsonSerializer: public Serializer{
    public:
        JsonSerializer()= default;
        ~JsonSerializer()= default;
        JsonSerializer(std::ostream *out){
            outstr = out;
        }
        void IntegerField(const std::string &field_name, int value) override ;
        void DoubleField(const std::string &field_name, double value)override ;
        void StringField(const std::string &field_name, const std::string &value)override ;
        void BooleanField(const std::string &field_name, bool value)override ;
        void SerializableField(const std::string &field_name, const academia::Serializable &value)override ;
        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value)override ;
        void Header(const std::string &object_name)override ;
        void Footer(const std::string &object_name)override ;
    };

    class BuildingRepository{
    public:
        BuildingRepository() = default;
        ~BuildingRepository() = default;
        BuildingRepository(std::initializer_list<Building> buildings);
        void StoreAll(Serializer *serializer);
        void Add(const Building& building);
        std::experimental::optional<Building> operator [](int number) const;

        std::vector<Building> all_buildings;
        std::vector<std::reference_wrapper<const academia::Serializable>> wrap_buildings;

    };



}


#endif //JIMP_EXERCISES_SERIALIZATION_H
