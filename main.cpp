#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.hpp"
#include "BinaryTree.hpp"

std::string PREFIX = "../";

/**
  @Purpose - Hash a character
  @param c - Data to be appended to the new node
  @return - The hashed version of the character
  @author - Dmitry Pleshkov
**/

int hashChar(char c) {
    return (c*31) % 256;
}

/**
  @Purpose - Encode a plain-text sequence into a morse code sequence
  @param line - The line of text being read
  @param map - The Hashmap cipher of character keywords
  @return - The encoded string
  @author - Kabir Samsi
**/

std::string encode(std::string line, HashMap<char, std::string> map) {
    std::locale loc; //Used to convert to uppercase as needed
    std::string encoded = "";
    char upper;
    for (int i = 0; i < line.length(); i++) { //Iterate through line
        upper = std::toupper(line.at(i), loc);
        if (map.exists(upper)) { //Check if character exists in map
            encoded += map.get(upper).substr(2, map.get(upper).length() - 2); //Add map cipher value of character key
            encoded += ' ';
        } else if (upper == ' ') encoded += ' '; //Add an extra space
    }
    return encoded;
}

/**
  @Purpose - Add a node or traverse to the left of a current node or subtree root
  @param val - Data value of the new node
  @param &node - Reference to the root or current node of the subtree being appended to
  @return - none (void)
  @author - Kabir Samsi
**/

void build_left(char val, BinaryTreeNode<char>* &node) {
    if (node->left == nullptr) { //If there is no node on the left, build one and add it to the left
        BinaryTreeNode<char>* newNode = new BinaryTreeNode<char>(val);
        node->left = newNode;
    }
    node = node->left; //Traverse left
}

/**
  @Purpose - Add a node to the right of a current node or subtree root
  @param val - Data value of the new node
  @param &node - Reference to the root or current node of the subtree being appended to
  @return - none (void)
  @author - Kabir Samsi
**/

void build_right(char val, BinaryTreeNode<char>* &node) {
    if (node->right == nullptr) { //If there is no node on the right, build on and add it to the right
        BinaryTreeNode<char>* newNode = new BinaryTreeNode<char>(val);
        node->right = newNode;
    }
    node = node->right; //Traverse right
}

/**
  @Purpose - Position a given value in a binary tree based on its morse cipher
  @param line - The entire sequence (character and its morse cipher) to be read
  @param root - Root node of the binary tree to append the node to
  @return - none (void)
  @author - Kabir Samsi
**/

void build(std::string line, BinaryTreeNode<char>* root) {
    BinaryTreeNode<char>* current_node = root; //Set current tracker node to traverse tree
    for (int i = 2; i < line.length(); i++) { //Iterate through cipher portion of line (starting at index 2)
        //Dot -> Left, Dash -> Right
        if (line.at(i) == '.') build_left(' ', current_node);
        else if (line.at(i) == '-') build_right(' ', current_node);
    }
    current_node->data = line.at(0); //Set the value to be the starting sequence character (cipher key)
}

/**
  @Purpose - Checks if a line is in morse code or plain text
  @param line - The sequence to be read and encoded/decoded
  @return - Whether line is morse or not
  @author - Kabir Samsi
**/

bool checkMorse(std::string line) {
    for (int i = 0; i < line.length(); i++) {
        //If there are any characters besides dots, dashes and spaces, it is not morse
        if (line[i] != '.' && line[i] != '-' && line[i] != ' ') return false;
    }
    return true;
}

/**
  @Purpose - Read through a morse sequence and decode it to plain text
  @param line - The line to be read and translated
  @param root - Root node of the binary tree to traverse
  @return - Decoded sequence
  @author - Kabir Samsi
**/

