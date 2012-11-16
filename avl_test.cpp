#include "AVL.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {

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
  delete avl;

  AVL<int>* a = new AVL<int>();
  a->insert(10);
  a->insert(5);
  a->print();
  a->insert(15);
  a->insert(12);
  a->insert(17);
  a->insert(3);
  a->insert(7);
  a->insert(1);
  a->insert(4);
  a->insert(6);
  a->insert(8);
  a->print();
  a->insert(9);
  a->print();

  // a->print();

  delete a;
  
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
  a2.removeAVL(7);
  a2.print();
  a2.removeAVL(4);
  a2.print();

/*
  avl->insert(10);
  avl->insert(5);
  avl->insert(15);
  avl->insert(20);
  avl->insert(16);
  avl->insert(17);
  avl->insert(23);
  // avl->insert(18);
  avl->insert(24);
  avl->insert(15);
  avl->insert(21);

  avl->print();
  
  cout<<endl;
  cout<<avl->find(10)<<endl;
  cout<<avl->find(17)<<endl;
  cout<<avl->find(18)<<endl;
  cout<<avl->find(1)<<endl;
  cout<<endl;

  avl->removeMutable(20);
  avl->print();
  cout<<endl;

  avl->removeMutable(23);
  avl->print();
  cout<<endl;
 
  avl->removeMutable(10);
  avl->print();

  delete avl;

  AVL<double>* db=new AVL<double>();
  db->insert(7.5);
  db->insert(12.98);
  db->insert(3.45);
  db->insert(-2.58);
  db->insert(99.1);
  db->print();
  db->removeStd(12.98);
  db->removeStd(7.5);
  db->removeStd(5.34353);
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
