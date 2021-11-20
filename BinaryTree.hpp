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

    /**
     * Recursively finds the height of the tree.
     * @return height of the tree from the given node.
     */
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

    /**
     * Recursively deletes the tree.
     */
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
    /**
     * Constructs a Binary Tree setting the root with the given data.
     * @param data
     */
    explicit BinaryTree(BinaryTreeType data) {
        auto* newNode = new BinaryTreeNode<BinaryTreeType>(data);
        this -> root = newNode;
    }

    /**
     * Constructs a Binary Tree with the given root node.
     * @param root
     */
    explicit BinaryTree(BinaryTreeNode<BinaryTreeType>* root) {
        this -> root = root;
    }

    /**
     * Returns a pointer to the root node of the tree.
     * @return
     */
    BinaryTreeNode<BinaryTreeType>* getRoot() {
        return this -> root;
    }

    /**
     * Sets the root node with a new node.
     * @param newRoot
     */
    void setRoot(BinaryTreeNode<BinaryTreeType>* newRoot) {
        this -> root = newRoot;
    }

    /**
     * Returns the height of the tree
     * @return
     */
    int height() {
        return this -> root -> height();
    }
    ~BinaryTree() {
        this -> root -> destruct();
    }
private:
    BinaryTreeNode<BinaryTreeType>* root;
};