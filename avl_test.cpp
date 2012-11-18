#include "AVL.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

int main() {
   
  int SIZE=20;
  vector<int> v(SIZE);  
  AVL<int>* avl = new AVL<int>();
  srand(time(0));  

  for (int i=0;i<SIZE;i++) {
    v[i] = 5*i;
  }
  random_shuffle(v.begin(),v.end());

  cout << "Multiples of 5 from 0 to 95 have been shuffled." << endl;
  cout << "They will be inserted into an AVL tree in the following order:" << endl << endl;  
  for (int i=0;i<SIZE;i++) {
    cout << v[i] << endl;
  }
  cout << endl;

  for (int i=0;i<SIZE;i++) {
    avl->insert(v[i]);
    cout << "After Inserting " << v[i] << endl << endl;
    avl->print();
  }
  cout << "In Order Traversal: " << endl;
  avl->inOrderTraversal();
  cout << endl << "Post Order Traversal: " << endl;
  avl->postOrderTraversal();
  cout << endl;
  
  cout << "Now the shuffled numbers will be removed from the AVL tree ";
  cout << "in the order they were inserted." << endl << endl;
  for (int i=0;i<SIZE;i++) {
    avl->remove(v[i]);
    cout << "After Removing " << v[i] << endl << endl;
    avl->print();
  }
  
  avl->removeTree(); 
  srand(time(0)); 

  cout << "Now 20 random numbers between 0 and 99 will be inserted into an AVL tree in this order.";
  cout << endl;
  for (int i=0;i<SIZE;i++) {
    v[i] = rand() % 100;
    cout << v[i] << endl;
  }
  cout << endl;
  
  for (int i=0;i<SIZE;i++) {
    avl->insert(v[i]);
    cout << "After Inserting " << v[i] << endl << endl;
    avl->print();
  }

  cout << "In Order Traversal: " << endl;
  avl->inOrderTraversal();
  cout << endl << "Post Order Traversal: " << endl;
  avl->postOrderTraversal();
  cout << endl;
  
  for (int i=0;i<SIZE;i++) {
    avl->remove(v[i]);
    cout << "After Removing " << v[i] << endl << endl;
    avl->print();
  }

  avl->removeTree();

  cout << "Now the numbers from 1 to 20 will be inserted into an AVL tree in order." << endl;
  cout << "They will be removed in the same order." << endl;
  for (int i=0;i<SIZE;i++) {
    v[i] = i+1;
    cout << v[i] << endl;
  }
  cout << endl;

  for (int i=0;i<SIZE;i++) {
    avl->insert(v[i]);
    cout << "After Inserting " << v[i] << endl << endl;
    avl->print();
  }

  cout << "In Order Traversal: " << endl;
  avl->inOrderTraversal();
  cout << endl << "Post Order Traversal: " << endl;
  avl->postOrderTraversal();
  cout << endl;
  
  for (int i=0;i<SIZE;i++) {
    avl->remove(v[i]);
    cout << "After Removing " << v[i] << endl << endl;
    avl->print();
  }

  avl->removeTree();

  cout << "Now the numbers from 1 to 20 will be inserted into an AVL tree in order." << endl;
  cout << "They will be removed in REVERSE order." << endl;
  for (int i=0;i<SIZE;i++) {
    v[i] = i+1;
    cout << v[i] << endl;
  }
  cout << endl;

  for (int i=0;i<SIZE;i++) {
    avl->insert(v[i]);
    cout << "After Inserting " << v[i] << endl << endl;
    avl->print();
  }

  cout << "In Order Traversal: " << endl;
  avl->inOrderTraversal();
  cout << endl << "Post Order Traversal: " << endl;
  avl->postOrderTraversal();
  cout << endl;
  
  for (int i=0;i<SIZE;i++) {
    avl->remove(v[SIZE-1-i]);
    cout << "After Removing " << v[SIZE-1-i] << endl << endl;
    avl->print();
  }

  delete avl;


/*
  AVL<int>* avl = new AVL<int>();
  avl->insert(1);
  avl->insert(2);
  avl->print();
  avl->insert(3);
  avl->print();
  avl->insert(4);
  avl->print();
  avl->insert(5);
  avl->print();
  avl->insert(6);
  avl->print();
  avl->insert(7);
  avl->print();
  avl->insert(8);
  avl->insert(9);
  avl->print();  
  avl->insert(10);
  avl->print();
  avl->inOrderTraversal();
  avl->postOrderTraversal();

  
  avl->remove(1);
  avl->print();  
  avl->remove(2);
  avl->print();  
  avl->remove(3);
  avl->print();  
  avl->remove(4);
  avl->print();
  avl->remove(5);
  avl->print();  
  avl->remove(6);
  avl->print();  
  avl->remove(7);
  avl->print();  
  avl->remove(8);
  avl->print();
  avl->remove(9);
  avl->print();
  avl->remove(10);
  avl->print();  

  avl->insert(5);
  avl->print();
  avl->insert(18);
  avl->print();
  avl->insert(25);
  avl->insert(2);
  avl->insert(1);
  avl->print();
  avl->remove(18);
  avl->print();
  delete avl;

  AVL<int>* a = new AVL<int>();
  a->insert(400);
  a->print();
  a->remove(5);
  a->print();
  a->remove(400);
  a->print();
  delete a;
*/

/*
  AVL<double>* d = new AVL<double>();
  d->insert(1);
  d->insert(2);
  d->insert(4);
  d->print();
  d->insert(3.5);
  d->insert(5);
  d->print();
  d->insert(3.25);
  d->print();

  delete d;

  AVL<int>* a1 = new AVL<int>();
  a1->insert(10);
  a1->insert(20);
  a1->insert(30);
  a1->insert(40);
  a1->print();
  a1->insert(35);
  a1->print();
  delete a1;

  AVL<int> a2;
  a2.insert(3);
  a2.insert(2);
  a2.insert(1);
  a2.insert(4);
  a2.print();
  a2.insert(5);
  a2.print();
  a2.insert(6);
  a2.print();
  a2.insert(7);
  a2.print();
  a2.insert(16);
  a2.print();
  a2.insert(15);
  a2.print();
  a2.insert(14);
  a2.print();
  a2.remove(7);
  a2.print();
  a2.remove(4);
  a2.print();
*/
/*
  AVL<double>* db=new AVL<double>();
  db->insert(7.5);
  db->insert(12.98);
  db->insert(3.45);
  db->insert(-2.58);
  db->insert(99.1);
  db->print();
  db->remove(12.98);
  db->remove(7.5);
  db->remove(5.34353);
  db->print();
  delete db;

  AVL<int>* b=new AVL<int>();
  b->insert(10);
  b->insert(5);
  b->insert(15);
  b->insert(1);
  b->insert(7);
  b->insert(11);
  b->insert(17);
  b->insert(18);
  b->insert(12);
  b->insert(14);
  b->insert(19);
  b->insert(8);
  b->insert(9);

  b->print();
 
  b->remove(15);
  b->remove(12);
  b->remove(10);
  b->print();
  b->remove(19);
  b->print();

  delete b;
*/

}
