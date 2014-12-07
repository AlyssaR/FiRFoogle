#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>
using namespace std;

class AVLTreeNode {
private:
   string keyword;
   int wordCount;
   // Other data fields can be inserted here
   AVLTreeNode *left;
   AVLTreeNode *right;
   AVLTreeNode *parent;
   char balanceFactor;

public:
   string getKeyword() {return keyword;}
   int getWordCount() {return wordCount;}
   AVLTreeNode* getLeft() {return left;}
   AVLTreeNode* getRight() {return right;}
   AVLTreeNode* getParent() {return parent;}
   char getBalanceFactor() {return balanceFactor;}

   void setKeyword(string s) {keyword = s;}
   void setwordCount(int i) {wordCount = i;}
   void setLeft(AVLTreeNode* s) {left = s;}
   void setRight(AVLTreeNode* s) {right = s;}
   void setParent(AVLTreeNode* s) {parent = s;}
   void setBalanceFactor(char s) {balanceFactor = s;}
};

#endif // AVLNODE_H
