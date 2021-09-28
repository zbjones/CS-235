//
// Created by zacha on 3/13/2020.
//

#ifndef LAB_8_BST_BST_H
#define LAB_8_BST_BST_H
#include <string>
#include <sstream>
#include "BSTInterface.h"


//NOTE: No .cpp file here because of the templated nature of the class and the BST interface.h file.  This has been
//seen before in other labs!!! Its totally okay.


template<typename T>
class BST : public BSTInterface<T> {

private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& d, Node* l, Node* r) : data(d), left(l), right(r) { }
    };
    Node* root;

public:
    BST() { this->root = NULL; }
    ~BST() {
        clearTree();
    }
    //recursive addNodes functions taken in user data and recursively adds it to the approriate location in the BST
    bool addNode(const T& userData) {
        return addNode(root, userData);
    }
    bool addNode(BST::Node*& node, const T &userData) {
        if (node == NULL) {
            node = new Node(userData, NULL, NULL);
            return true;
        }
        else if (node->data == userData) {
            return false;
        }
        else if (userData < node->data) {
            return addNode(node->left, userData);
        }
        else if (userData > node->data) {
            return addNode(node->right, userData);
        }
        return true;
    }

    //returns a string that prints the BST in an intuitive manner
    std::string toString() const {
        std::stringstream out;
        if (root == NULL) out << " empty";
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
    bool removeNode(Node* node, const T &userData) {
        Node* parentNode = NULL;
        findParentNode(node, userData, parentNode); //gets parentNode and keeps track of it
        if (userData < node->data) { //recursive call to continue traversing tree
            return removeNode(node->left, userData);
        }
        else if (userData > node->data) {
            return removeNode(node->right, userData);
        }

        //The no children cases
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
                    delete root;
                    root = NULL;
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
                return true;
            }
            else { //two children case
                Node* inOrderPredecessor = getInorderPredecessor(node); // use helper function to get inorder predecessor
                swap(node, inOrderPredecessor); //swap data with predecessor
                return removeNode(inOrderPredecessor, userData); //call recursive remove on that value
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
    //helper function to get the parent node at any location, passes by reference
    void findParentNode(Node*& currentNode, const T &data, BST::Node*& parentNode) {
        currentNode = root;
        while (currentNode != NULL && currentNode->data != data) {
            parentNode = currentNode;
            if (currentNode->left) {
                if (currentNode->left->data == data) {
                    parentNode = currentNode;
                    currentNode = currentNode->left;
                    return;
                }
            }
            if (currentNode->right) {
                if (currentNode->right->data == data) {
                    parentNode = currentNode;
                    currentNode = currentNode->right;
                    return;
                }
            }
            if (data < currentNode->data) {
                currentNode = currentNode->left;
            }
            else {
                currentNode = currentNode->right;
            }
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



#endif //LAB_8_BST_BST_H
