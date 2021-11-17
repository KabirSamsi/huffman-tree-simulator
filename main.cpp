#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.hpp"

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

int main() {
    HashMap<char, std::string> map(hashChar, 31);
    std::string line;
    std::ifstream file;
    
    //Open cipher key and build hashmap
    file.open("cipher.txt");
    while (getline(file, line)) {
        map.set(line[0], line);
    }
    file.close();

    //Open other input file and translate
    file.open("english.txt");
    while (getline(file, line)) std::cout << encode(line, map);
    std::cout << std::endl;
    file.close();

    return 0;
}
