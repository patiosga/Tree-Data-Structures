#include "AVL.h"
#include <cmath>
#include <iostream>

AVL::AVL(Token **elements) { //Η συνθήκη ισορροπίας μπορεί να παραβιαστεί μόνο στο κλαδί προς τη ρίζα που έχει μπει ο κόμβος!!
    headPointer = new TokenLRpointer(elements[0]->getValue());
    headPointer->setParent(nullptr); //μάλλον δε χρειάζεται το αφήνω για την ώρα
    int i;
    for (i=1;elements[i]!= nullptr;i++) {
        addTokenAVL(*elements[i]);
    }
}


bool AVL::addTokenAVL(Token &node) {
    TokenLRpointer *temp;
    temp = new TokenLRpointer(node.getValue());
    bool added = false;
    //Αρχίζω από ρίζα και ψάχνω νέα θέση μέχρι να καταλήξω σε null - καμία διαφοροποίηση απο BinaryTree αρχικά με εξαίρεση ότι κρατάω προγόνους
    TokenLRpointer *currentNode = headPointer;
    while (!added) { //while μέχρι να φτάσω στον κατάλληλο δείκτη null και να προσθέσω το νέο στοιχείο
        if (temp->getValue()>=currentNode->getValue()) {
            if (currentNode->getRightToken()== nullptr) {
                currentNode->setRightToken(temp);
                temp->setParent(currentNode);
                added = true;
            }
            else
                currentNode = currentNode->getRightToken();
        }
        else {
            if (currentNode->getLeftToken()== nullptr) {
                currentNode->setLeftToken(temp);
                temp->setParent(currentNode);
                added = true;
            }
            else
                currentNode = currentNode->getLeftToken();
        }
    }

    currentNode = temp; //αρχίζω από φύλλο και θα κινηθώ προς τα πάνω
    //Ξεκινάω διαδικασία ισορρόπησης
    restoreBalance(currentNode);
    TokenLRpointer *leftChild,*rightChild;
    while (currentNode!= nullptr) {
        leftChild = currentNode->getLeftToken();
        rightChild = currentNode->getRightToken();
        if (leftChild== nullptr && rightChild== nullptr) { // είμαι σε φύλλο άρα δεν κάνω κάτι
            currentNode = currentNode->getParent();
        }
        else {
            if (currentNode->getBalance()>1 || currentNode->getBalance()<(-1)) {//κόμβος που έχει πρόβλημα / +2 --> δεξιά, -2 --> αριστερά γιατί κάνω έλεγχο maxright-maxleft
                if (currentNode->getBalance()==2) { //δεξιά
                    if (rightChild->getBalance()==1) { //σίγουρα το πρόβλημα είναι δεξιά δεξιά - Περίπτωση ΔΔ / το δεξί παιδί έχει μεγαλύτερο δεξί υποδέντρο αφού balance = maxright - maxleft
                        leftTurn(currentNode);
                        currentNode = currentNode->getParent(); // προχωράω στο επόμενο
                    }
                    else  { //δεξιά αριστερά - Περίπτωση ΔΑ - το balance του rightChild θα είναι σίγουρα -1
                        RightLeft(currentNode);
                        currentNode = currentNode->getParent(); // προχωράω στο επόμενο
                    }
                }
                else { //balance = -2 --> αριστερά
                    if (leftChild->getBalance()== -1) { //ΑΑ - σίγουρα το πρόβλημα είναι αριστερά αριστερά γιατί το αριστερό υποδέντρο του leftChild είναι μεγαλύτερο του δεξιού
                        rightTurn(currentNode);
                        currentNode = currentNode->getParent(); // προχωράω στο επόμενο
                    }
                    else { //ΑΔ - το balance του leftChild θα είναι σίγουρα 1
                        LeftRight(currentNode);
                        currentNode = currentNode->getParent(); // προχωράω στο επόμενο
                    }
                }
            }
            else
                currentNode = currentNode->getParent();
        }
    }
    return true;
}

