#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>
#include <vector>
#include <cassert>

using std::vector;

template <typename T>
class AVL {
 private:
  Node<T>* root;
  
  Node<T>* findNodeAVL(T val,Node<T>* curr,Node<T>* &parent,bool &isLC,bool &isRC,
           vector<Node<T>* > &nV,vector<short> &bV);
  Node<T>* findIOPAVL(Node<T>* curr, Node<T>* &parent, vector<Node<T>* > &nV,vector<short> &bV);
  Node<T>* findIOSAVL(Node<T>* curr, Node<T>* &parent, vector<Node<T>* > &nV,vector<short> &bV);
  
  Node<T>* findNode(T val,Node<T>* curr,Node<T>* &parent,bool &isLC,bool &isRC);
  Node<T>* findIOP(Node<T>* curr, Node<T>* &parent);
  Node<T>* findIOS(Node<T>* curr, Node<T>* &parent);

  void propagateBalances(vector<Node<T>* > &nV,vector<short> &bV); 
  void updateBalances(vector<Node<T>* > &nV, vector<short> &bV);
  void findRotateVectors(Node<T>* curr, vector<Node<T>* > &nV, vector<short> &bV);
  void rotate(vector<short> &bV, Node<T>* &curr, Node<T>* &prev);
  void leftRotation(Node<T>* &cNode, Node<T>* &pCNode); 
  void rightRotation(Node<T>* &cNode, Node<T>* &pCNode); 

  void removeTree(Node<T>* curr);
  void remove01(T v);
  void inOrderTraversal(Node<T>* root);
  void postOrderTraversal(Node<T>* root);
  void printTree();
  void printSpaces(int n);
  
 public:
  AVL<T>();
  ~AVL<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
  void inOrderTraversal();
  void postOrderTraversal();
};


#endif
