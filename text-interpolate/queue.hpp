#include <iostream>
#include <fstream>

struct QueueNode { //Struct definition of Queue Node
    char val;
    QueueNode* next;
};

void push(QueueNode* &hp, char val) { //Add node to the end of the queue
    QueueNode* temp = hp;
    QueueNode* newNode = new QueueNode;
    newNode->val = val;
    newNode->next = nullptr;

    while (temp->next != nullptr) temp = temp->next; //Iterate forward in linked list, until lat node reached
    temp->next = newNode; //Add to end
}

char pop(QueueNode* &hp) { //Remove node from the front of the queue
    char top = hp->val;
    QueueNode* current = hp; //Track head pointer after removal
    hp = hp->next;
    delete current; //Remove pointer for front node
    return top; //Return value of front ptr
}

std::string printQueue(QueueNode* &hp) { //Print all the values in a queue
    QueueNode* current = hp;
    std::string final_string = "";
    while (current->next != nullptr) { //Iterate until there are no nodes left
        std::cout << current->val;
        final_string += current->val;
        current = current->next; //Traverse forward
    }
    return final_string;
}

QueueNode* createQueue(std::string phrase) { //Create a queue of characters from a string
    QueueNode* newNode = new QueueNode;
    newNode->val = phrase[0]; //Set head pointer to first value in string
    newNode->next = nullptr;
    
    int start_val;
    if (phrase[0] == ' ') start_val = 1;
    else start_val = 0;
    for (int i = 1; i <= phrase.length(); i++) {
        push(newNode, phrase[i]); //Add new value to new node
    }
    return newNode;
}

void deleteQueue(QueueNode* &hp) { //Deallocate and remove all nodes from a queue
    while (hp) pop(hp);
}