#include <iostream>

/**
 * A Binary Tree Node
 * @tparam BinaryTreeNodeType
 */
template <typename BinaryTreeNodeType>
class BinaryTreeNode {
public:
    BinaryTreeNodeType data;
    BinaryTreeNode<BinaryTreeNodeType>* left;
    BinaryTreeNode<BinaryTreeNodeType>* right;
    explicit BinaryTreeNode(BinaryTreeNodeType data) {
        this -> data = data;
        this -> left = nullptr;
        this -> right = nullptr;
    }
    int height() {
        int leftHeight = 0;
        int rightHeight = 0;
        if (this -> left != nullptr) {
            leftHeight = this -> left -> height();
        }
        if (this -> right != nullptr) {
            rightHeight = this -> right -> height();
        }
        return 1 + std::max(leftHeight, rightHeight);
    }
    void destruct() {
        if (this -> left != nullptr) {
            this -> left -> destruct();
        }
        if (this -> right != nullptr) {
            this -> right -> destruct();
        }
        delete this;
    }
};

template <typename BinaryTreeType>
class BinaryTree {
public:
    explicit BinaryTree(BinaryTreeType data) {
        auto* newNode = new BinaryTreeNode<BinaryTreeType>(data);
        this -> root = newNode;
    }
    explicit BinaryTree(BinaryTreeNode<BinaryTreeType>* root) {
        this -> root = root;
    }
    BinaryTreeNode<BinaryTreeType>* getRoot() {
        return this -> root;
    }
    void setRoot(BinaryTreeNode<BinaryTreeType>* newRoot) {
        this -> root = newRoot;
    }
    int height() {
        return this -> root -> height();
    }
    ~BinaryTree() {
        this -> root -> destruct();
    }
private:
    BinaryTreeNode<BinaryTreeType>* root;
};