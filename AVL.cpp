#include "AVL.h"
#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


template <typename T>
Node<T>* AVL<T>::findNodeAVL(T val, Node<T>* curr, Node<T>* &parent,bool &isLC, bool &isRC,
                 vector<Node<T>* > &nV, vector<short> &bV) {
  if (curr==0)
    return 0;
  else if (curr->getValue()==val) {
    nV.push_back(curr);
    bV.push_back(curr->getBalance());
    return curr;
  }
  else if (curr->getValue()>val) {
    nV.push_back(curr);
    bV.push_back(curr->getBalance());
    isLC=true;
    isRC=false;
    parent=curr;
    return findNodeAVL(val,curr->getLeftChild(),parent,isLC,isRC,nV,bV);
  }
  else {
    nV.push_back(curr);
    bV.push_back(curr->getBalance());
    isLC=false;
    isRC=true;
    parent=curr;
    return findNodeAVL(val,curr->getRightChild(),parent,isLC,isRC,nV,bV);
  }
}

template <typename T>
Node<T>* AVL<T>::findIOPAVL(Node<T>* curr, Node<T>* &parent, vector<Node<T>* > &nV, vector<short> &bV) {
  if (curr==0) 
    return 0;   
  else if (curr->getLeftChild()==0)
    return 0;
  else {
    parent=curr;
    curr=curr->getLeftChild();
    nV.push_back(curr);
    bV.push_back(curr->getBalance());
  }
    
  while (curr->getRightChild()!=0) {
    parent=curr;
    curr=curr->getRightChild();
    nV.push_back(curr);
    bV.push_back(curr->getBalance());
  }
  
  return curr;
}

template <typename T>
Node<T>* AVL<T>::findIOSAVL(Node<T>* curr, Node<T>* &parent, vector<Node<T>* > &nV, 
                 vector<short> &bV) {
  if (curr==0) 
    return 0;   
  else if (curr->getRightChild()==0)
    return 0;
  else {
    parent=curr;
    curr=curr->getRightChild();
    nV.push_back(curr);
    bV.push_back(curr->getBalance());
  }

  while (curr->getLeftChild()!=0) {
    parent=curr;
    curr=curr->getLeftChild();
    nV.push_back(curr);
    bV.push_back(curr->getBalance());
  }

  return curr;
}

