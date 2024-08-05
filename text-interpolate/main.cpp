#include <iostream>
#include <fstream>
#include <vector>
#include "stack.hpp"
#include "queue.hpp"

int checkProse(std::string filename) { //Check if file is prose or poem based on number of lines
    std::string line;
    std::ifstream file;
    file.open(filename);
    if (file.fail()) return -1; //If file cannot be opened, return a negative result

    int count = 0;
    while (getline(file, line)) count ++; //For every line in the file, add 1 to the count
    file.close();
    return count;
}

std::string printPhrase(std::string line, bool para) { //Print a line either reversed or normally, using a stack and a queue
    std::locale loc;
    StackNode* stack; //Initialize stack head pointer
    QueueNode* queue; //Initialize queue head pointer
    std::string final_string = "";

    if (line != "") { //If line is not empty
        stack = createStack(line); //Initializes stack of reversed text (see "stack.hpp" for implementation details)
        if (std::tolower(stack->val, loc) == stack->val) { //If the top of the stack is lowercase, output the line normally (as a queue)
            queue = createQueue(line); //Create and output a queue of the text, in FIFO (in-order) fashion
            final_string += printQueue(queue);
            deleteQueue(queue); //Delete and deallocate memory for the queue (Valgrind successfully returns all blocks deallocated)

        } else { //If line is reversed
        	if (!para) std::cout << line << "-> "; //If the line is part of a poem, output the original line
        	final_string += printStack(stack); //Output the newly reversed line
        }
        deleteStack(stack); //Deallocate stack

    } else std::cout << std::endl; //If line is empty, put an endline character
    return final_string;
}

std::string printPara(std::string line) { //Output a paragraph of properly reversed text
	std::cout << "ORIGINAL: " << line << std::endl << "\nREVERSED: "; //Output original text first
	std::vector<std::string> lines; //Vector tracks the original lines
	int count = 0; //Tracks the number of characters since the last period
	int index = 0; //Tracks the current index within the word
	int current_index = 0; //Track the index of the previous period, to start new sentence
	std::string final_string = "";
	while (index < line.length()) {
		index ++;
		count ++;
		if (line[index] == '.') { //If period is found, break sentence at this point
			lines.push_back(line.substr(current_index, count+2));
			count = 0;
			current_index = index;
		}
	}
	for (int i = 0; i < lines.size(); i++ ) { //Print out each line in the vector like a poem, but without the original text being displayed
		final_string += printPhrase(lines[i], true);
	}
	return final_string;
}

void interface(std::string filename) { //Controls the heart of the lab runtime
    std::ifstream file; //Open the specified file based on user filename input
    file.open(filename);

    if (file.fail()) std::cout << "Unable to open file." << std::endl; //If file does not exist or has an error, output error message
    else { //If successful, continue process
        std::string line;
        std::ofstream output_file;
        output_file.open("result.txt");
        if (output_file.fail()) {
        	std::cout << "Unable to open file." << std::endl;
        	return;
        }
        
        int proseCount = checkProse(filename); //Check if file is prose or poem using earlier method
        if (proseCount == 1) { //If file is prose
        	while (getline(file, line)) output_file << printPara(line); //Print out the single paragraph in standardized paragraph format
        	std::cout << std::endl << "\nSuccessfully written to result file!" << std::endl;
		std::cout << "NOTE: The original reversed lines are not included in the result file." << std::endl;
        } else if (proseCount > 1) { //If file is poetry (multiple lines)
		while (getline(file, line)) { //Iterate through each line of the file
			output_file << printPhrase(line, false) << "\n"; //Print in formatted fashion, reversed if necessary
			std::cout << std::endl;
		}
		std::cout << std::endl << "Successfully written to result file!" << std::endl;
		std::cout << "NOTE: The original reversed lines are not included in the result file." << std::endl;
        } else std::cout << "Unable to open file." << std::endl; //If there is a file opening issue (-1 returned from checkProse() method)
        output_file.close();
    }
}

int main() { //Main method
	std::ifstream file;
	std::string filename;
	int runcount = 0;
	file.open("description.txt"); //Output description of program to user
	if (file.fail()) std::cout << "Unable to open file." << std::endl;
	else { //If no error opening file, execute main methods
		std::string line, username, user_input;
		std::cout << "What is your name? "; //Query the user for their name, greet them, and ask if they want to view the lab
		getline(std::cin, username);
		std::cout << "Hello " << username << "!" << std::endl;
		while (getline(file, line)) std::cout << line << std::endl;
		file.close();
		std::cout << "Would you like to view this program? Enter yes or no: ";
		std::cin >> user_input;
		while (user_input == "yes") { //Continue process until user no longer wants to view files
			if (runcount == 0) { //Run Jabberwocky first (can cause errors otherwise)
				std::cout << "You can view an example of this program, with Lewis Carroll's poem, 'Jabberwocky'!\n" << std::endl;
				interface("twas_brillig.txt");
				std::cout << std::endl << "Now you can try some other files!\n" << std::endl;
			}
    			std::cout << "Which file would you like to view? ";
    			std::cin >> filename;
    			std::cout << std::endl;
			interface(filename); //Execute primary method that controls interface
			std::cout << std::endl << "Would you like to view this program again? Enter yes or no: "; //Check if user want to run again
			std::cin >> user_input;
			runcount ++;
		}
		std::cout << "Thanks for checking this out, " << username << "! Goodbye." << std::endl; //Goodbye (exit) message
	}
	return 0;
}