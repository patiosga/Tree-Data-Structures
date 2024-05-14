#ifndef ___TOKEN_H
#define ___TOKEN_H
#include <string>
using namespace std; //για τη δήλωση μεταβλητών τύπου string

class Token {
protected:
    int apps;  //Αριθμός εμφανίσεων του token
    string value;

public:
    Token(const string& value);
    int getApps();
    string getValue();
    void setApps(int num);
};


#endif //___TOKEN_H
