#include <string>
#include <cassert>
#include "Node.h"

template <typename T>
Node<T>::Node(T v) {
  value = v;
  balance = 0;
  leftChild = 0;
  rightChild = 0;
}

template <typename T>
T Node<T>::getValue() {
  assert(this!=0);
  return value;
}

template <typename T>
void Node<T>::setValue(T v) {
  assert(this!=0);
  value = v;
}

template <typename T>
short Node<T>::getBalance() {
  assert(this!=0);
  return balance;
}

template <typename T>
void Node<T>::setBalance(short b) {
  assert(this!=0);
  balance = b;
}

template <typename T>
Node<T>* Node<T>::getLeftChild() {
  assert(this!=0);
  return leftChild;
}

template <typename T>
void Node<T>::setLeftChild(Node<T>* lc) {
  assert(this!=0);
  leftChild = lc;
}

template <typename T>
Node<T>* Node<T>::getRightChild() {
  assert(this!=0);
  return rightChild;
}

template <typename T>
void Node<T>::setRightChild(Node<T>* rc) {
  assert(this!=0);
  rightChild = rc;
}

template class Node<int>;
template class Node<double>;
//template class Node<std::string>;