void AVL::rightTurn(TokenLRpointer *node) { //x,y όπως είναι στο Ισορροπημένα Δέντρα Αναζήτησης (κεφάλαιο) - σελ. 156
    bool head;
    if (node==headPointer) //αν έχω τον headPointer μετά τις αλλαγές πρέπει να αλλάξω που θα δείχνει γιατί αλλώς μένει μόνιμα ορισμένο από τον κατασκευαστή
        head = true;
    else
        head = false;

    TokenLRpointer *leftChild,*grandFather; //leftChild: x
    leftChild = node->getLeftToken(); //x
    grandFather = node->getParent();
    //Έλεγχος αν είμαι στο πρώτο μέρος διπλής περιστροφής ΔΑ και έχω μόνο έναν κόμβο στο αριστερό υποδέντρου του leftChild
    if (leftChild->getDepth() == 1) { // βρίσκομαι σε φύλλο με depth 1
        node->setParent(leftChild); //το node δείχνει στο μοναδικό παιδί του ως πρόγονο
        leftChild->setParent(grandFather); //το μοναδικό παιδί του δείχνει στον πρόγονο του node
        leftChild->setRightToken(node); //το μοναδικό παιδί του node θα έχει ως αριστερό παιδί το node
        node->setLeftToken(nullptr); //το node στα αριστερά του τώρα δε θα έχει τίποτα
    }
    else {
        //Επανατοποθέτηση παιδιών
        if (leftChild->getRightToken()!=nullptr) //μετακίνηση δεξιού υποδέντρου του αριστερού παιδιού του node να έχει ως γονέα το node
            leftChild->getRightToken()->setParent(node);
        node->setLeftToken(leftChild->getRightToken()); //Αριστερό παιδί του y γίνεται το δεξί παιδί του x
        leftChild->setRightToken(node); //Δεξί παιδί του x γίνεται το y
        //Επανατοποθέτηση γονέων
        node->setParent(leftChild); //Γονέας του y γίνεται το x
        leftChild->setParent(grandFather); //Γονέας του x γίνεται ο πρόγονος του y
        if (head)
            headPointer = leftChild; //Αν η περιστροφή ήταν της ρίζας πρέπει να αλλάξει η ρίζα
    }
    if (grandFather!=nullptr) { //Αν δεν είμαι στη ρίζα πρέπει ο πρόγονος του node να δείχνει στο νέο του παιδί που θα είναι το αριστερό παιδί του node
        //είναι πιο περίπλοκο από ότι νόμιζα γιατί δε γνωρίζω χωρίς έλεγχο αν το node είναι δεξί ή αριστερό παιδί του grandFather
        if (grandFather->getLeftToken()== nullptr) //node είναι σίγουρα δεξιά του grandFather
            grandFather->setRightToken(leftChild);
        else if (grandFather->getRightToken()== nullptr) //node είναι σίγουρα αριστερά του grandFather
            grandFather->setLeftToken(leftChild);
            //τώρα κανένα από τα παιδιά του grandFather δεν είναι null
        else if (grandFather->getRightToken()==node) // το node είναι δεξιά του
            grandFather->setRightToken(leftChild);
        else // το node είναι αριστερά (μόνη περίπτωση που μένει
            grandFather->setLeftToken(leftChild);
    }
    restoreBalance(node); // το node έχει πάει προς τα κάτω άρα πηγαίνοντας προς τα πάνω με restoreBalance χτυπάω όσα node χρειάζονται αλλαγή στο depth
}

