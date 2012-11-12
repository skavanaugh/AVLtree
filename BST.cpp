#include "BST.h"
#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <typename T>
Node<T>* BST<T>::findNode(T val,Node<T>* curr,Node<T>* &parent,bool &isLC, bool &isRC) {
  if (curr==0)
    return 0;
  else if (curr->getValue()==val)
    return curr;
  else if (curr->getValue()>val) {
    isLC=true;
    isRC=false;
    parent=curr;
    return findNode(val,curr->getLeftChild(),parent,isLC,isRC);
  }
  else {
    isLC=false;
    isRC=true;
    parent=curr;
    return findNode(val,curr->getRightChild(),parent,isLC,isRC);
  }
}

template <typename T>
Node<T>* BST<T>::findIOP(Node<T>* curr,Node<T>* &parent) {
  if (curr==0) 
    return 0;   
  else if (curr->getLeftChild()==0)
    return 0;
  else {
    parent=curr;
    curr=curr->getLeftChild();
  }
    
  while (curr->getRightChild()!=0) {
    parent=curr;
    curr=curr->getRightChild();
  }
  
  return curr;
}

template <typename T>
Node<T>* BST<T>::findIOS(Node<T>* curr,Node<T>* &parent) {
  if (curr==0) 
    return 0;   
  else if (curr->getRightChild()==0)
    return 0;
  else {
    parent=curr;
    curr=curr->getRightChild();
  }

  while (curr->getLeftChild()!=0) {
    parent=curr;
    curr=curr->getLeftChild();
  }

  return curr;
}

template <typename T>
void BST<T>::removeTree(Node<T>* curr) {
  if (curr!=0) {
    removeTree(curr->getLeftChild());
    removeTree(curr->getRightChild());
    delete curr;
  }
}

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  removeTree(root);  
}

template <typename T>
bool BST<T>::find(T v) {

  Node<T>* fNode=0;
  Node<T>* parent=0;
  bool isLC=false;
  bool isRC=false;

  fNode=findNode(v,root,parent,isLC,isRC);

  if (fNode==0)
    return false;
  else 
    return true;
}

template <typename T>
void BST<T>::insert(T v) {

  Node<T>* newNode=new Node<T>(v);
  Node<T>* curr=root;
  Node<T>* prev=0;
  Node<T>* critNode=root;
  Node<T>* critPrev=0;

  if (curr==0) {
    root=newNode;
    return;
  }
  else if (curr->getValue()==v) {
    delete newNode;
    return;
  }
  while (curr!=0) {
    if (curr->getBalance()==1 || curr->getBalance()==-1) {
      critPrev=prev;
      critNode=curr;
    }

    if (v<curr->getValue()) {
      prev=curr;
      curr=curr->getLeftChild();
    }
    else if (v>curr->getValue()) {
      prev=curr;
      curr=curr->getRightChild();
    }
    else {  // if v==curr->getValue()
      delete newNode;
      return;
    }
  }

  if (v<prev->getValue())
    prev->setLeftChild(newNode);
  else
    prev->setRightChild(newNode);

  // update balances from critNode down to where newNode was inserted
  curr=critNode;
  while (curr!=newNode) {
    if (v<curr->getValue()) {
      curr->setBalance((curr->getBalance())-1);
      curr=curr->getLeftChild();
    }
    else if (v>curr->getValue()) {
      curr->setBalance((curr->getBalance())+1);
      curr=curr->getRightChild();
    }
  }

  // need to rebalance anything?
  if (critNode->getBalance()==2 && critNode->getRightChild()->getBalance()!=-1) {
    // simple left rotation
    simpleLeftRotation(critNode,critPrev);
  }
   
  else if (critNode->getBalance()==-2 && critNode->getLeftChild()->getBalance()!=1) {
    // simple right rotation
    simpleRightRotation(critNode,critPrev);
  }

  else if (critNode->getBalance()==2 && critNode->getRightChild()->getBalance()==-1) {
    // right then left rotation
    simpleRightRotation(critNode->getRightChild(),critNode);
    simpleLeftRotation(critNode,critPrev);
  }

  else if (critNode->getBalance()==-2 && critNode->getLeftChild()->getBalance()==1) {
    // left then right rotation
    simpleLeftRotation(critNode->getLeftChild(),critNode);
    simpleRightRotation(critNode,critPrev);
  }
  


}

