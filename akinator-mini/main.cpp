#include <algorithm>
#include <string>
#include <iostream>

class Node { //Node class representing the values in a binary tree
    private:
        std::string data;
        Node* left;
        Node* right;
        friend class BinaryTree;
};

class BinaryTree { //Binary tree consisting of nodes with at most two children
    public:
        BinaryTree(); //Constructs an empty tree.
        BinaryTree(std::string root_data); //Constructs a tree with one node and no children
        BinaryTree(std::string root_data, BinaryTree left, BinaryTree right); //Tree with a value and two children
        int height() const; //Returns height of tree
        bool empty() const; //Returns whether tree is empty or not
        std::string data() const; //Returns the data in a tree
        void changeData(std::string newData) const; //Changes the data in a node
        void buildLeft(std::string newData); //Build a left subtree given new data input
        void buildRight(std::string newData); //Build a right subtree given new data input
        BinaryTree left() const; //Trace left subtree
        BinaryTree right() const; //Trace right subtree
        void mutate(std::string newData); //Replace the current node's data with new input

    private:
        int height(const Node* n) const; //Returns height of a subtree
        Node* root; //The root value of the tre
};

BinaryTree::BinaryTree() { //Initialize empty binary tree
    root = nullptr;
}

BinaryTree::BinaryTree(std::string root_data) { //Initialize tree with a root but no children
   root = new Node;
   root->data = root_data;
   root->left = nullptr;
   root->right = nullptr;
}

BinaryTree::BinaryTree(std::string root_data, BinaryTree left, BinaryTree right) { //Initialize tree with a root and children (left, right)
   root = new Node;
   root->data = root_data;
   root->left = left.root;
   root->right = right.root;
}
   
int BinaryTree::height(const Node* n) const { //Calculate height of a binary tree
   if (n == nullptr) return 0;
   else return 1 + std::max(height(n->left), height(n->right)); //Find maximum height of subtrees
}

int BinaryTree::height() const {return height(root);} //Return the height of a tree

bool BinaryTree::empty() const {return root == nullptr;} //Check if tree is empty

void BinaryTree::changeData(std::string newData) const {root->data = newData;} //Change the data of a tree's root

std::string BinaryTree::data() const {return root->data;} //Return the data of a tree's root
   
void BinaryTree::buildLeft(std::string newVal) { //Build a left subtree given a new value
    BinaryTree newTree(newVal);
    root->left = newTree.root;
}

void BinaryTree::buildRight(std::string newVal) { //Build a right subtree given a new value
    BinaryTree newTree(newVal);
    root->right = newTree.root;
}

BinaryTree BinaryTree::left() const { //Return the left subtree
   BinaryTree result;
   result.root = root->left; 
   return result;
}

BinaryTree BinaryTree::right() const { //Return the right subtree
   BinaryTree result;
   result.root = root->right; 
   return result;
}

void BinaryTree::mutate(std::string newData) { //Mutator method that replaces the current data with a new data
    root->data = newData;
}

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
   bool done, guessed;
   BinaryTree root = question_tree;
   BinaryTree left, right;
   std::string newAnimal, newQuestion, response;
   std::string playing = "y";

   while (playing == "y") { //Continues while user wants to play
      done = false; //Game is not yet finished
      guessed = false;
      question_tree = root; //Set question to start at the root of the tree

      while (!done) { //While game is not completed
         left = question_tree.left();
         right = question_tree.right();
         if (left.empty() && right.empty()) { //If a leaf has been reached
            do { //Accept input to move left or right while user has not entered a valid input
               std::cout << question_tree.data() << " (y/n): ";
               std::cin >> response;
            } while (response != "y" && response != "n");

            if (response == "y") {
                done = true; //If guess is correct, this round is finished
                guessed = true;
            } else { //Otherwise, add new animal to tree
               std::cout << "What animal is it? (One word): ";
               std::cin >> newAnimal;
               question_tree.buildLeft("Is it a " + newAnimal + "?"); //Build a left subtree with the new animal
               question_tree.buildRight(question_tree.data()); //Build a right subtree with the old animal
               
               //Access input for new question
               std::cout << std::endl << "Write a question for future users to determine which of the two animals it is." << std::endl;
               std::cout << "We will assume that the answer to the question is true for the new animal, and false for the original one." << std::endl;
               std::cout << "Enter your new question here: ";
               std::cin.ignore(1024, '\n');
               getline(std::cin, newQuestion);
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
        if (guessed) std::cout << "Great, the program guessed your animal!" << std::endl;
        std::cout << "\nWould you like to play again? (y/n): ";
        std::cin >> playing;
      }
   }
   std::cout << "Thanks for playing!" << std::endl; //Game terminates
}