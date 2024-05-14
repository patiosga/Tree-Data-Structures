#include "BinaryTree.h"

BinaryTree::BinaryTree(Token **elements) {
    int i;
    headPointer = new TokenLRpointer(elements[0]->getValue()); //Θέτω ρίζα του δέντρου το πρώτο στοιχείο
    for (i=1;elements[i]!= nullptr;i++) { //Ξεκινάω να βάζω στοιχεία στο δέντρο απο τη θέση 1 του πίνακα elements
        addToken(*elements[i]);
    }
}

bool BinaryTree::addToken(Token &node) {
    TokenLRpointer *temp = new TokenLRpointer(node.getValue());
    bool added = false;
    TokenLRpointer *currentNode = headPointer;
    while (!added) { //while μέχρι να φτάσω στον κατάλληλο δείκτη null και να προσθέσω το νέο στοιχείο
        if (temp->getValue()>=currentNode->getValue()) { //>= as a precaution
            if (currentNode->getRightToken()== nullptr) {
                currentNode->setRightToken(temp);
                added = true;
                return true;
            }
            else
                currentNode = currentNode->getRightToken();
        }
        else {
            if (currentNode->getLeftToken()== nullptr) {
                currentNode->setLeftToken(temp);
                added = true;
                return true;
            }
            else
                currentNode = currentNode->getLeftToken();
        }
    }
}

BinaryTree::~BinaryTree() = default;



TokenLRpointer *BinaryTree::searchToken(Token &node, bool &found) {
    found = false; //επιστρέφω by reference αν βρέθηκε το στοιχείο
    bool giveUp = false; //γίνεται true όταν φτάνω σε null και δεν έχει βρεθεί το στοιχείο
    TokenLRpointer *currentNode = headPointer;
    while (!found && !giveUp) {
        if (node.getValue() > currentNode->getValue()) {
            if (currentNode->getRightToken() == nullptr) {
                giveUp = true; //Δε βρέθηκε το node γιατί έφτασα σε null
                currentNode = nullptr;
            } else {
                currentNode = currentNode->getRightToken(); //προχωράω στο δεξί παιδί
            }
        }
        else if (node.getValue() < currentNode->getValue()) {
            if (currentNode->getLeftToken() == nullptr) {
                giveUp = true; //Δε βρέθηκε το node γιατί έφτασα σε null
                currentNode = nullptr;
            }
            else {
                currentNode = currentNode->getLeftToken(); //προχωράω στο αριστερό παιδί
            }
        }
        else { //Ισότητα, άρα το node βρέθηκε
            found = true;
        }
    }
    return currentNode; //αν δε βρεθεί επιστρέφει null
}

