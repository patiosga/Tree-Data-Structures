#ifndef ___TOKENLRPOINTER_H
#define ___TOKENLRPOINTER_H
#include "Token.h"

class TokenLRpointer:public Token {
private:
    TokenLRpointer *right,*left;
    //Μόνο για το AVL:
    TokenLRpointer *parent;
    int depth, balance; //depth: μέγιστο βάθος υποδέντρου, balance = βάθος δεξιού - βάθος αριστερού (πρέπει -1<=balance<=1)
public:
    TokenLRpointer(const string& value);
    TokenLRpointer *getRightToken();
    TokenLRpointer *getLeftToken();
    TokenLRpointer *getParent();
    int getDepth();
    int getBalance();
    void setRightToken(TokenLRpointer *temp);
    void setLeftToken(TokenLRpointer *temp);
    void setParent(TokenLRpointer *temp);
    void setDepth(int y);
    void setBalance(int x);
};


#endif //___TOKENLRPOINTER_H