template <typename T>
void BST<T>::remove(T v) {

  bool isLC=false;  // remNode is LC of parent?
  bool isRC=false;  // remNode is RC of parent?
  Node<T>* parent=0;
  Node<T>* remNode=findNode(v,root,parent,isLC,isRC); // node to be removed
  
  if (remNode==0) // remNode not in BST
    return;

  Node<T>* remLCNode=remNode->getLeftChild();  // LC of node to be removed
  Node<T>* remRCNode=remNode->getRightChild(); // RC of node to be removed

  if (remLCNode==0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(0);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(0);
      delete remNode;
    }
    else {  
      root=0;
      delete remNode;
    }
  }
  else if (remLCNode==0 && remRCNode!=0) {
    if (isLC) {
      parent->setLeftChild(remRCNode);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      delete remNode;
    }
    else {
      root=remRCNode;
      delete remNode;
    }

  }
  else if (remLCNode!=0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(remLCNode);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      delete remNode;
    }
    else {
      root=remLCNode;
      delete remNode;
    }
  }

  else {  // remNode has two children (need to use IOS or IOP)
    Node<T>* iopParent=0;
    Node<T>* iop=findIOP(remNode,iopParent);
    Node<T>* newIOP=new Node<T>(iop->getValue());

    remove(iop->getValue());

    if (isLC) {
      parent->setLeftChild(newIOP);
      newIOP->setLeftChild(remNode->getLeftChild());
      newIOP->setRightChild(remNode->getRightChild());
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(newIOP);
      newIOP->setLeftChild(remNode->getLeftChild());
      newIOP->setRightChild(remNode->getRightChild());
      delete remNode;
    }
    else {
      newIOP->setLeftChild(remNode->getLeftChild());
      newIOP->setRightChild(remNode->getRightChild());
      root=newIOP;
      delete remNode;
    }
  }
}

template <typename T>
void BST<T>::removeMutable(T v) {

  bool isLC=false;  // remNode is LC of parent?
  bool isRC=false;  // remNode is RC of parent?
  Node<T>* parent=0;
  Node<T>* remNode=findNode(v,root,parent,isLC,isRC); // node to be removed
  
  if (remNode==0) // remNode not in BST
    return;

  Node<T>* remLCNode=remNode->getLeftChild();  // LC of node to be removed
  Node<T>* remRCNode=remNode->getRightChild(); // RC of node to be removed

  if (remLCNode==0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(0);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(0);
      delete remNode;
    }
    else {
      root=0;
      delete remNode;
    }
  }
  else if (remLCNode==0 && remRCNode!=0) {
    if (isLC) {
      parent->setLeftChild(remRCNode);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      delete remNode;
    }
    else {
      root=remRCNode;
      delete remNode;
    }

  }
  else if (remLCNode!=0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(remLCNode);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      delete remNode;
    }
    else {
      root=remLCNode;
      delete remNode;
    }
  }

  else {  // remNode has two children (need to use IOS or IOP)
    Node<T>* iopParent=0;
    Node<T>* iop=findIOP(remNode,iopParent);
    T iopVal;

    if (iop!=0) {
      iopVal=iop->getValue();
      remove(iop->getValue());
      remNode->setValue(iopVal);
    }  
  }
}

