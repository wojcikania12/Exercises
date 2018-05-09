//
// Created by Ania Wójcik on 01.05.2018.
//

#include "MovieSubtitles.h"

namespace moviesubs {

    int MicroDvdSubtitles::Change_Frames(const int &offset_in_micro_seconds, const int &frames_per_second,
                                         const int &actual_frame) {
        int temp = actual_frame + offset_in_micro_seconds * frames_per_second / 1000;
        return temp;
    }


    void MicroDvdSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                                std::ostream *out) {
        int first_frame, last_frame, lines = 0;
        std::regex pattern{R"(^\{(\d+)\}\{(\d+)\}(.*)$)"};
        std::smatch my_match;
        std::string subtitles;
        if (0 > frame_per_second) {
            throw NegativeFrameAfterShift(subtitles, lines);
        }
        while (getline(*in, subtitles)) {
            if (regex_search(subtitles, my_match, pattern)) {
                ++lines;
                first_frame = Change_Frames(offset_in_micro_seconds, frame_per_second, std::stoi(my_match[1]));
                last_frame = Change_Frames(offset_in_micro_seconds, frame_per_second, std::stoi(my_match[2]));
                if (0 > first_frame || 0 > last_frame) {
                    throw NegativeFrameAfterShift(subtitles, lines);
                }
                if (first_frame > last_frame) {
                    throw SubtitleEndBeforeStart(lines, subtitles);
                }
                *out << "{" << std::to_string(first_frame) << "}"<< "{" << std::to_string(last_frame) << "}"
                     << my_match[3] << '\n';
            } else {
                throw InvalidSubtitleLineFormat("Invalid subtitle line format", lines);
            }
        }
    }

    //SubRip

    int SubRipSubtitles::Change_To_Microseconds(const std::string &hours, const std::string &minutes,
                                                const std::string &seconds, const std::string &microseconds) {
        int temp;
        temp = std::stoi(hours) * 60 * 60 * 1000 + std::stoi(minutes) * 60 * 1000 + std::stoi(seconds) * 1000 +
               std::stoi(microseconds);
        return temp;
    }

    std::string SubRipSubtitles::Change_Time_Format(const int &time) {
        std::string hours, minutes, seconds, microseconds, result;
        int rest = time, temp;
        temp = rest / (3600 * 1000);
        hours = std::to_string(temp);
        rest %= 3600 * 1000;
        if (hours.size() < 2) {
            hours = "0" + hours;
        }
        temp = rest / (60 * 1000);
        minutes = std::to_string(temp);
        rest %= (60 * 1000);
        if (minutes.size() < 2) {
            minutes = "0" + minutes;
        }
        temp = rest / 1000;
        seconds = std::to_string(temp);
        rest %= 1000;
        if (seconds.size() < 2) {
            seconds = "0" + seconds;
        }
        microseconds = std::to_string(rest);
        if (microseconds.size() == 1) {
            microseconds = "00" + microseconds;
        } else if (microseconds.size() == 2) {
            microseconds = "0" + microseconds;
        }
        result = hours + ":" + minutes + ":" + seconds + "," + microseconds;
        return result;
    }

    void SubRipSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second,
                                              std::istream *in, std::ostream *out) {
        int start_ms, end_ms, lines = 1;
        std::string start_time, end_time, sub;
        std::regex pattern{R"((\d{2}):(\d{2}):(\d{2}),(\d{3}) --> (\d{2}):(\d{2}):(\d{2}),(\d{3}))"};
        std::smatch my_match;
        std::string subtitles;
        if (0 > frame_per_second) {
            throw NegativeFrameAfterShift(subtitles, lines);
        }
        while (getline(*in, subtitles)) {
            if (std::regex_search(subtitles, my_match, pattern)) {
                    start_ms = Change_To_Microseconds(my_match[1], my_match[2], my_match[3], my_match[4]);
                    end_ms = Change_To_Microseconds(my_match[5], my_match[6], my_match[7], my_match[8]);
                    start_time = Change_Time_Format(start_ms + offset_in_micro_seconds);
                    end_time = Change_Time_Format(end_ms + offset_in_micro_seconds);
                    if (0 > end_ms + offset_in_micro_seconds || 0 > start_ms + offset_in_micro_seconds) {
                        throw NegativeFrameAfterShift(subtitles, lines);
                    }
                    if (start_ms > end_ms) {
                        throw SubtitleEndBeforeStart(lines, Change_Time_Format(start_ms) + " --> " +
                                                            Change_Time_Format(end_ms));
                    }
                    *out << lines << "\n" << start_time << " --> " << end_time << "\n";
                ++lines;
                getline(*in, sub);
                while (true) {
                        if (sub == "") {
                            *out << "\n";
                            break;
                        } else {
                            *out << sub << "\n";
                        }
                        getline(*in, sub);

                    }
                }
            }
            }
            }






