//
// Created by Ania Wójcik on 20.05.2018.
//

#include "Scheduler.h"

namespace academia{
    SchedulingItem::SchedulingItem(int course,int teacher,int room,int time, int year_){
        course_id = course;
        teacher_id = teacher;
        room_id = room;
        time_slot = time;
        year = year_;
    }

    int SchedulingItem::CourseId() const{
        return course_id;
    }
    int SchedulingItem::TeacherId() const{
        return teacher_id;
    }
    int SchedulingItem::RoomId() const{
        return room_id;
    }
    int SchedulingItem::TimeSlot() const{
        return time_slot;
    }
    int SchedulingItem::Year() const{
        return year;
    }

    Schedule Schedule::OfTeacher(int teacher_id) const {
        std::vector<SchedulingItem>temp(schedule.size());
        auto it = std::copy_if(schedule.begin(),schedule.end(),temp.begin(),[teacher_id](const SchedulingItem &element)
        {return teacher_id == element.TeacherId();});
        temp.resize(std::distance(temp.begin(),it));
        Schedule temp_schedule;
        temp_schedule.schedule = temp;
        return temp_schedule;
    }

    Schedule Schedule::OfRoom(int room_id) const {
        std::vector<SchedulingItem>temp(schedule.size());
        auto it = std::copy_if(schedule.begin(),schedule.end(),temp.begin(),[room_id](const SchedulingItem &element)
        {return room_id == element.RoomId();});
        temp.resize(std::distance(temp.begin(),it));
        Schedule temp_schedule;
        temp_schedule.schedule = temp;
        return temp_schedule;
    }

    Schedule Schedule::OfYear(int year) const {
        std::vector<SchedulingItem>temp(schedule.size());
        auto it = std::copy_if(schedule.begin(),schedule.end(),temp.begin(),[year](const SchedulingItem &element)
        {return year == element.Year();});
        temp.resize(std::distance(temp.begin(),it));
        Schedule temp_schedule;
        temp_schedule.schedule = temp;
        return temp_schedule;
    }

    std::vector<int> Schedule::AvailableTimeSlots(int n_time_slots) const {
        std::vector<int> temp(n_time_slots);
        std::iota(temp.begin(), temp.end(), 1);
        for(auto &i : schedule){
            if(i.time_slot <= n_time_slots){
                temp.erase(std::remove(temp.begin(), temp.end(), i.time_slot), temp.end());
            }
        }
        std::sort(temp.begin(),temp.end());
        auto temp1 = std::unique(temp.begin(),temp.end());
        temp.erase(temp1,temp.end());
        return temp;

    }

    void Schedule::InsertScheduleItem(const SchedulingItem &item) {
        schedule.push_back(item);
    }

    size_t Schedule::Size() const {
        return schedule.size();
    }

    SchedulingItem Schedule::operator[](int number) const{
        return schedule[number];
    }

    Schedule
    GreedyScheduler::PrepareNewSchedule(const std::vector<int> &rooms,
                                        const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                        const std::map<int, std::set<int>> &courses_of_year,
                                        int n_time_slots)  {
        Schedule new_schedule;
        SchedulingItem temp;
        std::vector<int> used_rooms;
        int room_number = 0;
        int time_slots =0;

        for(auto teacher : teacher_courses_assignment) {
            for (auto course : teacher.second) {
                for (auto year_ : courses_of_year) {
                    for (auto course_id : year_.second) {
                        if (course_id == course) {
                            if(time_slots == n_time_slots){
                                time_slots =0;
                                ++room_number;
                            }
                            temp.teacher_id = teacher.first;
                            temp.year = year_.first;
                            temp.course_id = course;
                            temp.year = rooms[room_number];
                            temp.time_slot = time_slots;
                            new_schedule.InsertScheduleItem(temp);
                        }
                    }
                }
            }
        }
        if(new_schedule.Size() > rooms.size() * n_time_slots)
            throw NoViableSolutionFound();


        return new_schedule;
    }
}