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
    for (int i = 0; i < words.size()-1; i++) {
        int smallest = smallest_value(words, i, words.size()-1); //Find smallest value in shrunk vector range, and swap with current index
        swap(words[i], words[smallest]);
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
    while(!sorted && counter < words.size()) { //Continue iteration until array is sorted
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

/**
  @Purpose - function merges two sorted adjacent halves of a vector of words
  @param words - The vector of words, consisting of two alphabetically sorted, adjacent halves
  @param from - The starting index of the vector
  @param mid - The middle index of the vector (rounded down to integer value)
  @param to - The ending index of the vector
  @return - The final index of the right pointer (traversing left) to determine the new pivot
  @author - Kabir Samsi
**/

void merge(std::vector<std::string> &words, int from, int mid, int to) {
    int a = 0;
    int b = mid+1;
    std::vector<std::string> merged; //Copy vector stores values

    while (a <= mid && b <= to) { //Merge the two halves in order, depending on which current element has the smaller value
        if (words[a] < words[b]) {
            merged.push_back(words[a]);
            a++;
        } else {
            merged.push_back(words[b]);
            b++;
        }
    }

    while (a <= mid) { //Leftover elements from first half (if first half has larger values)
        merged.push_back(words[a]);
        a++;
    }

    while (b <= to) { //Leftover elements from second half (if second half has larger values)
        merged.push_back(words[b]);
        b++;
    }
}

/**
  @Purpose - function recursively performs the Mergesort algorithm on an unsorted vector of words
  @param words - The unsorted vector of words that is sorted using the Mergesort>algorithm
  @param from - The left bound of the to-sort portion
  @param to - The right bound of the to-sort portion
  @return - The time period taken to complete the algorithm
  @author - Kabir Samsi
**/

void mergesort(std::vector<std::string> &words, int from, int to) {
    if (from == to) return;
    int mid = (from+to)/2; //Find array midpoint
    
    //Recursively sort each half
    mergesort(words, from, mid);
    mergesort(words, mid+1, to);
    merge(words, from, mid, to); //Merge two sorted halves
}

/**
  @Purpose - function performs and times Mergesort on an unsorted vector of parsed and cleaned words
  @param words - The unsorted vector of words that is sorted using the Mergesort algorithm
  @return - The time period taken to complete the algorithm
  @author - Kabir Samsi
**/

duration<double> time_mergesort(std::vector<std::string> &words) {
    high_resolution_clock::time_point start = high_resolution_clock::now(); //Time of start
    mergesort(words, 0, words.size()-1);
    high_resolution_clock::time_point finish = high_resolution_clock::now(); //Time of finish
    return duration_cast<duration<double> >(finish - start); //Calculate difference in times
}

/**
  @Purpose - function iterates from two pointers at either end of array, swapping the first out-of-place elements it occurs
  @param words - The unsorted vector of words that is iterated through
  @param from - The starting point of iteration towards pivot (from left)
  @param to - The starting point of iteration towards pivot (from right)
  @return - The final index of the right pointer (traversing left) to determine the new pivot
  @author - Kabir Samsi
**/

int partition(std::vector<std::string> &words, int from, int to) {
    std::string pivot = lower_sort(words[from]);
    //Set tracker variables on either side
    int i = from-1;
    int j = to+1;

    while (i < j) { //Continue swapping process until i moves past j
        i++; while (lower_sort(words[i]) < pivot) i++; //Find first value larger than pivot on the left
        j--; while (lower_sort(words[j]) > pivot) j--; //Find first value smaller than pivot on the right
        //If i and j are both on the correct sides of the pivot, swap elements on either side
        if (lower_sort(words[i]) < lower_sort(words[j])) swap(words[i], words[j]);
    }
    return j;
}

/**
  @Purpose - function recursively performs the Quicksort algorithm on an unsorted vector of words
  @param words - The unsorted vector of words that is sorted using the Quicksort algorithm
  @param from - The starting point of iteration towards pivot (from left)
  @param to - The starting point of iteration towards pivot (from right)
  @return - The time period taken to complete the algorithm
  @author - Kabir Samsi
**/

void quicksort(std::vector<std::string> &words, int from, int to) {
    if (from > to) return; //Continue until pivot falls outside array bounds
    int p = partition(words, from, to); //Create pivot point by partitioning array

    //Recursively sort around pivot
    quicksort(words, from, p);
    quicksort(words, p+1, to);
}

/**
  @Purpose - function performs and times Quicksort on an unsorted vector of parsed and cleaned words
  @param words - The unsorted vector of words that is sorted using the Quicksort algorithm
  @return - The time period taken to complete the algorithm
  @author - Kabir Samsi
**/

duration<double> time_quicksort(std::vector<std::string> &words) {
    high_resolution_clock::time_point start = high_resolution_clock::now(); //Time of start
    quicksort(words, 0, words.size()-1);
    high_resolution_clock::time_point finish = high_resolution_clock::now(); //Time of finish
    return duration_cast<duration<double> >(finish - start); //Calculate difference in times
}