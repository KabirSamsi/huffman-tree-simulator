#ifndef CS_124_Lab_4_HASHMAP_HPP
#define CS_124_Lab_4_HASHMAP_HPP

template <typename SinglyLinkedNodeType>
class SinglyLinkedNode {
public:
    explicit SinglyLinkedNode(SinglyLinkedNodeType value) {
        this -> value = value;
    };
    SinglyLinkedNode<SinglyLinkedNodeType>* next = nullptr;
    SinglyLinkedNodeType value;
};

template <typename HashMapType>
class HashMap {
public:
    HashMap(int (*hashFunction)(HashMapType), int size) {
        this -> hashTable = new SinglyLinkedNode<HashMapType>*[size];
        this -> hashFunction = hashFunction;
    }
private:
    SinglyLinkedNode<HashMapType>* hashTable[];
    int (*hashFunction)(HashMapType);
};

#endif