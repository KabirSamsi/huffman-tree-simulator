#include <iostream>
#include <vector>
#include <chrono>
#include <locale>
#include <string>

using namespace std::chrono;

/**
  @Purpose - function outputs the last fifty words of a sorted vector
  @param words - The sorted vector of words
  @return - None (void)
  @author - Kabir Samsi
**/

void last_fifty(std::vector<std::string> &words) {
    for (int i = words.size()-51; i < words.size(); i++) std::cout << words[i] << " "; //Iterate through last 50 words and print each out
    std::cout << std::endl;
}

/**
  @Purpose - function converts input string to lowercase
  @param input - A string that is to be converted
  @return - A lowercase version of the word
  @author - Kabir Samsi
**/

std::string lower_search(std::string input) {
    std::locale loc;
    std::string lower;
    for (int i = 0; i < input.length(); i++) {
        lower += std::tolower(input[i], loc);
    }
    return lower;
}

/**
  @Purpose - function iterates through a vector of strings and searches for a givecn value
  @param vals - A vector of words to be searched through
  @param search - The string that is being searched
  @return - Time taken to complete the search algorithm
  @author - Kabir Samsi
**/

duration<double> linear_search(std::vector<std::string> vals, std::string search) {
    high_resolution_clock::time_point start = high_resolution_clock::now(); //Time of start

    for (int i = 0; i < vals.size(); i++) { //Iterate through array and search for value
        if (lower_search(vals[i]) == lower_search(search)) {
            std::cout << "This word is at index " << i << std::endl;
            break;
        }
    }
    std::cout << "Word not found" << std::endl;
    high_resolution_clock::time_point finish = high_resolution_clock::now(); //Time of finish
    return duration_cast<duration<double> >(finish - start); //Calculate difference in times
}

/**
  @Purpose - function searches recursively through a sorted vector of words, dividing it into ranges and searching through those
  @param vals - A vector of words to be searched through
  @param search - The string that is being searched
  @param from - The lower bound of the current search range
  @param to - The upper bound of the current search range
  @return - None (Void)
  @author - Kabir Samsi
**/

void binary_search(std::vector<std::string> vals, std::string search, int from, int to) {
    int mid = (from + to) / 2; //Array midpoint

    if (lower_search(vals[mid]) == lower_search(search)) std::cout << "This word is at index " << mid << std::endl; //Value found at midpoint
    else if (from == to) std::cout << "Word not found" << std::endl; //Value not in array

    else if (lower_search(vals[mid]) < lower_search(search)) binary_search(vals, search, mid+1, to); //Value in right half -> recursively search right half
    else binary_search(vals, search, from, mid); //Value in left half -> recursively search left half
}

/**
  @Purpose - function performs Binary Search and times the process
  @param vals - A vector of words to be searched through
  @param search - The string that is being searched
  @return - Time taken to complete the search algorithm
  @author - Kabir Samsi
**/

duration<double> time_binary_search(std::vector<std::string> vals, std::string search) { //Time binary Search
    high_resolution_clock::time_point start = high_resolution_clock::now(); //Time of start

    binary_search(vals, search, 0, vals.size()-1);
    high_resolution_clock::time_point finish = high_resolution_clock::now(); //Time of finish
    return duration_cast<duration<double> >(finish - start); //Calculate difference in times
}

