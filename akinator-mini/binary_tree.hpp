#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>

class Node { //Node class representing the values in a binary tree
    private:
        std::string data;
        Node* left;
        Node* right;
        friend class BinaryTree;
};

class BinaryTree { //Binary tree consisting of nodes with at most two children
    public:
        BinaryTree(); //Constructs an empty tree.
        BinaryTree(std::string root_data); //Constructs a tree with one node and no children
        BinaryTree(std::string root_data, BinaryTree left, BinaryTree right); //Tree with a value and two children
        int height() const; //Returns height of tree
        bool empty() const; //Returns whether tree is empty or not
        std::string data() const; //Returns the data in a tree
        void changeData(std::string newData) const; //Changes the data in a node
        void buildLeft(std::string newData); //Build a left subtree given new data input
        void buildRight(std::string newData); //Build a right subtree given new data input
        BinaryTree left() const; //Trace left subtree
        BinaryTree right() const; //Trace right subtree
        void mutate(std::string newData); //Replace the current node's data with new input

    private:
        int height(const Node* n) const; //Returns height of a subtree
        Node* root; //The root value of the tre
};

#endif