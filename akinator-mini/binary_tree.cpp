#include <algorithm>
#include <string>
#include "binary_tree.hpp"

BinaryTree::BinaryTree() { //Initialize empty binary tree
    root = nullptr;
}

BinaryTree::BinaryTree(std::string root_data) { //Initialize tree with a root but no children
   root = new Node;
   root->data = root_data;
   root->left = nullptr;
   root->right = nullptr;
}

BinaryTree::BinaryTree(std::string root_data, BinaryTree left, BinaryTree right) { //Initialize tree with a root and children (left, right)
   root = new Node;
   root->data = root_data;
   root->left = left.root;
   root->right = right.root;
}
   
int BinaryTree::height(const Node* n) const { //Calculate height of a binary tree
   if (n == nullptr) return 0;
   else return 1 + std::max(height(n->left), height(n->right)); //Find maximum height of subtrees
}

int BinaryTree::height() const {return height(root);} //Return the height of a tree

bool BinaryTree::empty() const {return root == nullptr;} //Check if tree is empty

void BinaryTree::changeData(std::string newData) const {root->data = newData;} //Change the data of a tree's root

std::string BinaryTree::data() const {return root->data;} //Return the data of a tree's root
   
void BinaryTree::buildLeft(std::string newVal) { //Build a left subtree given a new value
    BinaryTree newTree(newVal);
    root->left = newTree.root;
}

void BinaryTree::buildRight(std::string newVal) { //Build a right subtree given a new value
    BinaryTree newTree(newVal);
    root->right = newTree.root;
}

BinaryTree BinaryTree::left() const { //Return the left subtree
   BinaryTree result;
   result.root = root->left; 
   return result;
}

BinaryTree BinaryTree::right() const { //Return the right subtree
   BinaryTree result;
   result.root = root->right; 
   return result;
}

void BinaryTree::mutate(std::string newData) { //Mutator method that replaces the current data with a new data
    root->data = newData;
}