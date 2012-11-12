#ifndef __NODE_H__
#define __NODE_H__

template <typename T>
class Node {
 private:
  T value;
  short balance;
  Node<T>* leftChild;
  Node<T>* rightChild;

 public:
  Node<T>(T v);

  T getValue();
  void setValue(T v);

  short getBalance();
  void setBalance(short b);

  Node<T>* getLeftChild();
  void setLeftChild(Node<T>* n);

  Node<T>* getRightChild();
  void setRightChild(Node<T>* n);
};
#endif
