#ifndef ___AVL_H
#define ___AVL_H
#include "BinaryTree.h"

class AVL:public BinaryTree {
public:
    AVL(Token **elements);
    bool addTokenAVL(Token &node);
    //search είναι υλοποιημένη στην κλάση BinaryTree
    int findMaxDepth(TokenLRpointer *node);
    void rightTurn(TokenLRpointer *node);
    void leftTurn(TokenLRpointer *node);
    void RightLeft(TokenLRpointer *node);
    void LeftRight(TokenLRpointer *node);
    void restoreBalance(TokenLRpointer *node);
};


#endif //___AVL_H
