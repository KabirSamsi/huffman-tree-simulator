#include <iostream>
#include <string>

struct Node { //Struct definition for a binary tree node
    char val;  
    Node* left; //Left pointer
    Node* right; //Right pointer
};

/**
  @Purpose - Build a left subtree given a new value
  @param current - The current tree node
  @param newVal - Character value of the new node's data
  @return - None (void)
  @author - Kabir Samsi
**/

void buildLeft(Node* current, char newVal) {
    Node* newNode = new Node;
    newNode->val = newVal;
    current->left = newNode; //Set new node to current's left pointer
}

/**
  @Purpose - Build a right  subtree given a new value
  @param current - The current tree node
  @param newVal - Character value of the new node's data
  @return - None (void)
  @author - Kabir Samsi
**/

void buildRight(Node* current, char newVal) { //Build a left subtree given a new value
    Node* newNode = new Node;
    newNode->val = newVal;
    current->right = newNode; //Set new node to current's right pointer
}

/**
  @Purpose - Position a character in a binary tree given a morse code sequence
  @param root - The root node of the binary tree
  @param newVal - Character value of the new node
  @param path - The morse path to follow for this character
  @return - None (void)
  @author - Kabir Samsi
**/

void build(Node* root, char newVal, std::string path) {
    Node* current = root; //Track current node
    for (int i = 2; i < path.length(); i++) { //Start at the third character (beginning of morse sequence)
        if (path[i] == '.') {
            if (current->left == nullptr) buildLeft(current, ' '); //Short -> traverse left
            current = current->left;
        } else if (path[i] == '-') {
            if (current->right == nullptr) buildRight(current, ' '); //Long -> traverse right
            current = current->right;
        }
    }
    current->val = newVal; //Set the final new node to the new value
}

/**
  @Purpose - Inorder traversal of a binary tree
  @param root - The root node of the binary tree
  @return - None (void)
  @author - Kabir Samsi
**/

void inorder(Node* root) {
    if (root == nullptr) return; //Base case
    inorder(root->left); //Traverse the left subtree
    std::cout << root->val;
    inorder(root->right); //Traverse the right subtree
}

/**
  @Purpose - Find the number of nodes in a binary tree
  @param root - The root node of the binary tree
  @return - Number of nodes in the tree
  @author - Kabir Samsi
**/

int size(Node* root) {
    if (root == nullptr) return 0; //Base case
    return 1 + (size(root->left) + size(root->right)); //Calculate the sum of the two smaller subtrees
}
