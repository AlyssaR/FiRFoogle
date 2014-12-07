/*************************************************
 * Class: AVLTree
 * Owner: Courtney Kent
 *
 * **Adapted from Code203_3 by Dr. Rick Coleman**
 *************************************************/

//==================================================================
// Code203_Tree.cpp
// Demonstration of an AVL tree which keeps the tree nodes in as
//   near perfect balance as possible.
// Author: Dr. Rick Coleman
// Date: January 2007
//==================================================================
#include "avltree.h"

using namespace std;

//------------------------------------------------------------------
// Default constructor
//------------------------------------------------------------------
Code203_Tree::Code203_Tree()
{
   root = NULL;   // Initialize root to NULL
}

//------------------------------------------------------------------
// Class destructor
//------------------------------------------------------------------
Code203_Tree::~Code203_Tree()
{
   // Start recursive destruction of tree
   ClearTree(root);
}

//------------------------------------------------------------------
// ClearTree()
// Recursively delete all node in the tree.
//------------------------------------------------------------------
void Code203_Tree::ClearTree(AVLTreeNode *n)
{
   if(n != NULL)
   {
      ClearTree(n->getLeft());   // Recursively clear the left sub-tree
      ClearTree(n->getRight());   // Recursively clear the right sub-tree
      delete n;         // Delete this node
   }
}

//------------------------------------------------------------------
// Insert()
// Insert a new node into the tree then restore the AVL property.
// Assumes that all three pointers (left, right, and parent) have
//  already been set to NULL in the new node
//------------------------------------------------------------------
void Code203_Tree::Insert(AVLTreeNode *newNode)
{
   AVLTreeNode *temp, *back, *ancestor;

   temp = root;
   back = NULL;
   ancestor = NULL;

   // Check for empty tree first
   if(root == NULL)
   {
      root = newNode;
      return;
   }
   // Tree is not empty so search for place to insert
   while(temp != NULL) // Loop till temp falls out of the tree
   {
      back = temp;
      // Mark ancestor that will be out of balance after
      //   this node is inserted
      if(temp->getBalanceFactor() != '=')
         ancestor = temp;
      if(newNode->getKeyword() < temp->getKeyword())
         temp = temp->getLeft();
      else
         temp = temp->getRight();
   }
   // temp is now NULL
   // back points to parent node to attach newNode to
   // ancestor points to most recent out of balance ancestor

   newNode->setParent(back);   // Set parent
   if(newNode->getKeyword() < back->getKeyword())  // Insert at left
   {
      back->setLeft(newNode);
   }
   else     // Insert at right
   {
      back->setRight(newNode);
   }

   // Now call function to restore the tree's AVL property
   restoreAVL(ancestor, newNode);
}

