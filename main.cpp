#include <iostream>
#include <fstream>
#include <string>
#include "binary_tree.hpp"

std::string unscramble(Node* morseTree, std::string morse) {
    Node* current = morseTree;
    std::string result = "";
    std::cout << "Original: " << morse << std::endl << "Unscrambled: ";

    for (int i = 0; i <= morse.length(); i++) {
        switch(morse[i]) {
            case '.':
                if (current->left != nullptr) current = current->left;
                break;

            case '-':
                if (current->right != nullptr) current = current->right;
                break;

            default:
                if (current != nullptr && current->val != ' ') {
                    result += current->val;
                    if (morse[i] < morse.length() && morse[i+1] == ' ') result += ' ';
                }
                current = morseTree;
                break;
        }
    }
    return result;
}

int main() {
    Node* morseTree = new Node;
    std::string line;
    std::ifstream file;
    
    morseTree->val = ' ';
    file.open("cipher.txt");
    while (getline(file, line)) build(morseTree, line[0], line);
    file.close();

    file.open("input.txt");
    while (getline(file, line)) std::cout << unscramble(morseTree, line);
    std::cout << std::endl;
    return 0;
}
