//
// Created by Ania Wójcik on 13.05.2018.
//

#include "Serialization.h"

namespace academia{

    //Room

    Room::Room(int id, std::string number,Room::Type type) {
        room_id = id;
        room_number =std::move(number);
        room_type = type;
    }

    std::string Room::TypeToString(Room::Type type)const {
        switch(type) {
            case Type::COMPUTER_LAB:
                return "COMPUTER_LAB";
            case Type::LECTURE_HALL:
                return "LECTURE_HALL";
            case Type::CLASSROOM:
                return "CLASSROOM";
        }
    }

    void Room::Serialize(Serializer *s)const {
        s->Header("room");
        s->IntegerField("id", room_id);
        s->StringField("name", room_number);
        s->StringField("type", TypeToString(room_type));
        s->Footer("room");
    }

    //Building

    Building::Building(int id, std::string number,
                       const std::vector<Room> &value) {
        building_id = id;
        building_number = std::move(number);
        all_rooms = value;
        for(const auto &i : all_rooms){
            wrap_rooms.push_back(i);
        }

    }

    void Building::Serialize(Serializer *s) const{
        s-> Header("building");
        s -> IntegerField("id",building_id);
        s-> StringField("name",building_number);
        s-> ArrayField("rooms",wrap_rooms);
        s-> Footer("building");
    }

    int Building::Id() const {
        return building_id;
    }

    //XmlSerializer

    void XmlSerializer::Footer(const std::string &object_name){
        *outstr<<"<\\"<<object_name<<">";

    }

    void  XmlSerializer::IntegerField(const std::string &field_name, int value){
        *outstr<<"<"<<field_name<<">"<<std::to_string(value);
        *outstr<<"<\\"<<field_name<<">";
    }

    void XmlSerializer::DoubleField(const std::string &field_name, double value){}

    void XmlSerializer::StringField(const std::string &field_name, const std::string &value){
        *outstr<<"<"<<field_name<<">"<<value;
        *outstr<<"<\\"<<field_name<<">";
    }

    void XmlSerializer::BooleanField(const std::string &field_name, bool value){}

    void XmlSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value){}

    void XmlSerializer::ArrayField(const std::string &field_name,
                                   const std::vector<std::reference_wrapper<const academia::Serializable>> &value){
        *outstr<<"<"<<field_name<<">";
        for(const auto &i : value){
            i.get().Serialize(this);
        }
        *outstr<<"<\\"<<field_name<<">";

    }

    void XmlSerializer::Header(const std::string &object_name){
        *outstr<<"<"<<object_name<<">";
    }

    void JsonSerializer::IntegerField(const std::string &field_name, int value){
        *outstr<<'\"'<<field_name<<'\"'<<": "<<value<<", ";

    }

    void JsonSerializer::DoubleField(const std::string &field_name, double value){}

    void JsonSerializer::StringField(const std::string &field_name, const std::string &value){
        *outstr<<'\"'<<field_name<<'\"'<<": ";
        if(field_name != "type"){
            *outstr<<'\"'<<value<<'\"'<<", ";}
        else{
            *outstr<<'\"'<<value<<'\"';
        }
    }

    void JsonSerializer::BooleanField(const std::string &field_name, bool value){}

    void JsonSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value){}

    void JsonSerializer::ArrayField(const std::string &field_name,
                                    const std::vector<std::reference_wrapper<const academia::Serializable>> &value){
        *outstr<<'\"'<<field_name<<'\"'<<": "<<"[";
        size_t inc = value.size();
        for(const auto &i:value){
            i.get().Serialize(this);
            if(--inc) {
                *outstr<<", ";
            }
        }
        *outstr<<']';

    }

    void JsonSerializer::Header(const std::string &object_name){
        *outstr<<"{";
    }

    void JsonSerializer::Footer(const std::string &object_name){
        *outstr<<"}";
    }

    //BuildingRepository

    BuildingRepository::BuildingRepository(std::initializer_list<Building> buildings) {
        all_buildings = buildings;
        for(const auto &i : all_buildings){
            wrap_buildings.emplace_back(i);
        }
    }

    void BuildingRepository::StoreAll(Serializer *serializer) {
        serializer->Header("building_repository");
        serializer->ArrayField("buildings",wrap_buildings);
        serializer->Footer("building_repository");

    }

    void BuildingRepository::Add(const Building &building) {
        all_buildings.push_back(building);
    }

    std::experimental::optional<Building> BuildingRepository::operator[](int number) const {
        for(const auto &i : all_buildings){
            if(i.Id()==number){
                return std::experimental::make_optional(i);

            }
        }
    }


}
