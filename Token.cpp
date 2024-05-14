#include "Token.h"


Token::Token(const string& value) {
    this->value.assign((value));
    apps = 1;
}

int Token::getApps() {
    return apps;
}

string Token::getValue() {
    return value;
}

void Token::setApps(int num) {
    apps = num;
}

