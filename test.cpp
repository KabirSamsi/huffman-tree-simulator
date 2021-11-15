#include <iostream>
#include "HashMap.hpp"

int hashChar(char c) {
    return (c*31) % 256;
}

int main() {
    HashMap<char, std::string> map(hashChar, 30);
    map.set('a', "apple");
    map.set('b', "banana");
    std::cout << map.exists('a') << std::endl;
    std::cout << map.get('b') << std::endl;
    map.remove('a');
    std::cout << map.exists('a');
}