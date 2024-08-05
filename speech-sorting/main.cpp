#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "clean.hpp"
#include "sort.hpp"
#include "search.hpp"

/**
  @Purpose - function sums up and calculates the averag timings for an array of times
  @param times - Array of timings with sort algorithms on vectors
  @return - The average duration for a series of times
  @author - Kabir Samsi
**/

double average_time(double times[]) {
    double total;
    for (int i = 0; i < sizeof(times); i++) total += times[i]; //Add up all times
    total /= sizeof(times); //Divide total by number of 
}

/**
  @Purpose - function accepts two arrays of timings, and outputs them in tabular format
  @param sorted - Array of timings for sort algorithms on sorted vectors
  @param unsorted - Array of timings with sort algorithms on unsorted vectors
  @return - None (void)
  @author - Kabir Samsi
**/

void print_table(std::string algo_type, double unsorted[], double sorted[]) {
    double average_unsorted = average_time(unsorted);
    double average_sorted = average_time(sorted);
    char separator = ' ';
    int width = 20;

    std::cout << algo_type << std::setw(width) << std::setfill(separator) << "Unsorted" << std::setw(width) << std::setfill(separator) << "Sorted" << std::setw(width) << std::setfill(separator) << std::endl;

    for (int i = 0; i < sizeof(sorted); i++) {
        std::cout << "Iteration " << i << std::setw(width) << std::setfill(separator) << unsorted[i] << " seconds " << std::setw(width) << std::setfill(separator) << sorted[i] << " seconds " << std::setw(width) << std::setfill(separator) << std::endl;
    }
    std::cout << "Average" << std::setw(width) << std::setfill(separator) << average_unsorted << " seconds " << std::setw(width) << std::setfill(separator) << average_sorted << " seconds " << std::setw(width) << std::setfill(separator) << std::endl;
}

/**
  @Purpose - function times five different sorting algorithms on vector, and stores and outputs them along with their average times
  @param words - Unsorted vector of words
  @param files - Array of files to be reused as necessary
  @return - None (void)
  @author - Kabir Samsi
**/

std::vector<std::string> time_sorts(std::vector<std::string> &unsorted, std::string files[]) {
    double times_unsorted[5];
    double times_sorted[5];
    std::vector<std::string> words;

    std::cout << "Timing Selection" << std::endl;
    for (int i = 0; i < 5; i++) {
        //Clear vector, and re-add parsed fillers into vector at various positions.
        words.clear();
        for (int i = 0; i < unsorted.size(); i++) words.push_back(unsorted[i]);
        //Implement sorting algorithms on both sorted and unsorted
        times_unsorted[i] = selection_sort(words).count();
        times_sorted[i] = selection_sort(words).count();
    }
    print_table("Selection Sort", times_unsorted, times_sorted);

    std::cout << "Timing Bubble" << std::endl;
    for (int i = 0; i < 5; i++) {
        //Clear vector, and re-add parsed fillers into vector at various positions.
        words.clear();
        for (int i = 0; i < unsorted.size(); i++) words.push_back(unsorted[i]);
        //Implement sorting algorithms on both sorted and unsorted
        times_unsorted[i] = bubblesort(words).count();
        times_sorted[i] = bubblesort(words).count();
    }
    print_table("Bubblesort", times_unsorted, times_sorted);

    for (int i = 0; i < 5; i++) {
        //Clear vector, and re-add parsed fillers into vector at various positions.
        words.clear();
        for (int i = 0; i < unsorted.size(); i++) words.push_back(unsorted[i]);
        //Implement sorting algorithms on both sorted and unsorted
        times_unsorted[i] = insertion_sort(words).count();
        times_sorted[i] = insertion_sort(words).count();
    }
    print_table("Insertion Sort", times_unsorted, times_sorted);

    for (int i = 0; i < 5; i++) {
        //Clear vector, and re-add parsed fillers into vector at various positions.
        words.clear();
        for (int i = 0; i < unsorted.size(); i++) words.push_back(unsorted[i]);
        //Implement sorting algorithms on both sorted and unsorted
        times_unsorted[i] = time_mergesort(words).count();
        times_sorted[i] = time_mergesort(words).count();
    }
    print_table("Mergesort", times_unsorted, times_sorted);

    for (int i = 0; i < 5; i++) {
        //Clear vector, and re-add parsed fillers into vector at various positions.
        words.clear();
        for (int i = 0; i < unsorted.size(); i++) words.push_back(unsorted[i]);
        //Implement sorting algorithms on both sorted and unsorted
        times_unsorted[i] = time_quicksort(words).count();
        times_sorted[i] = time_quicksort(words).count();
    }
    print_table("Quicksort", times_unsorted, times_sorted);
    
    return words;
}

