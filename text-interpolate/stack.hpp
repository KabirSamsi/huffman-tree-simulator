#include <iostream>
#include <fstream>

struct StackNode { //Struct definition of Stack Node
    char val;
    StackNode* next;
};

void push(StackNode* &hp, char val) { //Add node to the top of the stack
    StackNode* newNode = new StackNode;
    newNode->val = val;
    newNode->next = hp; //Set the node's next pointer to the head pointer
    hp = newNode; //Reinitialize head pointer to point to the new top
}

char pop(StackNode* &hp) { //Remove node from the top of the stack
    char top = hp->val;
    StackNode* current = hp; //Track head pointer after removal
    hp = hp->next;
    delete current; //Remove pointer to top node
    return top; //Return value of the top pointer
}

char top(StackNode* &hp) { //Accessor method returns the top value of the stack
    return hp->val;
}

std::string printStack(StackNode* &hp) { //Print all the values in a stack
    StackNode* current = hp;
    std::string final_string = "";
    while (current->next != nullptr) { //Iterate until there are no nodes left
        std::cout << current->val;
        final_string += current->val;
        current = current->next; //Traverse forward
    }
    return final_string;
}

StackNode* createStack(std::string phrase) { //Create a stack of characters from a string
    StackNode* newNode = new StackNode;
    newNode->val = phrase[0]; //Set head pointer to the first value in the string
    
    int start_val = 0;
    while (phrase[start_val] == ' ') start_val ++; //Set start value to the first non-space character
    for (int i = start_val; i < phrase.length(); i++) {
        push(newNode, phrase[i]); //Iterate forward and add each new character to the top
    }
    while (!isalpha(top(newNode))) pop(newNode); //Remove all non-alphanumeric characters from the stack
    return newNode; //Return head pointer to the top of the stack
}

void deleteStack(StackNode* &hp) { //Deallocate and remove all nodes from the stack
    while (hp != nullptr) pop(hp);
}