template <typename T>
void BST<T>::removeStd(T v) {

  bool isLC=false;  // remNode is LC of parent?
  bool isRC=false;  // remNode is RC of parent?
  Node<T>* parent=0;
  Node<T>* remNode=findNode(v,root,parent,isLC,isRC); // node to be removed
  
  if (remNode==0) // remNode not in BST
    return;

  Node<T>* remLCNode=remNode->getLeftChild();  // LC of node to be removed
  Node<T>* remRCNode=remNode->getRightChild(); // RC of node to be removed

  if (remLCNode==0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(0);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(0);
      delete remNode;
    }
    else {
      root=0;
      delete remNode;
    }
  }
  else if (remLCNode==0 && remRCNode!=0) {
    if (isLC) {
      parent->setLeftChild(remRCNode);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      delete remNode;
    }
    else {
      root=remRCNode;
      delete remNode;
    }
  }
  else if (remLCNode!=0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(remLCNode);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      delete remNode;
    }
    else {
      root=remLCNode;
      delete remNode;
    }
  }

  else {  // remNode has two children (need to use IOS or IOP)
    Node<T>* iopParent=0;
    Node<T>* iop=findIOP(remNode,iopParent);
    
    iop->setRightChild(remRCNode);

    if (isLC) {
      parent->setLeftChild(remLCNode);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remLCNode);
      delete remNode;
    }
    else {
      root=iop;
      delete remNode;
    }
  }
}

template <typename T>
void BST<T>::print() {
  printTree(); 
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void BST<T>::printTree() {

  bool isEmptyLevel=false; 
  int numLevels=0;

  vector<vector<Node<T>* > > levelVector;
  vector<Node<T>* > currLevel(1,root);

  if (currLevel[0]==0) {
    isEmptyLevel=true;
  }
  else {
    levelVector.push_back(currLevel);
    numLevels++;
  }

  while (isEmptyLevel==false) {  

    currLevel.resize(2*levelVector[numLevels-1].size());
    for (unsigned int i=0;i<levelVector[numLevels-1].size();i++) {
      if (levelVector[numLevels-1][i]!=0) {
        currLevel[2*i]=levelVector[numLevels-1][i]->getLeftChild();
        currLevel[2*i+1]=levelVector[numLevels-1][i]->getRightChild();
      }
      else {
        currLevel[2*i]=0;
        currLevel[2*i+1]=0;
      } 
    }
  
    for (unsigned int i=0;i<currLevel.size();i++) {
      if (currLevel[i]!=0) {
        isEmptyLevel=false;
        break;
      }
    isEmptyLevel=true;
    }
  
    if (isEmptyLevel==false) {
      levelVector.push_back(currLevel);
      numLevels++;
    }
  }   

  // now print it out

  const int WIDTH=6;
  vector<int> vStart(levelVector.size());
  vector<int> vBetween(levelVector.size());
  vStart[levelVector.size()-1]=0;
  vBetween[levelVector.size()-1]=WIDTH;
  for (unsigned int i=0;i<levelVector.size()-1;i++) {
    vStart[levelVector.size()-i-2]=vStart[levelVector.size()-i-1]
      +vBetween[levelVector.size()-i-1]/2;
    vBetween[levelVector.size()-i-2]=2*vBetween[levelVector.size()-i-1];
  }

  for (unsigned int i=0;i<levelVector.size();i++) {
    for (unsigned int j=0;j<levelVector[i].size();j++) {
      if (j==0)
        printSpaces(vStart[i]);
      else
        printSpaces(vBetween[i]-1);

      if (levelVector[i][j]!=0)
        cout << levelVector[i][j]->getValue();
      else
        cout << "X";
    }
    cout << endl << endl;
  }
  cout << endl << endl;

// the following code prints the vectors left justified (without formatting)
// i may use this code another time
/*
  for (unsigned int i=0;i<levelVector.size();i++) {
    for (unsigned int j=0;j<levelVector[i].size();j++) {
      if (levelVector[i][j]!=0)
        cout << levelVector[i][j]->getValue() << " ";
      else
        cout << "X ";
    }
    cout << endl;
  }
*/
}

template <typename T>
void BST<T>::printSpaces(int n) {
  for (int i=0;i<n;i++) {
    cout << " ";
  }
}

template class BST<int>;
template class BST<double>;
//template class BST<std::string>;
