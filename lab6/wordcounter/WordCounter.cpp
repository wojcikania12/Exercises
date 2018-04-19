//
// Created by Ania Wójcik on 19.04.2018.
//


#include "WordCounter.h"

namespace datastructures{


    // Word
    Word:: ~Word(){
        searched ="";
    }

    bool Word::operator<(const Word &word) const {
        return (searched < word.searched);
    }
    Word::Word(std::string str) {
        searched = str;
    }

    std::string Word::GetWord()const{
        return searched;
    }
    bool Word::operator ==(const Word &word) const{
        return(searched == word.searched);
    }



    // Counts
    Counts::Counts(){
        counts = 0;
    }
    Counts::~Counts(){}

    Counts::Counts(int number) {
        counts = number;
    }

    Counts::operator int() const {
        return counts;
    }


    int Counts::GetCounts(){
        return counts;
    }

    bool Counts::operator==(const int &counts_) const{
        return (counts == counts_);
    }

    bool Counts::operator==(const Counts &counts_) const {
        return (counts == counts_.counts);
    }

    bool Counts::operator<(const Counts &counts_) const {
        return (counts < counts_.counts);
    }

    bool Counts::operator>(const Counts &counts_) const {
        return (counts > counts_.counts);
    }

    Counts &Counts::operator++() {
        counts++;
    }
    Counts &Counts::operator+=(int counts_){
        counts += counts_;
    }



    //WordCounter


    WordCounter::WordCounter(){}

    std::ostream & operator <<(std::ostream &out_stream, WordCounter & word_counter){
        out_stream << "Number of words: " << word_counter.words_list.size() << std::endl;
        out_stream <<"Lists of words :" <<std::endl;
        for(auto i : word_counter.words_list){
            out_stream << i.first.GetWord() << " " << i.second.GetCounts() << std::endl;
        }
        return out_stream;
    }


    WordCounter::WordCounter(std::initializer_list<Word> list) {
        bool found = false;
        for( auto i : list){
            for(auto j : words_list){
                if(i == j.first){
                    ++j.second.counts;
                    found = true;
                    break;
                }
            }
            if(not found) {
                Counts k_ = 1;
                words_list.push_back(std::make_pair(i, k_));
            }
            found = false;

        }

    }


    int WordCounter::DistinctWords() {
       distinct =0;
        for (const auto &i :words_list) {
            ++distinct;
        }
        return distinct;
    }

    int WordCounter::TotalWords() {
        total =0;
        for (auto i :words_list) {
            total += i.second.counts;
        }
        return total;
    }

    Counts WordCounter::operator[](std::string word) {
        bool flag = false;
        for (auto i : words_list) {
            if (i.first.searched == word) {
                return i.second.counts;
            }
        }
        return 0;

    }

    WordCounter WordCounter::FromInputStream(std::istream &input) {
        WordCounter output;
        char char_;
        bool found = false;
        while(input.get(char_)) {
            std::string temp_word = "";
            if (isalpha(char_)) {
                temp_word += char_;
            } else if (char_ == ' ') {
                for (auto i : output.words_list) {
                    if (i.first.searched == temp_word) {
                        ++i.second;
                        found = true;
                        break;
                    }
                }
                if (not found) {
                    Word w_(temp_word);
                    Counts c_(1);
                    output.words_list.push_back(std::make_pair(w_, c_));
                }
            }
        }
        return output;
    }

    std::set<Word> WordCounter::Words() {
        std::set <Word> temp;
        for(auto i : words_list){
            temp.insert(i.first);
        }
        return temp;
    }
}

