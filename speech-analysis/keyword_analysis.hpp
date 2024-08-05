#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <locale>

/**
  @Purpose - function converts string to lowercase
  @param input - The input string
  @return - lowercase version of input string
  @author - Kabir Samsi
**/

std::string lower_kw(std::string input) {
    std::locale loc;
    std::string lower;
    for (int i = 0; i < input.length(); i++) {
        lower += std::tolower(input[i], loc);
    }
    return lower;
}

/**
  @Purpose - function iterates through a vector in search of a given word, returning true if found and false if not
  @param words - A string vector containing all values that are being searched for
  @param word - A string that is being searched for within a vector
  @return - a boolean value demonstrating whether the given string element is in the vector or not
  @author - Kabir Samsi
**/

bool word_in_vector(std::vector<std::string> words, std::string word) {
    std::locale loc;
    for (int i = 0; i < words.size(); i++) { //Iterate through vector and check if word is included
        if (lower_kw(words[i]) == lower_kw(word)) return true;
    }
    return false;
}

/**
  @Purpose - function calculates average value of all elements in an integer vector
  @param values - An integer vector containing all values
  @return - a double value containing the average of all the vector's elements
  @author - Kabir Samsi
**/

double vector_average(std::vector<int> values) {
    double sum = 0.0;
    for (int i = 0; i < values.size(); i++) { //Sum up all values inside vector
        sum += values[i];
    }
    sum /= values.size(); //Divide to calculate average
    return sum;
}

/**
  @Purpose - function calculates the standard deviation of all elemments in an integer vector
  @param values - An integer vector containing all values
  @param mean - The average of the vector
  @return - a double value containing the standard deviation of the vector's elements
  @author - Kabir Samsi
**/

double vector_stddev(std::vector<int> values, double mean) {
    double stddev = 0.0;
    for (int i = 0; i < values.size(); i++) { //Sum up all values inside vector
        stddev += pow(values[i]-mean, 2.0);
    }
    stddev /= values.size(); //Divide to calculate average
    return pow(stddev, 0.5);
}

/**
  @Purpose - function outputs the last <word_count> values of the vcector
  @param words - A string vector (typically sorted) containing all words
  @param word_count - The number of words that need to be outputted from the end of the vector
  @return - None (void)
  @author - Kabir Samsi
**/

void output_last(std::vector<std::string> words, int word_count) {
    //Output last <count> words in dataset
    std::cout << std::endl << "LAST " << word_count << " WORDS IN THIS SORTED DATASET" << std::endl;
    for (int i = words.size()-word_count; i < words.size()-1; i++) { //Iterate through last (n-count) words and print them out
        std::cout << words[i] << ", ";
    }
    std::cout << words[words.size()-1] << "." << std::endl;
}

/**
  @Purpose - function sorts two vectors by the principle of 1 assuming that they are essentially related.
  @param words - A string vector containing a list of unique words
  @param frequencies - An integer array containing the frequency of each unique word
  @return - None (void)
  @author - Kabir Samsi
**/

void bubblesort_double(std::vector<std::string> &words, std::vector<int> &frequencies) {
    bool sorted = false;
    int counter = 0;

    while(!sorted) { //Continue iteration until array is sorted
        sorted = true;
        for (int i = 0; i < frequencies.size()-(counter+1); i++) {
            if (frequencies[i] > frequencies[i+1]) { //If adjacent elements out of order, swap and set array to not sorted
                //Inplace swap for frequencies
                sorted = false;
                int temp_freq = frequencies[i];
                frequencies[i] = frequencies[i+1];
                frequencies[i+1] = temp_freq;

                //Inplace swap for words
                std::string temp_word = words[i];
                words[i] = words[i+1];
                words[i+1] = temp_word;
            }
        }
        counter ++;
    }
}

/**
  @Purpose - function calculates the most frequent unique words, and outputs them in sorted order of frequency
  @param words - A string vector containing a list of unique words
  @param word_count - The number of words that need to be outputted from the start of the vector
  @return - None (void)
  @author - Kabir Samsi
**/

void keyword_frequency(std::vector<std::string> words, int word_count) {
    //Initialize tracker vars and vectors
    std::vector<std::string> frequent_words;
    std::vector<std::string> unique_words;
    std::vector<int> frequencies;
    std::string current_word = words[0];
    std::locale loc;
    int count = 0;
    int unique_count = 0;

    //Open filestream of common words and turn into vector
    std::ifstream frequent_words_file;
    frequent_words_file.open("frequent_words.txt");
    if (frequent_words_file.fail()) return;

    //Add all words from list of 100 common words into vector
    std::string word;
    while (frequent_words_file >> word) {
        if (isalpha(word[0]) && word.length() > 3) frequent_words.push_back(word);
    }
    frequent_words_file.close();

    //Iterate through words and find longer, uncommon unique words
    std::cout << std::endl << "FIRST " << word_count << " UNIQUE WORDS IN THIS SORTED DATASET" << std::endl;
    for (int i = 0; i < words.size(); i++) {
        if (lower_kw(words[i]) != lower_kw(current_word)) { //If word is new, add previous accumulated word and word count to vectors and move on
            if (unique_count < word_count) std::cout << words[i] << ", "; //Print out first 50 unique words
            else if (unique_count == word_count) std::cout << words[i] << "." << std::endl;
            unique_count ++;

            if (current_word.length() > 3 && !word_in_vector(frequent_words, current_word)) {
                unique_words.push_back(current_word);
                frequencies.push_back(count);
            }
            count = 1; //Set count to 1 since first word has already been encountered
        } else count ++; //Otherwise, continue to increment
        current_word = words[i];
    }

    //Sort both vectors and find average and standard deviation
    bubblesort_double(unique_words, frequencies);
    int start_index = (int) unique_words.size()/2;
    int average = (int) vector_average(frequencies);
    int start_range = (int) (average + vector_stddev(frequencies, average));

    //Iterate on either side of vector (depending on whether midpoint is less or greater than average) until value is reached
    switch (frequencies[start_index] > start_range) {
        case true:
            while (frequencies[start_index-1] > start_range) start_index --;
            break;
        case false:
            while (frequencies[start_index-1] < start_range) start_index ++;
            break;
    }

    //Output vector values to right of average
    std::cout << std::endl << "\nMOST FREQUENT WORDS IN DATASET (SORTED BY FREQUENCY)" << std::endl;
    for (int i = start_index; i < unique_words.size()-1; i++) {
        std::cout << unique_words[i] << " (" << frequencies[i] << ")" << ", ";
    }
    std::cout << unique_words[unique_words.size()-1] << " (" << frequencies[frequencies.size()-1] << ")" << std::endl;
}