#include <iostream>
#include <fstream>
#include <string>
#include "binary_tree.hpp"

/**
  @Purpose - Unscramble a morse code sequence into an English string
  @param morseTree - The starting node of the morse code binary tree
  @param morse - The morse code sequence
  @return - The unscrambled string
  @author - Kabir Samsi
**/

std::string unscramble(Node* morseTree, std::string morse) {
    Node* current = morseTree; //Track current node
    std::string result = "";
    std::cout << "Original: " << morse << std::endl << "Unscrambled: ";

    for (int i = 0; i <= morse.length(); i++) { //Iterate through each element
        switch(morse[i]) {
            case '.': //Short -> traverse left
                if (current->left != nullptr) current = current->left;
                break;

            case '-': //Long -> traverse right
                if (current->right != nullptr) current = current->right;
                break;

            default: //If space is encountered
                if (current != nullptr && current->val != ' ') { //If value is not an empty node, add to result string
                    result += current->val;
                    if (morse[i] < morse.length() && morse[i+1] == ' ') result += ' '; //Add space if double-space encountered
                }
                current = morseTree; //Reset current node to the root node
                break;
        }
    }
    return result;
    delete current;
}

/**
  @Purpose - Execute main method
  @return - 0
  @author - Kabir Samsi
**/

int main() {
    Node* morseTree = new Node; //Declare root of morse binary tree
    std::string line;
    std::ifstream file;
    
    //Open cipher key and build binary tree
    morseTree->val = ' ';
    file.open("cipher.txt");
    while (getline(file, line)) build(morseTree, line[0], line);
    file.close();

    //Open input file and translate
    file.open("input.txt");
    while (getline(file, line)) std::cout << unscramble(morseTree, line);
    std::cout << std::endl;
    return 0;
}