/**
  @Purpose - function performs the three primary layers of the lab, opening and parsing a file of words, sorting and then searching through them. Implements separately compiled functions.
  @return - None (void)
  @author - Kabir Samsi
**/

void interface() {
    std::string files[1];
    std::string search;

    std::cout << "Enter File 1 Path: ";
    std::cin >> files[0];
    std::cout << std::endl << "Enter File 2 Path: ";
    std::cin >> files[1];

    std::vector<std::string> unsorted; //Unsorted vector tracks words in original format for later searching
    unsorted = parseFillers(files); //Store vector of all cleaned and processed words
    if (unsorted.size() == 0) {
        std::cout << std::endl << "An error occurred" << std::endl;
        return;
    }
    std::vector<std::string> words = time_sorts(unsorted, files); //Time sorts on the word vector (finishing with quicksort)

    //Output last fifty words if user requests
    std::string view_last;
    std::cout << "Would you like to view the last 50 words? Y/N: ";
    std::cin >> view_last;
    std::cout << std::endl;
    if (view_last == "Y") last_fifty(words);
    else std::cout << "Ok, skipping this step." << std::endl;
    
    //Perform each search algorithm on vector (already sorted by quicksort)
    std::cout << "Enter search word: ";
    std::cin >> search;
    std::cout << std::endl;
    double linear_search_time = linear_search(words, search).count();
    double linear_search_unsorted_time = linear_search(unsorted, search).count(); //Compare linear search timings for sorted and unsorted vectors
    double binary_search_time = time_binary_search(words, search).count(); //Include the time for quicksort
    char separator = ' ';
    int width = 20;
    
    double times_linear[5];
    double times_linear_sorted[5];
    double times_binary[5];

    //Output search results
    std::cout << "Linear (Unsorted)" << std::setw(width) << std::setfill(separator) << " Linear (Sorted)" << std::setw(width) << std::setfill(separator) << " Binary" << std::endl;
    for (int i = 0; i < 5; i++) {
        times_linear[i] = linear_search(words, search).count();
        times_linear_sorted[i] = linear_search(unsorted, search).count();
        times_binary[i] = time_binary_search(words, search).count();
        std::cout << times_linear[i] << " seconds " << std::setw(width) << std::setfill(separator) << times_linear_sorted[i] << " seconds " << std::setw(width) << std::setfill(separator) << times_binary[i] << " seconds " << std::setw(width) << std::endl;
    }
    //Output averages
    std::cout << average_time(times_linear) << "seconds " << std::setw(width) << std::setfill(separator) << average_time(times_linear_sorted) <<  "seconds " << std::setw(width) << std::setfill(separator) << average_time(times_binary) << " seconds " << std::setw(width) << std::endl;
}

/**
  @Purpose - Main method displays program description to user, then queries them to run program. Executed inside a loop that runs repeatedly until the user calls the program to stop.
  @return - None (void)
  @author - Kabir Samsi
**/

int main() {
    std::string name, command;

    std::cout << "Please enter your name: ";
    getline(std::cin, name);
    std::cout << std::endl << "Hello " << name << "!" << std::endl;

    //Open and read filestream tahat describes program
    std::ifstream description_file;
    description_file.open("description.txt");
    if (description_file.fail()) {
        std::cout << "An error occurred." << std::endl;
    } else {
        std::string line;
        while (getline(description_file, line)) std::cout << line << std::endl;
    }

    //Prompt user to run program, and enter execution loop
    std::cout << std::endl << "Would you like to view this program? Enter 'yes' or 'no': ";
    std::cin >> command;

    while (command != "yes" && command != "no") {
        std::cout << "Invalid command, please enter 'yes' or 'no': ";
        std::cin >> command;
    }

    while(command == "yes") {
        interface();
        std::cout << std::endl << "Would you like to repeat this program? Enter 'yes' or 'no': ";
        std::cin >> command;

        while (command != "yes" && command != "no") {
            std::cout << "Invalid command, please enter 'yes' or 'no': ";
            std::cin >> command;
        }
    }

    std::cout << "Thanks for checking this out, " << name << "! Goodbye." << std::endl;
    return 0;    
}