//
// Created by Ania Wójcik on 19.04.2018.
//

#ifndef JIMP_EXERCISES_WORDCOUNTER_H
#define JIMP_EXERCISES_WORDCOUNTER_H



#include <iostream>
#include <set>
#include <vector>
#include <initializer_list>
#include <string>


namespace datastructures {
    class Word {
    public:
        friend class WordCounter;
        Word();
        ~Word();
        bool operator ==(const Word &word) const;

        Word(std::string str);
        bool operator<(const Word& word) const;

        std::string GetWord() const;
    private:
        std::string searched;

    };

    class Counts{
    public:
        friend class WordCounter;
        Counts();
        ~Counts();
        Counts(int number);

        operator int() const ;
        bool operator==(const int &counts_) const;
        bool operator==(const Counts &counts_) const;
        bool operator<(const Counts &counts_) const;
        bool operator>(const Counts &counts_) const;
        Counts & operator++();
        Counts & operator+=(int counts_);
        int GetCounts();


    private:
        int counts;
    };

    class WordCounter{
    public:
        WordCounter();
        WordCounter(std::initializer_list<Word> words);

        int DistinctWords();
        int TotalWords();
        Counts operator [](std::string word);
        static WordCounter FromInputStream(std::istream &input);
        friend std::ostream &operator<<(std::ostream &out_stream, WordCounter & word_counter);
        std::set <Word> Words();
    private:
        int distinct ;
        int total ;
        std::vector<std::pair<Word,Counts>> words_list;


    };

}



#endif //JIMP_EXERCISES_WORDCOUNTER_H
