//
// Created by zacha on 4/2/2020.
//

#ifndef LAB_11_AVL_AVL_H
#define LAB_11_AVL_AVL_H

#include "AVLInterface.h"
#include <iostream>
#include <string>
#include <ostream>
#include <sstream>

using namespace std;
template <typename T>
class AVL : public AVLInterface<T> {

private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        size_t height;
        Node(const T& d, Node* l, Node* r, size_t h) : data(d), left(l), right(r), height(h) { }
    };
    Node* root;

public:
    AVL() { this->root = NULL; }
    ~AVL() {
        clearTree();
    }

    size_t getHeight(Node* node) {
        if(node == NULL) {
            return 0;
        }
        return node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    void rightRotate(Node*& y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        // Return new root
        y = x;
//        return x;
    }

    void leftRotate(Node*& x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        // Return new root
        x = y;
//        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node*& N) {
        if(N == NULL)
            return 0;
        return getHeight(N->left) - getHeight(N->right);
    }


    //recursive addNodes functions taken in user data and recursively adds it to the appropriate location in the BST
    bool addNode(const T& userData) {
        return addNode(root, userData);
    }
    bool addNode(AVL::Node*& node, const T &userData) {
        bool success;
        if (node == NULL) {
            node = new Node(userData, NULL, NULL, 1);
            success = true;
        }
        else if (node->data == userData) {
            success = false;
        }
        else if (userData < node->data) {
            success = addNode(node->left, userData);
            balance(node);
            return success;
        }
        else if (userData > node->data) {
            success = addNode(node->right, userData);
            balance(node);
            return success;
        }

        //Get Balance
        balance(node);

    return success;
    }

    int updateHeight(Node*& node) {
        if (node == NULL) {
            return 0;
        }
        node->height = max (updateHeight(node->left), updateHeight(node->right)) + 1;
        return node->height;
       // node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void balance(Node*& node) {
        //parentNode height
        updateHeight(node);


        int balance = getBalance(node);
        // 4 cases

        if (balance < -1) { //right heavy
            int childBalance = getBalance(node->right);
            if(childBalance >= 1) { // right right case
                rightRotate(node->right);
                leftRotate(node);

            }
            else { //right left case
                leftRotate(node);
            }
        }
        if (balance > 1) { // left heavy
            int childBalance = getBalance(node->left);
            if(childBalance <= -1) { // left left case
                leftRotate(node->left);
                rightRotate(node);
            }
            else { // left right case
                rightRotate(node);
            }
        }
    }

    //returns a string that prints the BST in an intuitive manner
    std::string toString() const {
        std::stringstream out;
        if (root == NULL) {
            out << " empty";
        }
        else
        {
            int level = 0;
            do
            {
                out << std::endl << "  " << ++level << ":";
            } while (outLevel(root, level, out));
        }
        return out.str();
    }

    //helper function for remove, switches data at two nodes and leaves nodes intact
    void swap(Node*& nodeOne, Node*& nodeTwo) {
        T tempValue = nodeOne->data;
        nodeOne->data = nodeTwo->data;
        nodeTwo->data = tempValue;
    }
    //recursive functions to remove nodes
    bool removeNode(const T& userData) {
        if (root == NULL) return false;
        if (!findNode(userData)) { //check that node exists before removal
            return false;
        }
        return removeNode(root, userData);
    }
    bool removeNode(Node*& node, const T &userData) {
        bool success = false;
        if (node == NULL) {
            return false;
        }

        Node* parentNode = NULL;
        findParentNode(node->data, parentNode); //gets parentNode and keeps track of it

        if (userData < node->data) { //recursive call to continue traversing tree
            success = removeNode(node->left, userData);
            balance(node);
            return success;
        }
        else if (userData > node->data) {
            success = removeNode(node->right, userData);
            balance(node);
            return success;
        }

        else {
            if (node->left == NULL && node->right == NULL) { // No child case
                if (node->data == root->data) { //you are the root case, must set root to NULL
                    delete root;
                    root = NULL;
                    return true;
                }
                if (parentNode->left != NULL) { // if you are on the left, are the left child
                    if (node->data == parentNode->left->data) { //if you are the left child
                        delete parentNode->left;
                        parentNode->left = NULL;
                        return true;
                    }
                }
                if (parentNode->right != NULL) { //if you are the right child of the parent
                    if (node->data == parentNode->right->data) { // if you are for sure the right child
                        delete parentNode->right;
                        parentNode->right = NULL;
                    }
                }
                return true;
            }
            else if (node->left == NULL) { // You have a right child case
                if (node->data == root->data) { //first check to see if you are the root
                    Node* tempNode = root->right;
                    delete root;
                    root = tempNode;
                }
                else if (userData < parentNode->data) { // if you need to go left because you are less than the parent
                    Node* tempNode = node->right; //right child stored
                    delete node;
                    parentNode->left = tempNode;
                }
                else {
                    Node* tempNode = node->right; //right child stored
                    delete node;
                    parentNode->right = tempNode; //right child Node moved up to replace deleted node
                }
                balance(node);
                return true;
            }
            else { //two children case
                Node* inOrderPredecessor = getInorderPredecessor(node); // use helper function to get inorder predecessor
                swap(node, inOrderPredecessor); //swap data with predecessor
                success = removeNode(node->left, userData); //call recursive remove on that value
                balance(node); //Balance here??
                return success;
            }
        }
    }
    //helper function for in-order predecessor
    Node* getInorderPredecessor(Node* nodeToDelete) {
        if (nodeToDelete == NULL) {
            return NULL;
        }
        Node* currentNode = nodeToDelete->left;
        while (currentNode->right != NULL) { // the rightmost node in the left subtree
            currentNode = currentNode->right;
        }
        return currentNode;
    }

    void findParentNode(const T& data, Node*& parentNode) {
        findParentNode(root, data, parentNode);
    }
    void findParentNode(Node* node, const T& data, Node*& parentNode) {
        Node* currentNode = node;
        if (node == NULL)
            return;

        // If current node is the required node
        if (node->left != NULL && node->left->data == data) {
            parentNode = currentNode;
        }
        else if (node->right != NULL && node->right->data == data) {
            parentNode = currentNode;
        }
        else {
            findParentNode(currentNode->left, data, parentNode);
            findParentNode(currentNode->right, data, parentNode);
        }
    }


    //given helper function
    bool outLevel(Node* root, int level, std::stringstream &out) const {
        if (root == NULL) return false;
        if (level == 1)
        {
            out << " " << root->data;
            if ((root->left != NULL) || (root->right != NULL)) return true;
            return false;
        }
        if ((level == 2) && !root->left && root->right) out << " _";
        bool left = outLevel(root->left, level - 1, out);
        bool right = outLevel(root->right, level - 1, out);
        if ((level == 2) && root->left && !root->right) out << " _";
        return left || right;
    }

    //recursive size function
    int size() {
        return size(root);
    }
    int size(Node* node)
    {
        if (node == NULL)
            return 0;
        else
            return(size(node->left) + 1 + size(node->right)); //returns the structure of the tree recursively (root + left and right subtrees)
    }

    //recursive clear tree algorithm, sets root to null.
    bool clearTree() {
        clearTree(root);
        root = NULL;
        return true;
    }
    void clearTree(Node* node) {
        if (node == NULL) {
            return;
        }
        else {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
    //function returns true if node is present
    bool findNode(const T &data) {
        Node* currentNode = root;
        if (root == NULL) {
            return false;
        }
        while (currentNode->data != data) {
            if (currentNode->right == NULL && currentNode->left == NULL && currentNode->data != data) {
                return false;
            }
            if (currentNode->right != NULL) {
                if (data > currentNode->data) {
                    currentNode = currentNode->right;
                    continue;
                }
            }
            if (currentNode->left != NULL) {
                if (data < currentNode->data) {
                    currentNode = currentNode->left;
                    continue;
                }
            }
            return false;
        }
        return true;
    }



};
#endif //LAB_11_AVL_AVL_H