std::string decode(std::string line, BinaryTreeNode<char>* root) {
    std::locale loc;
    std::string decoded = "";
    BinaryTreeNode<char>* current_node = root; //Set current tracker node to traverse tree

    for (int i = 0; i < line.length(); i++) { //Iterate through entire line
        //Dot -> Left, Dash -> Right
        if (line.at(i) == '.') current_node = current_node->left;
        else if (line.at(i) == '-') current_node = current_node->right;
        else if (current_node->data != ' ') { //If word ends (don't evaluate blank trees)
            //If word is at the start of the sentence (either start of phrase or preceded by ". "), add capitalized character
            if (decoded.length() == 0) {
                decoded += current_node->data;
            } else if (decoded.length() > 1 && decoded.substr(decoded.length()-2, 2) == ". ") {
                decoded += current_node->data;
            } else { //Otherwise, add lowercase character
                decoded += std::tolower(current_node->data, loc);
            }
            current_node = root; //Reset node to root node
            if (i+1 < line.length() && line.at(i+1) == ' ') decoded += ' '; //Add space if the word ends
        }
    }
    decoded += current_node->data;
    return decoded;
}

/**
  @Purpose - Control most of the operations of the program and call necessary encode/decode methods
  @return - none (void)
  @author - Kabir Samsi
**/

void interface() {
    HashMap<char, std::string> map(hashChar, 30);
    BinaryTree<char> morseTree(' ');
    std::string line;
    std::ifstream file;
    std::string filename;

    file.open(PREFIX+"cipher.txt"); //Open cipher key
    if (file.fail()) {
        std::cout << "An error occurred";
        return;
    }

    while (getline(file, line)) { //Build hashtable and binary tree implementation
        map.set(line[0], line);
        build(line, morseTree.getRoot());
    }
    file.close();

    std::cout << "What file would you like to read? ";
    std::cin >> filename;
    file.open(PREFIX+filename); //Open English input file and encode to Morse Code
    if (file.fail()) {
        std::cout << "An error occurred";
        return;
    }

    while (getline(file, line)) { //Output encoded version
        std::cout << "Original: " << line << std::endl;
        if (checkMorse(line)) {
            std::cout << "Decoded: ";
            std::cout << decode(line, morseTree.getRoot());
            std::cout << std::endl;

        } else {
            std::cout << "Encoded: ";
            std::cout << encode(line, map);
            std::cout << std::endl;
        }
    }
    file.close();
}


/**
  @Purpose - Check if a user wants to view the program
  @param redo - Check if the user wants to  view the program
  @return - Final action (Y/N)
  @author - Kabir Samsi
**/

char checkPlaying(bool redo) {
    char playing;
    //Different message if user is redoing
    if (redo) std::cout << "Would you like to view this again? Y/N: ";
    else std::cout << "Would you like to view our program? Y/N: ";

    std::cin >> playing;
    while (playing != 'Y' && playing != 'N') { //Repeat until user enters a valid command
        std::cout << "Invalid command, Enter Y or N. Please try again: ";
        std::cin >> playing;
    }
    return playing;
}

/**
  @Purpose - Main method controls and calls necessary operations for core program functionality
  @return - 0
  @author - Kabir Samsi
**/

int main() {
    std::string line;
    std::ifstream file;
    std::string name;
    char playing;

    std::cout << "What is your name? "; //User greeting
    getline(std::cin, name);
    std::cout << "Hello " << name << "!" << std::endl;

    file.open(PREFIX+"description.txt"); //Output program description
    if (file.fail()) {
        std::cout << "An error occurred";
        return 0;
    }

    while (getline(file, line)) std::cout << line << std::endl;
    file.close();
    std::cout << "Would you like to view our program? Y/N: ";
    std::cin >> playing;

    while (playing == 'Y') { //Continue program loop while user wants to play
        std::cout << std::endl;
        interface();
        std::cout << "\nWould you like to view this again? Y/N: "; //Repeat loop method
        std::cin >> playing;
    }
    std::cout << "Thanks for checking this out, " << name << "! Goodbye." << std::endl; //Exit message
    return 0;
}
