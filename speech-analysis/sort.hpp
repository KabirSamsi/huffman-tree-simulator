#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <locale>

using namespace std::chrono;

/**
  @Purpose - function converts string to lowercase
  @param input - The input string
  @return - lowercase version of input string
  @author - Kabir Samsi
**/

std::string lower_sort(std::string input) {
    std::locale loc;
    std::string lower;
    for (int i = 0; i < input.length(); i++) {
        lower += std::tolower(input[i], loc);
    }
    return lower;
}

/**
  @Purpose - function swaps pointers to two array elements
  @param x - The first array element
  @param y - The second array element
  @return - None (void)
  @author - Kabir Samsi
**/

void swap(std::string &x, std::string &y) {
    std::string temp = x;
    x = y;
    y = temp;
}

/**
  @Purpose - Function iterates from a given range of an array and finds the smallest value
  @param words - The string vector of words
  @param from - Starting point of vector iteration
  @param to - Ending point of vector iteration
  @return - The index of the smallest value in the range
  @author - Kabir Samsi
**/

int smallest_value(std::vector<std::string> &words, int from, int to) {
    std::locale loc;
    int smallest = from;
    for (int i = from; i <= to; i++) { //Iterate through range and find smallest value
        if (lower_sort(words[i]) < lower_sort(words[smallest])) {
            smallest = i;
        }
    }
    return smallest;
}

/**
  @Purpose - function performs and times Selection Sort on an unsorted vector of parsed and cleaned words
  @param words - The unsorted vector of words that is sorted using the Selection Sort algorithm
  @return - The time period taken to complete the algorithm
  @author - Kabir Samsi
**/

duration<double> selection_sort(std::vector<std::string> &words) {

    high_resolution_clock::time_point start = high_resolution_clock::now(); //Time of start
    int next;
    for (next = 0; next < words.size()-1; next++) {
        int smallest = smallest_value(words, next, words.size()-1); //Find smallest value in shrunk vector range, and swap with current index
        swap(words[next], words[smallest]);
    }
    high_resolution_clock::time_point finish = high_resolution_clock::now(); //Time of finish

    return duration_cast<duration<double> >(finish - start); //Calculate difference in times
}

/**
  @Purpose - function performs and times Bubblesort on an unsorted vector of parsed and cleaned words
  @param words - The unsorted vector of words that is sorted using the Bubblesort algorithm
  @return - The time period taken to complete the algorithm
  @author - Kabir Samsi
**/

duration<double> bubblesort(std::vector<std::string> &words) {
    bool sorted = false;
    int counter = 0;
    std::locale loc;

    high_resolution_clock::time_point start = high_resolution_clock::now(); //Time of start
    while(!sorted) { //Continue iteration until array is sorted
        sorted = true;
        for (int i = 0; i < words.size()-(counter+1); i++) {
            if (lower_sort(words[i]) > lower_sort(words[i+1])) { //If adjacent elements out of order, swap and set array to not sorted
                sorted = false;
                swap(words[i], words[i+1]);
            }
        }
        counter ++;
    }
    high_resolution_clock::time_point finish = high_resolution_clock::now(); //Time of finish
    return duration_cast<duration<double> >(finish - start); //Calculate difference in times
}

/**
  @Purpose - function performs and times Insertion Sort on an unsorted vector of parsed and cleaned words
  @param words - The unsorted vector of words that is sorted using the Insertion Sort algorithm
  @return - The time period taken to complete the algorithm
  @author - Kabir Samsi
**/

duration<double> insertion_sort(std::vector<std::string> &words) {
    std::locale loc;
    high_resolution_clock::time_point start = high_resolution_clock::now(); //Time of start

    for (int i = 1; i < words.size(); i++) {
        std::string current = words[i];
        int j = i; //Element "safety space"

        while (j > 0 && lower_sort(words[j-1]) > lower_sort(current)) { //Iterate backwards until smaller element has been reached, moving all other elements forward
            words[j] = words[j-1];
            j--;
        }
        words[j] = current;
    }
    high_resolution_clock::time_point finish = high_resolution_clock::now(); //Time of finish
    return duration_cast<duration<double> >(finish - start); //Calculate difference in times
}