template <typename T>
Node<T>* AVL<T>::findNode(T val,Node<T>* curr,Node<T>* &parent,bool &isLC, bool &isRC) {
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
Node<T>* AVL<T>::findIOP(Node<T>* curr,Node<T>* &parent) {
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
Node<T>* AVL<T>::findIOS(Node<T>* curr,Node<T>* &parent) {
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
void AVL<T>::removeTree(Node<T>* curr) {
  if (curr!=0) {
    removeTree(curr->getLeftChild());
    removeTree(curr->getRightChild());
    delete curr;
  }
}

template <typename T>
AVL<T>::AVL() {
  root = 0;
}

template <typename T>
AVL<T>::~AVL() {
  removeTree(root);  
}

template <typename T>
bool AVL<T>::find(T v) {

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
void AVL<T>::insert(T v) {

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
  // store these updated balances in the vector balVec

  curr=critNode;
  vector<Node<T>* > nodeVec;
  vector<short> balVec;

  while (curr!=newNode) {
    if (v<curr->getValue()) {
      curr->setBalance((curr->getBalance())-1);
      nodeVec.push_back(curr);
      balVec.push_back(curr->getBalance());
      curr=curr->getLeftChild();
    }
    else if (v>curr->getValue()) {
      curr->setBalance((curr->getBalance())+1);
      nodeVec.push_back(curr);
      balVec.push_back(curr->getBalance());
      curr=curr->getRightChild();
    }
  }

  // adjust balances of nodes to their post-rotation state prior to rotating them 
  // adjust the balances prior to rotation

  if (critNode->getBalance()==2 || critNode->getBalance()==-2) {
    updateBalances(nodeVec,balVec);
  }
  else
    return; // if critNode has balance == -1, 0, or 1 no need to do rotations

  // if critNode has balance==+-2, we need to rotate
  // below, rotate method finds out what kind of rotation to do and does it 

  rotate(balVec,critNode,critPrev);
  
}

template <typename T>
void AVL<T>::updateBalances(vector<Node<T>* > &nV,vector<short> &bV) {

  // three nodes in a row after rotation leads to 0 balances for all nodes
  // (+-2,+-1) leads to (0,0)
  if (bV.size()==2 && bV[1]!=0) {
    nV[0]->setBalance(0);
    nV[1]->setBalance(0);
    return;
  }
   
  // in the remove method, we encounter different balance sequences such as (2,0) and (-2,0)
  // this sequence leads to (1,-1) or (-1,1) and does not propagate upward
  else if (bV[1]==0) {
    nV[0]->setBalance(bV[0]/2);
    nV[1]->setBalance(-bV[0]/2);
    return;
  }

  // one right or left rotation leads to 0 balance for crit node and child
  // (2,1,bV[2]) or (-2,-1,bV[2]) leads to (0,0,bV[2]) (really same case as above)
  else if (bV[0]==(2*bV[1])) {
    nV[0]->setBalance(0);
    nV[1]->setBalance(0);
    return;
  }
  
  // (2,-1,1) or (-2,1,-1) leads to (bV[1],0,0)
  else if (bV[0]==(2*bV[2])) {
    nV[0]->setBalance(bV[1]);
    nV[1]->setBalance(0);
    nV[2]->setBalance(0);
    return;
  }

  // (2,-1,-1) or (-2,1,1) leads to (0,-bV[1],0)
  else if (bV[0]==(-2*bV[2])) {
    nV[0]->setBalance(0);
    nV[1]->setBalance(-bV[1]);
    nV[2]->setBalance(0);
    return;
  }

  // (2,-1,0) or (-2,1,0) leads to (0,0,0)
  // this is impossible for insert method but comes up in remove method
  else if (bV[0]==-2*bV[1] && bV[2]==0) {
    nV[0]->setBalance(0);
    nV[1]->setBalance(0);
  }
 
  // shouldn't ever execute this code!
  else {
  }

}

template <typename T>
void AVL<T>::leftRotation(Node<T>* &cNode,Node<T>* &prevCNode) {
  Node<T>* temp=cNode->getRightChild()->getLeftChild();
  if (root==cNode) {
    root=cNode->getRightChild();
    root->setLeftChild(cNode);
    cNode->setRightChild(temp);
  }
  else {
    if (prevCNode->getRightChild()==cNode) {
      prevCNode->setRightChild(cNode->getRightChild());
    }
    else { 
      prevCNode->setLeftChild(cNode->getRightChild());  
    }
    cNode->getRightChild()->setLeftChild(cNode);
    cNode->setRightChild(temp);
  }
}

template <typename T>
void AVL<T>::rightRotation(Node<T>* &cNode,Node<T>* &prevCNode) {
  Node<T>* temp=cNode->getLeftChild()->getRightChild();
  if (root==cNode) {
    root=cNode->getLeftChild();
    root->setRightChild(cNode);
    cNode->setLeftChild(temp);
  }
  else {
    if (prevCNode->getLeftChild()==cNode) {
      prevCNode->setLeftChild(cNode->getLeftChild());
    }
    else { 
      prevCNode->setRightChild(cNode->getLeftChild());  
    }
    cNode->getLeftChild()->setRightChild(cNode);
    cNode->setLeftChild(temp);
  }
}

template <typename T>
void AVL<T>::remove(T v) {

  bool isLC=false;  // remNode is LC of parent?
  bool isRC=false;  // remNode is RC of parent?
  Node<T>* parent=0;
  vector<Node<T>* > nV;
  vector<short> bV;
  Node<T>* remNode=findNodeAVL(v,root,parent,isLC,isRC,nV,bV); // node to be removed
  
  if (remNode==0) // remNode not in tree
    return;

  Node<T>* remLCNode=remNode->getLeftChild();  // LC of node to be removed
  Node<T>* remRCNode=remNode->getRightChild(); // RC of node to be removed

  if (remLCNode==0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(0);
      propagateBalances(nV,bV);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(0);
      propagateBalances(nV,bV);
      delete remNode;
    }
    else {
      root=0;
      propagateBalances(nV,bV);
      delete remNode;
    }
  }
  else if (remLCNode==0 && remRCNode!=0) {
    if (isLC) {
      parent->setLeftChild(remRCNode);
      propagateBalances(nV,bV);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      propagateBalances(nV,bV);     
      delete remNode;
    }
    else {
      root=remRCNode;
      propagateBalances(nV,bV);
      delete remNode;
    }

  }
  else if (remLCNode!=0 && remRCNode==0) {
    if (isLC) {
      parent->setLeftChild(remLCNode);
      propagateBalances(nV,bV);
      delete remNode;
    }
    else if (isRC) {
      parent->setRightChild(remRCNode);
      propagateBalances(nV,bV);
      delete remNode;
    }
    else {
      root=remLCNode;
      propagateBalances(nV,bV);
      delete remNode;
    }
  }

  else {  // remNode has two children (need to use IOS or IOP)
    Node<T>* iopParent=0;
    Node<T>* iop=findIOPAVL(remNode,iopParent,nV,bV);
    T iopVal;

    if (iop!=0) {
      iopVal=iop->getValue();
      propagateBalances(nV,bV);
      remove01(iop->getValue());
      remNode->setValue(iopVal);
    }  
  }

  // go through balance vector toward root and find balances of +-2
 
  Node<T>* curr=0;
  Node<T>* prev=0;
  vector<Node<T>* > rotNV;
  vector<short> rotBV;
  while (bV.size()>0) {
    if (bV[bV.size()-1]>1 || bV[bV.size()-1]<-1) {

      curr=nV[nV.size()-1];

      if (nV.size()>1)
        prev=nV[nV.size()-2];
      else
        prev=0;
 
      findRotateVectors(curr,rotNV,rotBV);

      if (rotBV[1]!=0)
        propagateBalances(nV,bV);
      else {
        bV.pop_back();
        nV.pop_back();
      }  

      updateBalances(rotNV,rotBV);
      
      rotate(rotBV,curr,prev);  

    }
    else {
      bV.pop_back();
      nV.pop_back();
    }
  }  

}

template <typename T>
void AVL<T>::propagateBalances(vector<Node<T>* > &nV, vector<short> &bV) {
  
  unsigned int depth=nV.size()-1;
  
  for (unsigned int i=0;i<depth;i++) {
    if (nV[depth-i-1]->getValue()>nV[depth-i]->getValue()) {
      bV[depth-i-1]=(nV[depth-i-1]->getBalance())+1;
      nV[depth-i-1]->setBalance(bV[depth-i-1]);
      if (bV[depth-i-1]>=1)
        break;
    }
    else {
      bV[depth-i-1]=(nV[depth-i-1]->getBalance())-1;  
      nV[depth-i-1]->setBalance(bV[depth-i-1]);
      if (bV[depth-i-1]<=-1)
        break;
    }
  }
  nV.pop_back();
  bV.pop_back(); 
} 

template <typename T>
void AVL<T>::findRotateVectors(Node<T>* curr, vector<Node<T>* > &nV, vector<short> &bV) {
  
  nV.push_back(curr);
  bV.push_back(curr->getBalance());
  
  if (bV[0]==2)
    nV.push_back(curr->getRightChild());
  else
    nV.push_back(curr->getLeftChild());
  bV.push_back(nV[1]->getBalance());
  
  if (bV[1]==2*bV[0] || bV[1]==0)
    return;
  else {
    if (bV[1]>0)
      nV.push_back(nV[1]->getRightChild());
    else
      nV.push_back(nV[1]->getLeftChild());
  }
  bV.push_back(nV[2]->getBalance());

}

template <typename T>
void AVL<T>::rotate(vector<short> &balVec,
             Node<T>* &critNode, Node<T>* &critPrev) {
 
  Node<T>* child=0;
  
  if (balVec[0]==2 && balVec[1]!=-1) {    
    // simple left rotation
    leftRotation(critNode,critPrev);
  }
   
  else if (balVec[0]==-2 && balVec[1]!=1) {
    // simple right rotation
    rightRotation(critNode,critPrev);
  }

  else if (balVec[0]==2 && balVec[1]==-1) {
    // right then left rotation
    child=critNode->getRightChild();
    rightRotation(child,critNode);
    leftRotation(critNode,critPrev);
  }

  else if (balVec[0]==-2 && balVec[1]==1) {
    // left then right rotation
    child=critNode->getLeftChild();
    leftRotation(child,critNode);
    rightRotation(critNode,critPrev);
  }

}

template <typename T>
void AVL<T>::remove01(T v) {

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

}

template <typename T>
void AVL<T>::print() {
  printTree(); 
}

template <typename T>
void AVL<T>::inOrderTraversal(Node<T>* root) {
  if(root != 0) {
    inOrderTraversal(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    inOrderTraversal(root->getRightChild());
  }
}

template <typename T>
void AVL<T>::inOrderTraversal() {
  cout << endl;
  inOrderTraversal(root);
  cout << endl;
}


template <typename T>
void AVL<T>::postOrderTraversal(Node<T>* root) {
  if(root != 0) {
    postOrderTraversal(root->getLeftChild());
    postOrderTraversal(root->getRightChild());
    std::cout << root->getValue() << std::endl;
  }
}

template <typename T>
void AVL<T>::postOrderTraversal() {
  cout << endl;
  postOrderTraversal(root);
  cout << endl;
}

template <typename T>
void AVL<T>::printTree() {
  
  if (root==0)
    return;

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
void AVL<T>::printSpaces(int n) {
  for (int i=0;i<n;i++) {
    cout << " ";
  }
}

template class AVL<int>;
template class AVL<double>;
//template class AVL<std::string>;
