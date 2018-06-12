//
// Created by Ania Wójcik on 06.06.2018.
//

#ifndef JIMP_EXERCISES_TREE_H
#define JIMP_EXERCISES_TREE_H
#include <memory>
#include <algorithm>


namespace tree{
    template<class T>
    class Tree{
        public:
        Tree() = default;
        ~Tree() = default;
        Tree(T value_){
            value = value_;
            left = nullptr;
            right = nullptr;
            size = 1;
            depth = 1;
        }
        T Value(){
            return value;
        }
        size_t Size(){
            return size;
        }
        size_t Depth(){
          if(!this){
              return 0;
          }
            return(1+std::max(left->Depth(),right->Depth()));
        }
        bool operator <(T argument)const{
          return *this->value < argument->value;
        }
        void Insert(T new_value){
            size++;
            if(new_value <value){
                if(left == nullptr){
                    auto node = std::make_unique<Tree<T>>(new_value);
                    node -> left = nullptr;
                    node -> right = nullptr;
                    node -> value = new_value;
                    this->left = std::move(node);
                }
                else if(left != nullptr){
                    left -> Insert(new_value);
                }
            }
            else{
                if(right == nullptr){
                    auto node = std::make_unique<Tree<T>>(new_value);
                    node -> left = nullptr;
                    node -> right = nullptr;
                    node -> value = new_value;
                    right = std::move(node);

                }
                else if(right != nullptr){
                    right -> Insert(new_value);
                }
            }
        }

    private:
        T value;
        size_t depth;
        size_t size;
        std::unique_ptr<Tree<T>> left;
        std::unique_ptr<Tree<T>> right;
    };
}

#endif //JIMP_EXERCISES_TREE_H
