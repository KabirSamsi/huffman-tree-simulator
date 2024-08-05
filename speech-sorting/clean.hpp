#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <locale>

/**
  @Purpose - function takes string as input, converts it to lowercase and then removes all non-alpha values
  @param input - A formatted string containing forms of punctuation and uppercase chars
  @return - a fully lowercase, all-punctuation-removed string
  @author - Kabir Samsi
**/

std::string clean_string(std::string input) {
    std::string converted = "";

    for (int i = 0; i < input.length(); i++) {
        if (isalpha(input[i]) || input[i] == '\'' || input[i] == '-') converted += input[i];
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

bool word_in_arr(std::string value, std::string arr[]) {
    for (int i = 0; i < sizeof(arr); i++) { //Iterate through array and check if value is included
        if (arr[i] == value) return true;
    }
    return false;
}

/**
  @Purpose - function opens a series of text file, parses out all of its words, deformats them and adds them to an unsorted vector
  @param files - The names of the files that need to be opened
  @return - a vector containing all deformatted strings extracted from the file
  @author - Kabir Samsi
**/

std::vector<std::string> parseFillers(std::string files[]) {
    //Declare filler array and word vector
    std::string fillers[] = {"a", "an", "the", "A", "An", "The", "", " "};
    std::vector<std::string> parsedWords;

    //Open each filestream and test for opening error
    std::string file;
    for (int i = 0; i < sizeof(files); i++) {
        file = files[i];
        std::ifstream input_file;
        input_file.open(file);
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
    }
    return parsedWords;
}