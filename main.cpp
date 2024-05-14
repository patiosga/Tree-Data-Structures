#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>

#include "BinaryTree.h"
#include "AVL.h"
using namespace std;


string purifyStr(string temp) {
    int i;
    for (i=0;temp[i]!='\0';i++) {
        if (isalpha(temp[i]))
            temp[i] = tolower(temp[i]); //κάνω όλα τα γράμματα πεζά
        else if (!isdigit(temp[i])) {
            temp[i] = ' '; //κάνω όλους τους χαρακτήρες κενά ώστε να διαγραφούν παρακάτω
        }
    }
    temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end()); //αφαίρεση όλων των κενών χαρακτήρων
    return temp;
}

bool searchStr(Token **elements,string &str,int &pos) { //γυρνάω θέση που βρέθηκε το token by reference. Αν δε βρεθεί επιστρέφει -1
    int i;
    pos = -1;
    for (i = 0; elements[i] != nullptr; i++) { //Σταματάω μόλις βρω τον πρώτο δείκτη σε null
        if ((elements[i]->getValue()) == str) {
            pos = i;
            return true;
        }
    }
    return false;
}


int main() {
    string str, token; //token --> συμβολοσειρά ζεύγους
    ifstream inputFile("test_file.txt");
    ofstream myFile;
    int size=500000; //μέγεθος πίνακα από tokens. Στη συνέχεια μεγαλώνει ανάλογα με τις ανάγκες του αρχείου
    int counter=0, counterCircle=0, i; //counterCircle --> κυκλικός μετρητής για αλλαγή σειράς. Λόγος ύπαρξης: αισθητικός
    myFile.open("purified.txt");
    if (!inputFile.is_open()) {
        //cout<<"File Not Found";
    }
    else {
        //cout << "Found...Purifying file from all evil...\n";
        while (!inputFile.eof()) {
            inputFile >> str;
            counterCircle++;
            str = purifyStr(str);
            if (counterCircle != 15) // μόλις γράψω 15 λέξεις αλλάζω γραμμή
                myFile << str << " ";
            else {
                myFile << str << "\n";
                counterCircle = 0;
            }
        }
    }
    myFile.close();
    inputFile.close();

    ifstream file("purified.txt");
    Token **elements = new Token*[size];
    elements = new Token*[size];

    for (i=0; i<size; i++)
        elements[i] = nullptr; //αρχικοποίηση πίνακα δεικτών σε NULL
    i=0; //αρχικοποίηση μετρητή i για τη while
    bool flag=true;
    file>>str;
    while(!file.eof()) {

        if (flag) { //Η πρώτη λέξη του αρχείου δεν προστίθεται σε προηγούμενο token
            flag = false;
            token.assign(str);
            continue;
        }
        token += " ";
        token += str; //ολοκληρώνω ζεύγος λέξης
        int pos; // θέση που πρόκειται να βρεθεί (αν βρεθεί) το ζεύγος token
        bool existingStr = searchStr(elements,token,pos);
        if (existingStr) {
            elements[pos]->setApps(elements[pos]->getApps()+1);
            token.assign(str); //αφού προσθέσω το προηγούμενο ζεύγος κάνω καινούργιο με πρώτη λέξη τη δεύτερη του προηγούμενου ζεύγους
            file>>str;
        }
        else {
            Token *newstring = new Token(token);
            if (i==size-1) { // resize matrix elements + 100000 tokens
                elements = (Token **)(realloc(elements, (size+100000) * sizeof(Token *)));
                for (int j=size;j<size+100000;j++)
                    elements[j]= nullptr; //νέες θέσεις elements --> αρχικοποίηση σε null
                size+=100000;
            }
            elements[i] = newstring;
            token.assign(str); //αφού προσθέσω το προηγούμενο ζεύγος κάνω καινούργιο με πρώτη λέξη τη δεύτερη του προηγούμενου ζεύγους
            file>>str;
            i++; //το i που θα προκύψει είναι η επόμενη κενή θέση του πίνακα elements άρα και το μέγεθός του
            //cout<<i<<"\n";
        } //καταλήγω να παίρνω ένα token με δύο φορές την πρώτη λέξη του αρχείου, αλλά σε μεγάλα κείμενα αυτό είναι αμελητέο

    }
    file.close();
    //cout<<"All evil is gone\n";


    counter= i; //Χρειάζεται για να το περνάω ως την επόμενη κενή θέση στους κατασκευαστές των ταξινομημένων και μη πινάκων
    bool test;


    //ΔΙΑΔΙΚΑΣΙΑ ΕΜΦΑΝΙΣΗΣ ΑΠΟΤΕΛΕΣΜΑΤΩΝ
    ofstream results;
    results.open("results.txt");
    clock_t begin,end;
    int randomPos,tempNum;
    double time;
    Token *tempSearch;


    //ΔΥΑΔΙΚΟ ΔΕΝΤΡΟ
    begin = clock();
    BinaryTree tree1(elements);
    end = clock();
    time = (end - begin)*1.0/CLOCKS_PER_SEC;
    results<< "Build Time of Binary Tree: "<<time<<" sec"<<"\n";
    //ΑΝΑΖΗΤΗΣΗ ΣΤΟ ΔΥΑΔΙΚΟ ΔΕΝΤΡΟ
    results<<"\n"<<"Searching in Binary Tree:\n";
    begin = clock();
    for (i=0;i<1000;i++) {
        randomPos = rand() % counter; //counter --> αριθμός στοιχείων στον πίνακα elements και άρα έχω άνω όριο τυχαίου αριθμού το counter-1
        tree1.searchToken(*elements[randomPos],test);
        //cout<<test<<"\n";
        results<<"Pair: "<<elements[randomPos]->getValue()<<", Appearances: "<<elements[randomPos]->getApps()<<"\n";
    }
    end = clock();
    time = (end - begin)*1.0/CLOCKS_PER_SEC;
    results<<"Search Time: "<<time<<" sec"<<"\n\n\n";
    //cout<<"done\n";


    //ΙΣΟΡΡΟΠΗΜΕΝΟ ΔΥΑΔΙΚΟ ΔΕΝΤΡΟ
    begin = clock();
    AVL tree2(elements);
    end = clock();
    time = (end - begin)*1.0/CLOCKS_PER_SEC;
    results<< "Build Time of AVL: "<<time<<" sec";
    //ΑΝΑΖΗΤΗΣΗ ΣΤΟ AVL
    results<<"\n"<<"Searching in AVL:\n";
    begin = clock();
    for (i=0;i<1000;i++) {
        randomPos = rand() % counter; //counter --> αριθμός στοιχείων στον πίνακα elements και άρα έχω άνω όριο τυχαίου αριθμού το counter-1
        tree2.searchToken(*elements[randomPos],test);
        //cout<<test<<"\n";
        results<<"Pair: "<<elements[randomPos]->getValue()<<", Appearances: "<<elements[randomPos]->getApps()<<"\n";
    }
    end = clock();
    time = (end - begin)*1.0/CLOCKS_PER_SEC;
    results<<"Search Time: "<<time<<"sec"<<"\n";
    //cout<<"done\n";





    results.close();
    return 0;
}

