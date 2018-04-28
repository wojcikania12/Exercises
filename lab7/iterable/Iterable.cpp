//
// Created by Ania Wójcik on 24.04.2018.
//

#include "Iterable.h"

namespace utility {

    //ZipperIterator
    ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left_begin,
                                   std::vector<std::string>::const_iterator right_begin,
                                   std::vector<int>::const_iterator left_end,
                                   std::vector<std::string>::const_iterator right_end){
        left = left_begin;
        right = right_begin;
        right_end_ = right_end;
        left_end_ = left_end;
    }

    std::pair<int, std::string> ZipperIterator::Dereference() const {
        if(left == left_end_ && right== right_end_){
            return (std::make_pair(*(left-1),*(right-1)));
        }
        else if(left == left_end_ && right!= right_end_) {
            return (std::make_pair(*(left-1),*right));
        }
        else if(left != left_end_ && right== right_end_) {
            return (std::make_pair(*left,*(right-1)));
        }
        else{
            return (std::make_pair(*left,*right));
        }
    }

    IterableIterator & ZipperIterator::Next()  {
        if(left != left_end_){
            ++left;
        }
        else if(left == left_end_){
            --left;
        }
        if(right != right_end_){
            ++right;
        }
        else{
            --right;
        }

        return *this;
    }

    bool ZipperIterator::NotEquals(const std::unique_ptr<IterableIterator> &other) const {
        return !(left == other->left && right == other->right && left_end_ == other->left_end_ && right_end_//
     == other->right_end_);
    }

    ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left_,
                                   std::vector<std::string>::const_iterator right_) : IterableIterator(left_, right_) {
        left = left_;
        right = right_;
    }

    //IterableIteratorWrapper

    IterableIteratorWrapper::IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator){
        it = move(iterator);
    }

    bool IterableIteratorWrapper::operator!=(const IterableIteratorWrapper &other) const{
        bool result = it->NotEquals(other.it);
        return result;
    }
    std::pair<int, std::string> IterableIteratorWrapper::operator*() const{
        return it -> Dereference();
    }
   IterableIteratorWrapper &IterableIteratorWrapper::operator++(){
        it -> Next();
       return *this;
    }

    //Iterator

    IterableIteratorWrapper Iterable::cbegin() const{
        return IterableIteratorWrapper(move(ConstBegin()));
    }
    IterableIteratorWrapper Iterable::cend() const{
        return IterableIteratorWrapper(move(ConstEnd()));
    }
    IterableIteratorWrapper Iterable::begin() const{
        return cbegin();
    }
    IterableIteratorWrapper Iterable::end() const{
        return cend();
    }

    IterableIterator::IterableIterator(std::vector<int>::const_iterator left_begin,
    std::vector<std::string>::const_iterator right_begin){
        left =left_begin;
        right =right_begin;
    }

    //Zipper

    Zipper::Zipper(const std::vector<int>& v_int, const std::vector<std::string>& v_str){
        int_= v_int;
        string_ = v_str;
        size_t v_int_size = int_.size();
        size_t v_str_size = string_.size();
        if(v_int_size > v_str_size) {
            for (size_t i = v_str_size; i < v_int_size; ++i) {
                string_.push_back(string_[v_str_size-1]);
            }
        }
            else{
            for(size_t j = v_int_size; j < v_str_size; ++j){
                int_.push_back(int_[v_int_size-1]);
            }
        }
    }
    std::unique_ptr<IterableIterator> Zipper::ConstBegin() const {
        auto ptr= std::make_unique<ZipperIterator>(ZipperIterator(int_.begin(),string_.begin()));
        return std::move(ptr);
    }
    std::unique_ptr<IterableIterator> Zipper::ConstEnd() const {
        auto ptr= std::make_unique<IterableIterator>(IterableIterator(int_.end(),string_.end()));
        return std::move(ptr);
    }

    //ProductIterator

    ProductIterator::ProductIterator(std::vector<int>::const_iterator left_begin,
    std::vector<std::string>::const_iterator right_begin,
            std::vector<int>::const_iterator left_end,
    std::vector<std::string>::const_iterator right_end){
        left = left_begin;
        right = right_begin;
        right_end_ = right_end;
        left_end_ = left_end;
    }

    ProductIterator::ProductIterator(std::vector<int>::const_iterator left_,
    std::vector<std::string>::const_iterator right_){
        left = left_;
        right = right_;
    }

    std::pair<int, std::string> ProductIterator::Dereference() const {
        return (std::make_pair(*left,*right));
    };

    IterableIterator & ProductIterator::Next(){
        ++left;
        ++right;
        return* this;
    }

    bool ProductIterator::NotEquals(const std::unique_ptr<IterableIterator> &other)const {
        return !(left == other->left && right == other->right && left_end_ == other->left_end_ && right_end_//
                                                                                        == other->right_end_);
    }

    //Product

    Product::Product(const std::vector<int>& v_int, const std::vector<std::string>& v_str){
        for(auto i : v_int){
            for(auto j :v_str){
                string_.emplace_back(j);
                int_.emplace_back(i);
            }
        }
    }
    std::unique_ptr<IterableIterator> Product::ConstBegin() const {
        auto ptr= std::make_unique<ProductIterator>(ProductIterator(int_.begin(),string_.begin()));
        return std::move(ptr);
    }
    std::unique_ptr<IterableIterator> Product::ConstEnd() const {
        auto ptr= std::make_unique<ProductIterator>(ProductIterator(int_.end(),string_.end()));
        return std::move(ptr);
    }

    //Enumerate

    Enumerate::Enumerate(const std::vector<std::string> &v_str){
       string_=v_str;

    }
    std::unique_ptr<IterableIterator> Enumerate::ConstBegin() const {
        auto ptr= std::make_unique<EnumerateIterator>(EnumerateIterator(string_.begin(),string_.end()));
        return std::move(ptr);
    }
    std::unique_ptr<IterableIterator> Enumerate::ConstEnd() const {
        auto ptr= std::make_unique<EnumerateIterator>(EnumerateIterator(string_. end(),string_.end()));
        return std::move(ptr);
    }

    //EnumerateIterator
   EnumerateIterator::EnumerateIterator(std::vector<std::string>::const_iterator string_begin,
    std::vector<std::string>::const_iterator string_end){
       right = string_begin;
       right_end_ = string_end;
       temp_index =1;
   }

    std::pair<int, std::string> EnumerateIterator::Dereference() const{
        return (std::make_pair(temp_index,*right));
    }

    IterableIterator & EnumerateIterator::Next(){
        if(right != right_end_){
            ++temp_index;
            ++right;
        }
        return *this;
    }

    bool EnumerateIterator::NotEquals(const std::unique_ptr<IterableIterator> &other) const{
        return !(right == other->right && right_end_ == other->right_end_);
    }



}