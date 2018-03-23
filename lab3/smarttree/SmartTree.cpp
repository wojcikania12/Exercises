//
// Created by Ania Wójcik on 22.03.2018.
//

#include "SmartTree.h"

namespace datastructures {
    std::unique_ptr<SmartTree> CreateLeaf(int value) {
        std::unique_ptr<SmartTree> leaf = std::make_unique<SmartTree>();
        leaf->value = value;
        return leaf;
    }

    std::unique_ptr<SmartTree>
    InsertLeftChild(std::unique_ptr<SmartTree> tree, std::unique_ptr<SmartTree> left_subtree) {
        auto node = std::make_unique<SmartTree>();
        node = move(tree);
        node -> left = move(left_subtree);
        return node;
    }


    std::unique_ptr<SmartTree>
    InsertRightChild(std::unique_ptr<SmartTree> tree, std::unique_ptr<SmartTree> right_subtree) {
        auto node = std::make_unique<SmartTree>();
        node = move(tree);
        node -> right = move(right_subtree);
        return node;
    }

    void PrintTreeInOrder(const std::unique_ptr<SmartTree> &unique_ptr, std::ostream *out) {
        std::unique_ptr<SmartTree> node = std::make_unique<SmartTree>();
        if (unique_ptr == nullptr) return;
        else {
            if (unique_ptr->left != nullptr) {
                PrintTreeInOrder(unique_ptr->left, out);
            }
            *out << unique_ptr->value << ", ";
            if (unique_ptr->right != nullptr) {
                PrintTreeInOrder(unique_ptr->right, out);

            }
        }
    }

    std::string DumpTree(const std::unique_ptr<SmartTree> &tree) {
        std::string output="[";
        int value;
        value=tree->value;
        output=output+std::to_string(value);
        if(tree->left!=nullptr){
            output = output + " " + DumpTree(tree->left);
        }else{
            output = output + " [none]";
        }
        if(tree->right!=nullptr){
            output = output + " " + DumpTree(tree->right);
        }else{
            output=output+" [none]";
        }
        return output + "]";
    }

    std::unique_ptr<SmartTree> RestoreTree(const std::string &tree){}


    int FindIndex(int first, int last, std::string tree) {
        int index;
        std::stack<char> parenthesis;
        for (auto i : tree) {
            if (i == '[') {
                parenthesis.push(i);
            } else if (i == ']') {
                if (parenthesis.top() == '[') {
                    parenthesis.pop();
                    if (parenthesis.empty()) {
                        index = i;
                        break;
                    }
                }
            }
        }
        return index;
    }


}