//------------------------------------------------------------------
// restoreAVL()
// Restore the AVL quality after inserting a new node.
// @param ancestor – most recent node back up the tree that is
//            now out of balance.
// @param newNode– the newly inserted node.
//------------------------------------------------------------------
void Code203_Tree::restoreAVL(AVLTreeNode *ancestor, AVLTreeNode *newNode)
{
   //--------------------------------------------------------------------------------
   // Case 1: ancestor is NULL, i.e. balanceFactor of all ancestors' is '='
   //--------------------------------------------------------------------------------
   if(ancestor == NULL)
   {
      if(newNode->getKeyword() < root->getKeyword())       // newNode inserted to left of root
         root->setBalanceFactor('L');
      else
         root->setBalanceFactor('R');   // newNode inserted to right of root
      // Adjust the balanceFactor for all nodes from newNode back up to root
      adjustBalanceFactors(root, newNode);
   }

   //--------------------------------------------------------------------------------
   // Case 2: Insertion in opposite subtree of ancestor's balance factor, i.e.
   //  ancestor.balanceFactor = 'L' AND  Insertion made in ancestor's right subtree
   //     OR
   //  ancestor.balanceFactor = 'R' AND  Insertion made in ancestor's left subtree
   //--------------------------------------------------------------------------------
   else if(((ancestor->getBalanceFactor() == 'L') && (newNode->getKeyword() > ancestor->getKeyword())) ||
        ((ancestor->getBalanceFactor() == 'R') && (newNode->getKeyword() < ancestor->getKeyword())))
   {
      ancestor->setBalanceFactor('=');
      // Adjust the balanceFactor for all nodes from newNode back up to ancestor
      adjustBalanceFactors(ancestor, newNode);
   }
   //--------------------------------------------------------------------------------
   // Case 3: ancestor.balanceFactor = 'R' and the node inserted is
   //      in the right subtree of ancestor's right child
   //--------------------------------------------------------------------------------
   else if((ancestor->getBalanceFactor() == 'R') && (newNode->getKeyword() > ancestor->getRight()->getKeyword()))
   {
      ancestor->setBalanceFactor('='); // Reset ancestor's balanceFactor
      rotateLeft(ancestor);       // Do single left rotation about ancestor
      // Adjust the balanceFactor for all nodes from newNode back up to ancestor's parent
      adjustBalanceFactors(ancestor->getParent(), newNode);
   }

   //--------------------------------------------------------------------------------
   // Case 4: ancestor.balanceFactor is 'L' and the node inserted is
   //      in the left subtree of ancestor's left child
   //--------------------------------------------------------------------------------
   else if((ancestor->getBalanceFactor() == 'L') && (newNode->getKeyword() < ancestor->getLeft()->getKeyword()))
   {
      ancestor->setBalanceFactor('='); // Reset ancestor's balanceFactor
      rotateRight(ancestor);       // Do single right rotation about ancestor
      // Adjust the balanceFactor for all nodes from newNode back up to ancestor's parent
      adjustBalanceFactors(ancestor->getParent(), newNode);
   }

   //--------------------------------------------------------------------------------
   // Case 5: ancestor.balanceFactor is 'L' and the node inserted is
   //      in the right subtree of ancestor's left child
   //--------------------------------------------------------------------------------
   else if((ancestor->getBalanceFactor() == 'L') && (newNode->getKeyword() > ancestor->getLeft()->getKeyword()))
   {
      // Perform double right rotation (actually a left followed by a right)
      rotateLeft(ancestor->getLeft());
      rotateRight(ancestor);
      // Adjust the balanceFactor for all nodes from newNode back up to ancestor
      adjustLeftRight(ancestor, newNode);
   }

   //--------------------------------------------------------------------------------
   // Case 6: ancestor.balanceFactor is 'R' and the node inserted is
   //      in the left subtree of ancestor's right child
   //--------------------------------------------------------------------------------
   else
   {
      // Perform double left rotation (actually a right followed by a left)
          rotateRight(ancestor->getRight());
          rotateLeft(ancestor);
          adjustRightLeft(ancestor, newNode);
   }
}

//------------------------------------------------------------------
// Adjust the balance factor in all nodes from the inserted node's
//   parent back up to but NOT including a designated end node.
// @param end– last node back up the tree that needs adjusting
// @param start – node just inserted
//------------------------------------------------------------------
void Code203_Tree::adjustBalanceFactors(AVLTreeNode *end, AVLTreeNode *start)
{
    AVLTreeNode *temp = start->getParent(); // Set starting point at start's parent
    while(temp != end)
    {
        if(start->getKeyword() < temp->getKeyword())
            temp->setBalanceFactor('L');
        else
            temp->setBalanceFactor('R');
        temp = temp->getParent();
    } // end while
}

//------------------------------------------------------------------
// rotateLeft()
// Perform a single rotation left about n.  This will rotate n's
//   parent to become n's left child.  Then n's left child will
//   become the former parent's right child.
//------------------------------------------------------------------
void Code203_Tree::rotateLeft(AVLTreeNode *n)
{
   AVLTreeNode *temp = n->getRight();   //Hold pointer to n's right child
   n->setRight(temp->getLeft());      // Move temp 's left child to right child of n
   if(temp->getLeft() != NULL)      // If the left child does exist
      temp->getLeft()->setParent(n);// Reset the left child's parent
   if(n->getParent() == NULL)       // If n was the root
   {
      root = temp;      // Make temp the new root
      temp->setParent(NULL);   // Root has no parent
   }
   else if(n->getParent()->getLeft() == n) // If n was the left child of its' parent
      n->getParent()->setLeft(temp);   // Make temp the new left child
   else               // If n was the right child of its' parent
      n->getParent()->setRight(temp);// Make temp the new right child

   temp->setLeft(n);         // Move n to left child of temp
   n->setParent(temp);         // Reset n's parent
}

