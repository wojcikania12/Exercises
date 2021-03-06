//
// Created by Ania Wójcik on 24.04.2018.
//

#ifndef JIMP_EXERCISES_ITERABLE_H
#define JIMP_EXERCISES_ITERABLE_H
#include <vector>
#include<memory>
#include <string>
#include <utility>
namespace utility{
    class IterableIterator {
    public:
    IterableIterator()= default;
        explicit IterableIterator(std::vector<int>::const_iterator left_begin,
        std::vector<std::string>::const_iterator right_begin);
    virtual std::pair<int, std::string> Dereference() const{};
    virtual IterableIterator &Next() {};
    virtual bool NotEquals(const std::unique_ptr<IterableIterator> &other) const {};
    virtual ~IterableIterator() = default;

        std::vector<int>::const_iterator left;
        std::vector<std::string>::const_iterator right;
        std::vector<int>::const_iterator left_end_;
        std::vector<std::string>::const_iterator right_end_;

};


    class IterableIteratorWrapper:public IterableIterator{
    public:
        explicit IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator);
        bool operator!=(const IterableIteratorWrapper &other) const;
        std::pair<int, std::string> operator*() const;
        IterableIteratorWrapper &operator++();

    private:
        std::unique_ptr<IterableIterator> it;

    };


    class Iterable{
    public:
        Iterable() = default;
        ~Iterable() = default;
        virtual std::unique_ptr<IterableIterator> ConstBegin() const {};
        virtual std::unique_ptr<IterableIterator> ConstEnd() const {};
        IterableIteratorWrapper cbegin() const;
        IterableIteratorWrapper cend() const;
        IterableIteratorWrapper begin() const;
        IterableIteratorWrapper end() const;

        std::vector<int> int_;
        std::vector<std::string> string_ ;

    };

    class ZipperIterator:public IterableIterator{
    public:
        ZipperIterator()= default;
        explicit ZipperIterator(std::vector<int>::const_iterator left_begin,
                                std::vector<std::string>::const_iterator right_begin,
                                std::vector<int>::const_iterator left_end,
                                std::vector<std::string>::const_iterator right_end);

        explicit ZipperIterator(std::vector<int>::const_iterator left_,
                                std::vector<std::string>::const_iterator right_);

        std::pair<int, std::string> Dereference() const override ;
        IterableIterator &Next()override;
        bool NotEquals(const std::unique_ptr<IterableIterator> &other)const override ;
        ~ZipperIterator() = default;

    };

    class EnumerateIterator:public IterableIterator {
    public:
        EnumerateIterator() = default;

        explicit EnumerateIterator(std::vector<std::string>::const_iterator string_begin,
                                std::vector<std::string>::const_iterator string_end);

        std::pair<int, std::string> Dereference() const override;

        IterableIterator &Next() override;

        bool NotEquals(const std::unique_ptr<IterableIterator> &other) const override;

        ~EnumerateIterator() = default;
        int temp_index;
    };

    class ProductIterator:public IterableIterator{
    public:
        ProductIterator()= default;

        explicit ProductIterator(std::vector<int>::const_iterator left_,
                                std::vector<std::string>::const_iterator right_);

        std::pair<int, std::string> Dereference() const override ;
        IterableIterator &Next()override;
        bool NotEquals(const std::unique_ptr<IterableIterator> &other)const override ;
        ~ProductIterator() = default;
        std::vector<std::string> ::const_iterator right_copy;

    };

    class Zipper: public Iterable{
    public:
        Zipper(const std::vector<int> &v_int,const std::vector<std::string> &v_str);
        std::unique_ptr<IterableIterator> ConstBegin() const override;
        std::unique_ptr<IterableIterator> ConstEnd() const override;
    };

    class Product: public Iterable{
    public:
        Product(const std::vector<int> &v_int,const std::vector<std::string> &v_str);
        std::unique_ptr<IterableIterator> ConstBegin() const override;
        std::unique_ptr<IterableIterator> ConstEnd() const override;

    };

    class Enumerate: public Iterable{
    public:
        Enumerate(const std::vector<std::string> &v_str);
        std::unique_ptr<IterableIterator> ConstBegin() const override;
        std::unique_ptr<IterableIterator> ConstEnd() const override;

    };
}


#endif //JIMP_EXERCISES_ITERABLE_H
