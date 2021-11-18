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

void build_left(char val, BinaryTreeNode<char>* &node) {
    if (node->left == nullptr) {
        BinaryTreeNode<char>* newNode = new BinaryTreeNode<char>(val);
        node->left = newNode;
    }
    node = node->left;
}

void build_right(char val, BinaryTreeNode<char>* &node) {
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
}

std::string decode(std::string line, BinaryTreeNode<char>* root) {
    std::locale loc;
    std::string decoded = "";
    bool sentenceStart;
    BinaryTreeNode<char>* current_node = root;

    for (int i = 0; i < line.length(); i++) {
        if (line.at(i) == '.') current_node = current_node->left;
        else if (line.at(i) == '-') current_node = current_node->right;
        else if (current_node->data != ' ') {
            if (decoded.length() == 0 || decoded.at(decoded.length()-1) == ' ' && decoded.at(decoded.length()-2) == '.') {
                decoded += current_node->data;
            } else {
                decoded += std::tolower(current_node->data, loc);
            }
            current_node = root;
            if (i+1 < line.length() && line.at(i+1) == ' ') decoded += ' ';
        }
    }
    decoded += current_node->data;
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
    std::cout << std::endl;

    file.open("input.txt");
    if (file.fail()) {
        std::cout << "An error occurred";
        return 0;
    }

    while (getline(file, line)) {
        std::cout << "Original: " << line << std::endl;
        std::cout << "Decoded: ";
        std::cout << decode(line, morseTree.getRoot());
        std::cout << std::endl;
    }
    return 0;
}
