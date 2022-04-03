#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    if (root_ == nullptr) {
      root_ = new Node(key, value);
      return;
    }

    Node* node = root_;
    while (true) {
      if (key == node->key) {
        node->value = value;
        return;
      }

      if (key > node->key) {
        if (node->right == nullptr) {
          node->right = new Node(key, value);
          return;
        }

        node = node->right;
      } else {
        if (node->left == nullptr) {
          node->left = new Node(key, value);
          return;
        }

        node = node->left;
      }
    }
  }

  bool BinarySearchTree::Remove(int key) {
    if (root_ == nullptr) {
      return false;
    }

    if (root_->key == key) {
      if (root_->left == nullptr && root_->right == nullptr) {
        delete root_;
        root_ = nullptr;
        return true;
      }

      if (root_->right == nullptr) {
        Node* new_root = root_->left;
        delete root_;
        root_ = new_root;
        return true;
      }

      if (root_->left == nullptr) {
        Node* new_root = root_->right;
        delete root_;
        root_ = new_root;
        return true;
      }

      Node to_replace = *find_min(root_->right);
      Remove(to_replace.key);
      root_->key = to_replace.key;
      root_->value = to_replace.value;
      return true;
    }

    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
      clear(root_);
      root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key, root_);
    if (node == nullptr) {
      return std::nullopt;
    }

    return node->value;
  }

  bool BinarySearchTree::Contains(int key) const {
    return Find(key).has_value();
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    Node* node = find_min(root_);
    if (node == nullptr) {
      return std::nullopt;
    }
    return node->key;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    Node* node = find_max(root_);
    if (node == nullptr) {
      return std::nullopt;
    }
    return node->key;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

//  void BinarySearchTree::insert(int key, int value, Node*& node) {
//    // Write your code here ...
//  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node == nullptr) {
      return false;
    }

    if (key > node->key) {
      if (key != node->right->key) {
        return remove(key, node->right);
      }
      Node * child = node->right;
      if (child->left == nullptr && child->right == nullptr) {
        delete child;
        node->right = nullptr;
        return true;
      }

      if (child->right == nullptr) {
        Node* new_root = child->left;
        delete child;
        node->right = new_root;
        return true;
      }

      if (root_->left == nullptr) {
        Node* new_root = child->right;
        delete child;
        node->right = new_root;
        return true;
      }

      Node to_replace = *find_min(child->right);
      remove(to_replace.key, node);
      child->key = to_replace.key;
      child->value = to_replace.value;
    } else {
      if (key != node->left->key) {
        return remove(key, node->left);
      }
      Node * child = node->left;
      if (child->left == nullptr && child->right == nullptr) {
        delete child;
        node->left = nullptr;
        return true;
      }

      if (child->right == nullptr) {
        Node* new_root = child->left;
        delete child;
        node->left = new_root;
        return true;
      }

      if (root_->left == nullptr) {
        Node* new_root = child->right;
        delete child;
        node->left = new_root;
        return true;
      }

      Node to_replace = *find_min(child->right);
      remove(to_replace.key, node);
      child->key = to_replace.key;
      child->value = to_replace.value;
    }
    return true;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr) {
      if (node->left != nullptr) {
        clear(node->left);
      }
      if (node->right != nullptr) {
        clear(node->right);
      }
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (node->key == key) {
      return node;
    }

    if (key > node->key) {
      return find(key, node->right);
    }

    return find(key, node->left);
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (node->left == nullptr) {
      return node;
    }

    return find_min(node->left);
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (node->right == nullptr) {
      return node;
    }

    return find_max(node->right);
  }

}  // namespace assignment