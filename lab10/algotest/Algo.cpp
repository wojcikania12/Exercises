//
// Created by Ania Wójcik on 16.05.2018.
//

#include "Algo.h"

namespace algo{
    //std::set<std::string> Keys(const std::map<std::string, int> &m);
    //std::vector<int> Values(const std::map<std::string, int> &m);
    //std::map<std::string, int> DivisableBy(const std::map<std::string, int> &m,int divisor);

    void SortInPlace(std::vector<int> *v){
        return std::sort(v->begin(),v->end());
    }
    std::vector<int> Sort(const std::vector<int> &v){
        std::vector<int>temp = v;
        std::sort(temp.begin(),temp.end());
        return temp;
    }
    void SortByFirstInPlace(std::vector<std::pair<int,int>> *v){
        std::sort(v->begin(),v->end(),[](std::pair<int, int> &left, std::pair<int,int>&right){
            return left.first < right.first;
        });
    }
    void SortBySecondInPlace(std::vector<std::pair<int,int>> *v){
        std::sort(v->begin(),v->end(),[](std::pair<int, int> &left, std::pair<int,int>&right){
            return left.second < right.second;
        });
    }   
    void SortByThirdInPlace(std::vector<std::tuple<int,int,int>> *v){
        std::sort(v->begin(),v->end(),[](std::tuple<int, int, int> &left, std::tuple<int,int, int>&right){
            return std::get<2>(left) < std::get<2>(right);
        });
    }
    //std::vector<std::string> MapToString(const std::vector<double> &v);

    //std::string Join(const std::string &joiner, const std::vector<double> &v);
    int Sum(const std::vector<int> &v){
        int temp = std::accumulate(v.begin(),v.end(),0);
        return temp;
    }
    int Product(const std::vector<int> &v){
        int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
        return product;
    }
    bool Contains(const std::vector<int> &v, int element){
        return (std::find(v.begin(), v.end(),element)!= v.end());
    }
    //bool ContainsKey(const std::map<std::string, int> &v, const std::string &key){}
    //bool ContainsValue(const std::map<std::string, int> &v, int value){}

    std::vector<std::string> RemoveDuplicates(const std::vector<std::string> &v){
        std::vector<std::string>temp= v;
        auto temp2 =std::unique(temp.begin(),temp.end());
        temp.erase(temp2,temp.end());
        return temp;
    }
    void RemoveDuplicatesInPlace(std::vector<std::string> *v){
        auto temp = std::unique(v->begin(),v->end());
        v->erase(temp,v->end());
    }
    void InitializeWith(int initial_value, std::vector<int> *v){
        std::fill(v->begin(),v->end(),initial_value);
    }
    std::vector<int> InitializedVectorOfLength(int length, int initial_value){
        std::vector<int>temp;
        std::fill_n(std::back_inserter(temp),length,initial_value);
        return temp;
    }
    void CopyInto(const std::vector<int> &v, int n_elements, std::vector<int> *out){
        std::copy_n(v.begin(),n_elements,std::back_inserter(*out));
    }
    int HowManyShortStrings(const std::vector<std::string> &v, int inclusive_short_length){

    }
}