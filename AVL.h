#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>
#include <cassert>

template <typename T>
class AVL {
 private:
  Node<T>* root;
  
  void traversalPrint(Node<T>* root);
  Node<T>* findNode(T val,Node<T>* curr,Node<T>* &parent,bool &isLC,bool &isRC);
  Node<T>* findIOP(Node<T>* curr, Node<T>* &parent);
  Node<T>* findIOS(Node<T>* curr, Node<T>* &parent);
  void removeTree(Node<T>* curr);
  void printTree();
  void printSpaces(int n);
  
 public:
  AVL<T>();
  ~AVL<T>();

  bool find(T v);
  void remove(T v);
  void removeMutable(T v);
  void removeStd(T v);
  void insert(T v);
  void print();
};


#endif
