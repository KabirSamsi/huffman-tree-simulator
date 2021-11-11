#include <iostream>
#include <string>

struct Node {
    char val;  
    Node* left;
    Node* right;
};

void buildLeft(Node* current, char newVal) { //Build a left subtree given a new value
    Node* newNode = new Node;
    newNode->val = newVal;
    current->left = newNode;
}

void buildRight(Node* current, char newVal) { //Build a left subtree given a new value
    Node* newNode = new Node;
    newNode->val = newVal;
    current->right = newNode;
}

void build(Node* root, char newVal, std::string path) {
    Node* current = root;
    for (int i = 2; i < path.length(); i++) {
        if (path[i] == '.') {
            if (current->left == nullptr) buildLeft(current, ' ');
            current = current->left;
        } else if (path[i] == '-') {
            if (current->right == nullptr) buildRight(current, ' ');
            current = current->right;
        }
    }
    current->val = newVal;
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    std::cout << root->val;
    inorder(root->right);
}

int size(Node* root) {
    if (root == nullptr) return 0;
    return 1 + (size(root->left) + size(root->right));
}
