#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.hpp"
#include "BinaryTree.hpp"

int hashChar(char c) {
    return (c*31) % 256;
}

std::string encode(std::string line, HashMap<char, std::string> map) {
    std::locale loc;
    std::string encoded = "";
    char upper;
    for (int i = 0; i < line.length(); i++) {
        upper = std::toupper(line.at(i), loc);
        if (map.exists(upper)) {
            encoded += map.get(upper).substr(2, map.get(upper).length() - 2);
            encoded += ' ';
        } else if (upper == ' ') encoded += ' ';
    }
    return encoded;
}

void build_left(char val, BinaryTreeNode<char>* node) {
    if (node->left == nullptr) {
        BinaryTreeNode<char>* newNode = new BinaryTreeNode<char>(val);
        node->left = newNode;
    }
    node = node->left;
}

void build_right(char val, BinaryTreeNode<char>* node) {
    if (node->right == nullptr) {
        BinaryTreeNode<char>* newNode = new BinaryTreeNode<char>(val);
        node->right = newNode;
    }
    node = node->right;
}

void build(std::string line, BinaryTreeNode<char>* root) {
    BinaryTreeNode<char>* current_node = root;
    for (int i = 2; i < line.length(); i++) {
        if (line.at(i) == '.') build_left(' ', current_node);
        else if (line.at(i) == '-') build_right(' ', current_node);
    }
    current_node->data = line.at(0);
    std::cout << root->data << " " << current_node->data << std::endl;
}

std::string decode(std::string line, BinaryTree<char> tree) {
    std::locale loc;
    std::string decoded = "";
    BinaryTreeNode<char>* current_node = tree.getRoot();

    for (int i = 0; i < line.length(); i++) {
        if (line.at(i) == '.') current_node = current_node->left;
        else if (line.at(i) == '-') current_node = current_node->right;
        else {
            decoded += current_node->data;
            current_node = tree.getRoot();
            if (i+1 < line.length() && line.at(i+1) == ' ') decoded += ' ';
        }
    }
    return decoded;
}

void inorder(BinaryTreeNode<char>* node) {
    if (node == nullptr) return;
    inorder(node->left);
    std::cout << node->data;
    inorder(node->right);
}

int main() {
    HashMap<char, std::string> map(hashChar, 31);
    BinaryTree<char> morseTree(' ');
    std::string line;
    std::ifstream file;
    
    //Open cipher key and build hashmap
    file.open("cipher.txt");
    if (file.fail()) {
        std::cout << "An error occurred";
        return 0;
    }

    while (getline(file, line)) {
        map.set(line[0], line);
        build(line, morseTree.getRoot());
    }
    file.close();
    std::cout << morseTree.height() << std::endl;
    // inorder(morseTree.getRoot());

    //map.set('|', line);
    //Open other input file and translate
    file.open("english.txt");
        if (file.fail()) {
        std::cout << "An error occurred";
        return 0;
    }

    while (getline(file, line)) {
        std::cout << "Original: " << line << std::endl;
        std::cout << "Encoded: ";
        std::cout << encode(line, map);
        std::cout << std::endl;
    }
    file.close();
    return 0;
}