void AVL::leftTurn(TokenLRpointer *node) { //x,y όπως είναι στο Ισορροπημένα Δέντρα Αναζήτησης (κεφάλαιο) - σελ. 156
    bool head;
    if (node==headPointer) //αν έχω τον headPointer μετά τις αλλαγές πρέπει να αλλάξω που θα δείχνει γιατί αλλιώς μένει μόνιμα ορισμένο από τον κατασκευαστή
        head = true;
    else
        head = false;

    TokenLRpointer *rightChild,*grandFather; //rightChild: y
    rightChild = node->getRightToken(); //y
    grandFather = node->getParent();
    //Έλεγχος αν είμαι στο πρώτο μέρος διπλής περιστροφής ΑΔ και έχω μόνο έναν κόμβο στο αριστερό υποδέντρου του rightChild
    if (rightChild->getDepth() == 1) { // βρίσκομαι σε φύλλο με depth 1
        node->setParent(rightChild); //το node δείχνει στο μοναδικό παιδί του ως πρόγονο
        rightChild->setParent(grandFather); //το μοναδικό παιδί του δείχνει στον πρόγονο του node
        rightChild->setLeftToken(node); //το μοναδικό παιδί του node θα έχει ως δεξί παιδί το node
        node->setRightToken(nullptr); //το node στα δεξιά του τώρα δε θα έχει τίποτα
    }
    else {
        if (rightChild->getLeftToken()!=nullptr) //μετακίνηση αριστερού υποδέντρου του δεξιού παιδιού του node να έχει γονέα το node
            rightChild->getLeftToken()->setParent(node);
        node->setRightToken(rightChild->getLeftToken()); //Δεξί παιδί του x γίνεται το αριστερό παιδί του y
        rightChild->setLeftToken(node); //το y κάνει αριστερό παιδί το x
        //Επανατοποθέτηση γονέων
        node->setParent(rightChild); //Γονέας του x γίνεται το y
        rightChild->setParent(grandFather); //Γονέας του y γίνεται ο πρόγονος του x
        if (head)
            headPointer = rightChild; //Αν η περιστροφή ήταν της ρίζας πρέπει να αλλάξει η ρίζα
    }
    if (grandFather!=nullptr) { //Αν δεν είμαι στη ρίζα πρέπει ο πρόγονος του node να δείχνει στο νέο του παιδί που θα είναι το αριστερό παιδί του node
        //είναι πιο περίπλοκο από ότι νόμιζα γιατί δε γνωρίζω χωρίς έλεγχο αν το node είναι δεξί ή αριστερό παιδί του grandFather
        if (grandFather->getLeftToken()== nullptr) //node είναι σίγουρα δεξιά του grandFather
            grandFather->setRightToken(rightChild);
        else if (grandFather->getRightToken()== nullptr) //node είναι σίγουρα αριστερά του grandFather
            grandFather->setLeftToken(rightChild);
            //τώρα κανένα από τα παιδιά του grandFather δεν είναι null
        else if (grandFather->getRightToken()==node) // το node είναι δεξιά του
            grandFather->setRightToken(rightChild);
        else // το node είναι αριστερά (μόνη περίπτωση που μένει
            grandFather->setLeftToken(rightChild);
    }
    restoreBalance(node); // το node έχει πάει προς τα κάτω άρα πηγαίνοντας προς τα πάνω με restoreBalance χτυπάω όσα node χρειάζονται αλλαγή στο depth
}


void AVL::RightLeft(TokenLRpointer *node) {
    rightTurn(node->getRightToken());
    leftTurn(node);
}

void AVL::LeftRight(TokenLRpointer *node) {
    leftTurn(node->getLeftToken()); //αριστερή περιστροφή του δεξιού παιδιού
    rightTurn(node); //δεξιά περιστροφή του node
}

int AVL::findMaxDepth(TokenLRpointer *node) {
    int maxLeft,maxRight,max;
    TokenLRpointer *lefttoken,*righttoken;
    if (node == nullptr) //άδειο δέντρο ή γονέας ρίζας
        return 0;
    lefttoken = node->getLeftToken();
    righttoken = node->getRightToken();
    if (lefttoken== nullptr && righttoken== nullptr)
        return 1; //δεν υπάρχουν άλλα κλαδιά από κάτω
    else {
        if (righttoken != nullptr)
            maxRight = findMaxDepth(righttoken);
        else
            maxRight = 0;
        if (lefttoken != nullptr)
            maxLeft = findMaxDepth(lefttoken);
        else
            maxLeft = 0;
        max = fmax(maxLeft,maxRight) + 1; //δεν κάνω casting γιατί ούτως ή άλλως αποθηκεύεται σε ακέραιο
        return max;
    }
}

void AVL::restoreBalance(TokenLRpointer *node) { //node ξεκινάει το ταξίδι προς τα πάνω από το φύλλο που προστέθηκε
    if (node == nullptr)
        return; //τερματίζει η αναδρομή μόλις φτάσω στη ρίζα για την οποία ισχύει parent --> null
    int maxleft,maxright,max;
    max = findMaxDepth(node);
    //καλώ depth παιδιών που έχουν βρεθεί ήδη τα σωστά αφού πάω προς τα πάνω στο δέντρο
    if (node->getLeftToken()!= nullptr)
        maxleft = node->getLeftToken()->getDepth();
    else
        maxleft = 0;
    if (node->getRightToken()!= nullptr)
        maxright = node->getRightToken()->getDepth();
    else
        maxright = 0;
    node->setBalance(maxright-maxleft); //Δείκτης Ισορροπίας --> +2 όταν προκύπτει θέμα δεξιά, -2 όταν προκύπτει θέμα αριστερά
    node->setDepth(max);


    restoreBalance(node->getParent());
}
