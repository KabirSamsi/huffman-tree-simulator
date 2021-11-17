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
};

template <typename BinaryTreeType>
class BinaryTree {
public:
    BinaryTree() {
        this -> root = nullptr;
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
        return this -> root.height();
    }
    ~BinaryTree() {

    }
private:
    BinaryTreeNode<BinaryTreeType>* root;
};