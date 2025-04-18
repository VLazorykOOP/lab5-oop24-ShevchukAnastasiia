#include <iostream>
#include <queue>

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
protected:
    Node* root;

public:
    BinaryTree() : root(nullptr) {}

    virtual void insert(int value) = 0; // pure virtual method
    virtual void breadthFirstTraversal() const = 0;
    virtual void reverseInOrderTraversal() const = 0;
};

class BinarySearchTree : public BinaryTree {
private:
    void insertHelper(Node*& current, int value) {
        if (!current) {
            current = new Node(value);
            std::cout << "Inserted: " << value << std::endl;
        } else if (value < current->value) {
            insertHelper(current->left, value);
        } else if (value > current->value) {
            insertHelper(current->right, value);
        } else {
            std::cout << "Duplicate value (" << value << ") not inserted.\n";
        }
    }

    void reverseInOrderHelper(Node* current) const {
        if (!current) return;
        reverseInOrderHelper(current->right);
        std::cout << current->value << " ";
        reverseInOrderHelper(current->left);
    }

public:
    void insert(int value) override {
        insertHelper(root, value);
    }

    void breadthFirstTraversal() const override {
        if (!root) {
            std::cout << "Tree is empty.\n";
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        std::cout << "Breadth-first traversal: ";
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->value << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }

    void reverseInOrderTraversal() const override {
        std::cout << "Reverse in-order traversal: ";
        reverseInOrderHelper(root);
        std::cout << std::endl;
    }

    ~BinarySearchTree() {
        clear(root);
    }

private:
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main() {
    BinarySearchTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(30); // Duplicate test

    std::cout << std::endl;
    tree.breadthFirstTraversal();
    tree.reverseInOrderTraversal();

    return 0;
}
