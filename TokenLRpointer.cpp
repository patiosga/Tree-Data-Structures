#include "TokenLRpointer.h"


TokenLRpointer::TokenLRpointer(const string& value):Token(value) {
    left = right = parent = nullptr;
    balance = 0;
    depth = 1;
}

TokenLRpointer *TokenLRpointer::getRightToken() {
    return right;
}

TokenLRpointer *TokenLRpointer::getLeftToken() {
    return left;
}

void TokenLRpointer::setLeftToken(TokenLRpointer *temp) {
    left = temp;
}

void TokenLRpointer::setRightToken(TokenLRpointer *temp) {
    right = temp;
}

void TokenLRpointer::setParent(TokenLRpointer *temp) {
    parent = temp;
}

TokenLRpointer *TokenLRpointer::getParent() {
    return parent;
}

int TokenLRpointer::getDepth() {
    return depth;
}

int TokenLRpointer::getBalance() {
    return balance;
}

void TokenLRpointer::setDepth(int y) {
    depth = y;
}

void TokenLRpointer::setBalance(int x) {
    balance = x;
}
