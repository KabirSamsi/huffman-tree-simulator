//This program demonstrates a decision tree for an animal guessing game

#include <iostream>
#include <string>
#include "binary_tree.hpp"

int main() {
   BinaryTree question_tree( //Stores all of the questions in order
      BinaryTree("Is it a mammal?",
         BinaryTree("Does it have stripes?",
            BinaryTree("Is it a carnivore?",
               BinaryTree("Is it a tiger?"),
               BinaryTree("Is it a zebra?")),
            BinaryTree("Is it a pig?")),
      BinaryTree("Does it fly?",
         BinaryTree("It is an eagle?"),
         BinaryTree("Does it swim?",
            BinaryTree("Is it a penguin?"),
            BinaryTree("It is an ostrich?")
         )
      )
   ));
   
   //Loop-repeating variables
   bool done;
   BinaryTree root = question_tree;
   BinaryTree left, right;
   std::string newAnimal, newQuestion, response;
   std::string playing = "y";

   while (playing == "y") { //Continues while user wants to play
      done = false; //Game is not yet finished
      question_tree = root; //Set question to start at the root of the tree

      while (!done) { //While game is not completed
         left = question_tree.left();
         right = question_tree.right();
         if (left.empty() && right.empty()) { //If a leaf has been reached
            do { //Accept input to move left or right while user has not entered a valid input
               std::cout << question_tree.data() << " (y/n): ";
               std::cin >> response;
            } while (response != "y" && response != "n");

            if (response == "y") done = true; //If guess is correct, this round is finished
            else { //Otherwise, add new animal to tree
               std::cout << "What animal is it? ";
               getline(std::cin, newAnimal);
               question_tree.buildLeft("Is it a " + newAnimal + "? "); //Build a left subtree with the new animal
               question_tree.buildRight(question_tree.data()); //Build a right subtree with the old animal
               
               //Access input for new question
               std::cout << std::endl << "Write a question for future users to determine which of the two animals it is." << std::endl;
               std::cout << "We will assume that the answer to the question is true for the new animal, and false for the original one." << std::endl;
               std::cout << "Enter your new question here: ";
               std::cin >> newQuestion;
               getline(std::cin, newQuestion);
               std::cout << newQuestion << std::endl;
               question_tree.mutate(newQuestion); //Replace current node data with the new question

               std::cout << "Added " << newAnimal << " to our animal list!" << std::endl;
               done = true; //Round is not finished
            }
            
         } else {
            do { //Accept input to move left or right while user has not entered a valid input
               std::cout << question_tree.data() << " (y/n): ";
               std::cin >> response;
            } while (response != "y" && response != "n");

            if (response == "y") question_tree = left; //Move left     
            else question_tree = right; //Move right
         }
      }

      if (done) { //If round is finished, prompt user to play again
         std::cout << "Great, the program guessed your animal!" << std::endl;
         std::cout << "\nWould you like to play again? (y/n): ";
         std::cin >> playing;
      }
   }
   std::cout << "Thanks for playing!" << std::endl; //Game terminates
}