//------------------------------------------------------------------
// rotateRight()
// Perform a single rotation right about n.  This will rotate n's
//   parent to become n's right child.  Then n's right child will
//   become the former parent's left child.
//------------------------------------------------------------------
void Code203_Tree::rotateRight(AVLTreeNode *n)
{
   AVLTreeNode *temp = n->getLeft();   //Hold pointer to temp
   n->setLeft(temp->getRight());      // Move temp's right child to left child of n
   if(temp->getRight() != NULL)      // If the right child does exist
      temp->getRight()->setParent(n);// Reset right child's parent
   if(n->getParent() == NULL)       // If n was root
   {
      root = temp;      // Make temp the root
      temp->setParent(NULL);   // Root has no parent
   }
   else if(n->getParent()->getLeft() == n) // If was the left child of its' parent
      n->getParent()->setLeft(temp);   // Make temp the new left child
   else               // If n was the right child of its' parent
      n->getParent()->setRight(temp);// Make temp the new right child

   temp->setRight(n);         // Move n to right child of temp
   n->setParent(temp);         // Reset n's parent
}

//------------------------------------------------------------------
// adjustLeftRight()
// @param end- last node back up the tree that needs adjusting
// @param start - node just inserted
//------------------------------------------------------------------
void Code203_Tree::adjustLeftRight(AVLTreeNode *end, AVLTreeNode *start)
{
    if(end == root)
        end->setBalanceFactor('=');
    else if(start->getKeyword() < end->getParent()->getKeyword())
    {
        end->setBalanceFactor('R');
        adjustBalanceFactors(end->getParent()->getLeft(), start);
    }
    else
    {
        end->setBalanceFactor('=');
        end->getParent()->getLeft()->setBalanceFactor('L') ;
        adjustBalanceFactors(end, start);
    }
}

//------------------------------------------------------------------
// adjustRightLeft
// @param end- last node back up the tree that needs adjusting
// @param start - node just inserted
//------------------------------------------------------------------
void Code203_Tree::adjustRightLeft(AVLTreeNode *end, AVLTreeNode *start)
{
    if(end == root)
        end->setBalanceFactor('=');
    else if(start->getKeyword() > end->getParent()->getKeyword())
    {
        end->setBalanceFactor('L');
        adjustBalanceFactors(end->getParent()->getRight(), start);
    }
    else
    {
        end->setBalanceFactor('=');
        end->getParent()->getRight()->setBalanceFactor('R');
        adjustBalanceFactors(end, start);
    }
}

//------------------------------------------------------------------
// PrintTree()
// Intiate a recursive traversal to print the tree
//------------------------------------------------------------------
void Code203_Tree::PrintTree()
{
   cout << "\nPrinting the tree...\n";
   cout << "Root Node: " << root->getKeyword() << " balanceFactor is " <<
      root->getBalanceFactor() << "\n\n";
   Print(root);
}

//------------------------------------------------------------------
// Print()
// Perform a recursive traversal to print the tree
//------------------------------------------------------------------
void Code203_Tree::Print(AVLTreeNode *n)
{
   if(n != NULL)
   {
      cout<<"Node: " << n->getKeyword() << " balanceFactor is " <<
         n->getBalanceFactor() << "\n";
      if(n->getLeft() != NULL)
      {
         cout<<"\t moving left\n";
         Print(n->getLeft());
         cout<<"Returning to Node" << n->getKeyword() << " from its' left subtree\n";
      }
      else
      {
         cout<<"\t left subtree is empty\n";
      }
      cout<<"Node: " << n->getKeyword() << " balanceFactor is " <<
         n->getBalanceFactor() << "\n";
      if(n->getRight() != NULL)
      {
         cout<<"\t moving right\n";
         Print(n->getRight());
         cout<<"Returning to Node" << n->getKeyword() << " from its' right subtree\n";
      }
      else
      {
         cout<<"\t right subtree is empty\n";
      }
   }
}

 AVLTreeNode* Code203_Tree::find(string word, AVLTreeNode* &p)
{
    if (p == nullptr) {
        return nullptr;
    }
    else {
        if (word < p->getKeyword()) {
            AVLTreeNode* left = p->getLeft();
            find(word, left);
        }
        else {
            if (word > p->getKeyword()) {
                AVLTreeNode* right = p->getRight();
                find(word, right);
            }
            else {
                return p;
            }
        }
    }
}
