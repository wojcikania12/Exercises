//
// Created by Ania Wójcik on 01.05.2018.
//

#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <vector>
namespace moviesubs {
    class MovieSubtitles {
    public:
       virtual void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second,
                                        std::istream *in, std::ostream *out) = 0;
       virtual int Change_Frames(const int &offset_in_micro_seconds, const int &frames_per_second, const int & actual_frame) =0;

        virtual ~MovieSubtitles()= default;

    };

    class MicroDvdSubtitles: public MovieSubtitles{
    public:
        MicroDvdSubtitles() = default;
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second,
                                         std::istream *in, std::ostream *out) override ;
        int Change_Frames(const int &offset_in_micro_seconds, const int &frames_per_second, const int & actual_frame) override ;
        ~MicroDvdSubtitles() override = default;
    };

    class SubRipSubtitles : public MovieSubtitles{
    public:
        SubRipSubtitles() = default;
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second,
                                 std::istream *in, std::ostream *out) override ;
        int Change_To_Microseconds(const std::string &hours, const std::string &minutes,const std::string &seconds,
                                   const std::string &microseconds) ;
        std::string Change_Time_Format(const int &time) ;
        int Change_Frames(const int &offset_in_micro_seconds, const int &frames_per_second, const int & actual_frame) {};

        ~SubRipSubtitles() override = default;

    };

    class SubtitlesException: public std::invalid_argument{
    public:
        SubtitlesException(const std::string &error, int lines):std::invalid_argument{error}{}
    };

    class NegativeFrameAfterShift: public SubtitlesException{
    public:
        NegativeFrameAfterShift(const std::string &error, int lines):SubtitlesException("Negative frame after shift",lines){}
    };

    class SubtitleEndBeforeStart : public SubtitlesException{
    public:
        SubtitleEndBeforeStart(int lines,std::string str):SubtitlesException("At line " + std::to_string(lines)+": "+str,line),line{lines}{}

        int LineAt()const{
            return line;
        }
    private:
        int line;
    };

    class InvalidSubtitleLineFormat: public SubtitlesException{
    public:
        InvalidSubtitleLineFormat(const std::string &error, int lines):SubtitlesException("Invalid subtitle line format",lines){}
    };

    class OutOfOrderFrames: public SubtitlesException{
    public:
        OutOfOrderFrames(const std::string &error, int lines):SubtitlesException("Out of order frames",lines){}
    };

    class MissingTimeSpecification: public SubtitlesException{
    public:
        MissingTimeSpecification(const std::string &error, int lines):SubtitlesException("Missing time specification",lines){}
    };
}


#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
