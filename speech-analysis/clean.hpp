#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <locale>

/**
  @Purpose - function converts string to lowercase
  @param input - The input string
  @return - lowercase version of input string
  @author - Kabir Samsi
**/

std::string lower_clean(std::string input) {
    std::locale loc;
    std::string lower;
    for (int i = 0; i < input.length(); i++) {
        lower += std::tolower(input[i], loc);
    }
    return lower;
}

/**
  @Purpose - function takes string as input, converts it to lowercase and then removes all non-alpha values
  @param input - A formatted string containing forms of punctuation and uppercase chars
  @return - a fully lowercase, all-punctuation-removed string
  @author - Kabir Samsi
**/

std::string clean_string(std::string input) {
    std::string converted = "";

    for (int i = 0; i < input.length(); i++) {
        if (isalpha(input[i])) converted += input[i];
    }
    return converted;
}

/**
  @Purpose - function iterates through an array in search of a given word, returning true if found and false if not
  @param value - A string that is being searched for within a larger array
  @param arr - A string array containing all values that are being searched for
  @return - a boolean value demonstrating whether the given string element is in the array or not
  @author - Kabir Samsi
**/

bool word_in_arr(std::string value, const std::string arr[]) {
    for (int i = 0; i < sizeof(arr); i++) { //Iterate through array and check if value is included
        if (lower_clean(arr[i]) == lower_clean(value)) return true;
    }
    return false;
}

/**
  @Purpose - function opens a text file, parses out all of its words, deformats them and adds them to an unsorted vector
  @param filename - The name of the file that needs to be opened
  @return - a vector containing all deformatted strings extracted from the file
  @author - Kabir Samsi
**/

std::vector<std::string> parseFillers(const std::string filename) {
    //Declare filler array and word vector
    const std::string fillers[] = {"a", "an", "the", "", " "};
    std::vector<std::string> parsedWords;

    //Open filestream and test for opening error
    std::ifstream input_file;
    input_file.open(filename);
    if (input_file.fail()) return parsedWords;

    //Deformat words and add to unsorted vector
    std::string word;
    while (input_file >> word) {
        if (!word_in_arr(clean_string(word), fillers)) {
            parsedWords.push_back(clean_string(word));
        }
    }

    //Close file and return vector
    input_file.close();
    return parsedWords;
}