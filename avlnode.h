/*************************************************
 * Class: AVLNode
 * Owner: Courtney Kent
 *************************************************/

#ifndef AVLNODE_H
#define AVLNODE_H

#include <set>
#include <string>
#include <unordered_map>

#include <entry.h>
using namespace std;

class AVLTreeNode {
private:
   string keyword;
   unordered_map<string, set<Entry*> > table;
   // Other data fields can be inserted here
   AVLTreeNode *left;
   AVLTreeNode *right;
   AVLTreeNode *parent;
   char balanceFactor;

public:
   string getKeyword() {return keyword;}
   unordered_map<string, set<Entry*>> getDocAndWeights() {return table;}
   AVLTreeNode* getLeft() {return left;}
   AVLTreeNode* getRight() {return right;}
   AVLTreeNode* getParent() {return parent;}
   char getBalanceFactor() {return balanceFactor;}

   void setKeyword(string s) {keyword = s;}
   void setDocAndWeights(unordered_map<string, set<Entry*> > s) {table = s;}
   void setLeft(AVLTreeNode* s) {left = s;}
   void setRight(AVLTreeNode* s) {right = s;}
   void setParent(AVLTreeNode* s) {parent = s;}
   void setBalanceFactor(char s) {balanceFactor = s;}
};

#endif // AVLNODE_H
