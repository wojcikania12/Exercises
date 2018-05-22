//
// Created by Ania Wójcik on 20.05.2018.
//

#ifndef JIMP_EXERCISES_SCHEDULER_H
#define JIMP_EXERCISES_SCHEDULER_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>

namespace academia{
    class SchedulingItem{
    public:
        friend class Schedule;
        friend class GreedyScheduler;
        SchedulingItem() = default;
        ~SchedulingItem() = default;

        SchedulingItem(int course,int teacher,int room,int time, int year_);
        int CourseId() const;
        int TeacherId()const;
        int RoomId() const;
        int TimeSlot() const;
        int Year() const;
    private:
        int course_id;
        int teacher_id;
        int room_id;
        int time_slot;
        int year;
    };

    class Schedule{
    public:
        Schedule() = default;
        ~Schedule() = default;

        Schedule OfTeacher(int teacher_id) const;
        Schedule OfRoom(int room_id) const;
        Schedule OfYear(int year) const;
        std::vector<int> AvailableTimeSlots(int n_time_slots) const;
        void InsertScheduleItem(const SchedulingItem &item);
        size_t Size() const;
        SchedulingItem operator [](int number)const;

    private:
        std::vector<SchedulingItem> schedule;
    };

    class Scheduler{
    public:
        Scheduler() = default;
        ~Scheduler() = default;
        virtual Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                            const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                            const std::map<int, std::set<int>> &courses_of_year,
                                            int n_time_slots)=0;


    };

    class NoViableSolutionFound : public std::runtime_error{
    public:
       explicit NoViableSolutionFound();
    };

    class GreedyScheduler : public Scheduler{
    public:
        Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                    const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                    const std::map<int, std::set<int>> &courses_of_year,
                                    int n_time_slots) override;

    };
}

#endif //JIMP_EXERCISES_SCHEDULER_H
