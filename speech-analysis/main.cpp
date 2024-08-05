#include <iostream>
#include <fstream>
#include <vector>
#include "clean.hpp"
#include "sort.hpp"
#include "keyword_analysis.hpp"

/**
  @Purpose - function performs the three primary layers of the lab, opening and parsing a file of words, sorting and then analyzing them. Implements separately compiled functions.
  @return - None (void)
  @author - Kabir Samsi
**/

void interface() {
    std::cout << "Loading Files...";
    const std::string filename = "BreneBrown3Speeches.txt";

    std::vector<std::string> words = parseFillers(filename); //Store vector of all cleaned and processed words
    std::cout << " Done." << std::endl;

    if (words.size() == 0) {
        std::cout << std::endl << "An error occurred" << std::endl;

    }  else {
        std::cout << "Parsing Word Data...";
        std::vector<std::string> copied_words, third_copy; //Create vector copies for second and third sorts
        for (int i = 0; i < words.size(); i++) {
            copied_words.push_back(words[i]);
            third_copy.push_back(words[i]);
        }
        std::cout << " Done." << std::endl << "Sorting Vectors...";

        //Time sorts for all three vectors, sorted and unsorted (resulting in words vector getting sorted in the process)
        duration<double> sorting_times[6];
        sorting_times[0] = selection_sort(words);
        sorting_times[1] = bubblesort(copied_words);
        sorting_times[2] = insertion_sort(third_copy);
        sorting_times[3] = selection_sort(words);
        sorting_times[4] = bubblesort(copied_words);
        sorting_times[5] = insertion_sort(third_copy);
        std::cout << " Done." << std::endl;

        //Output timings for the three n^2 sorting algorithms, on both unsorted and sorted vectors
        std::cout << std::endl << "SORTING TIMES" << std::endl;
        std::cout << "Selection Sort (Unsorted): " << sorting_times[0].count() << " seconds" << std::endl;
        std::cout << "Bubblesort (Unsorted): " << sorting_times[1].count() << " seconds" << std::endl;
        std::cout << "Insertion Sort (Unsorted): " << sorting_times[2].count() << " seconds\n" << std::endl;
        std::cout << "Selection Sort (Sorted): " << sorting_times[3].count() << " seconds" << std::endl;
        std::cout << "Bubblesort (Sorted): " << sorting_times[4].count() << " seconds" << std::endl;
        std::cout << "Insertion Sort (Sorted): " << sorting_times[5].count() << " seconds\n" << std::endl;
        std::cout << "Difference in Selection Sort Timings: " << sorting_times[0].count()-sorting_times[3].count() << " seconds" << std::endl;
        std::cout << "Difference in Bubblesort Timings: " << sorting_times[1].count()-sorting_times[4].count() << " seconds" << std::endl;
        std::cout << "Difference in Insertion Sort Timings: " << sorting_times[2].count()-sorting_times[5].count() << " seconds" << std::endl;

        copied_words.clear();
        third_copy.clear();
        //Output last and first 50 words and calculate most frequent keywords
        output_last(words, 50);
        keyword_frequency(words, 50);
    }
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

    std::cout << "Thanks for checking this out! Goodbye." << std::endl;
    return 0;    
}