#pragma once
#include <memory>

template<typename T>
struct TreeNode
{
     T item;
     std::unique_ptr<TreeNode<T>> left;
     std::unique_ptr<TreeNode<T>> right;

     explicit TreeNode(T val) : item(val) {};
};

template<typename T>
class BST {
private:
     std::unique_ptr<TreeNode<T>> root;

public:
     BST() : root(nullptr) {};

     TreeNode<T>* search(T target);
     TreeNode<T>* search(TreeNode<T>* node, T target);

     void insert(T item);
     void insert(std::unique_ptr<TreeNode<T>>& node, T item);

     void remove(T target);
     void remove(std::unique_ptr<TreeNode<T>>& node, T target);

     void inorder();
     void inorder(TreeNode<T>* node);

     void preorder();
     void preorder(TreeNode<T>* node);

     void postorder();
     void postorder(TreeNode<T>* node);

     bool isEmpty();

     int countNodes();
     int countNodes(TreeNode<T>* node);

     int getHeight();
     int getHeight(TreeNode<T>* node);

     bool isBalanced();
     bool isBalanced(TreeNode<T>* node);
};

template<typename T>
int BST<T>::countNodes() {
     if (!root) {
          return 0;
     }
     return countNodes(root.get());
}

template<typename T>
int BST<T>::countNodes(TreeNode<T>* node) {
     if (!node) {
          return 0;
     }
     return 1 + countNodes(node->left.get()) + countNodes(node->right.get());
}

template<typename T>
int BST<T>::getHeight() {
     if (!root) {
          return 0;
     }
     return getHeight(root.get());
}

template<typename T>
int BST<T>::getHeight(TreeNode<T>* node) {
     if (!node) {
          return 0;
     }

     int leftHeight = getHeight(node->left.get());
     int rightHeight = getHeight(node->right.get());

     return 1 + std::max(leftHeight, rightHeight);
}

template<typename T>
bool BST<T>::isBalanced() {
     if (!root) {
          return true;
     }
     return isBalanced(root.get());
}

template<typename T>
bool BST<T>::isBalanced(TreeNode<T>* node) {
     if (!node) {
          return true;
     }

     int leftHeight = getHeight(node->left.get());
     int rightHeight = getHeight(node->right.get());

     if (std::abs(leftHeight - rightHeight) > 1) {
          return false;
     }

     return isBalanced(node->left.get()) && isBalanced(node->right.get());
}
