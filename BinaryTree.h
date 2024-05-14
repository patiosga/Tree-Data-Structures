#ifndef ___BINARYTREE_H
#define ___BINARYTREE_H
#include "TokenLRpointer.h"

class BinaryTree {
protected:
    TokenLRpointer *headPointer;
public:
    BinaryTree() = default; //default constructor
    BinaryTree(Token** elements);
    ~BinaryTree();
    bool addToken(Token &node);
    TokenLRpointer *searchToken(Token &node, bool &found);
};


#endif //___BINARYTREE_H
