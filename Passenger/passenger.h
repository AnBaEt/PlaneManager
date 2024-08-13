#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Passenger {
    string CMND;
    string Ho;
    string Ten;
    string Phai;
    Passenger* left;
    Passenger* right;
};

struct PassengerBST {
    Passenger* root;

    PassengerBST();
    ~PassengerBST();

    void insertPassenger(const string& CMND, const string& Ho, const string& Ten, const string& Phai);
    Passenger* searchPassenger(const string& CMND) const;
    void displayPassenger(const Passenger* passenger) const;
    void loadFromFile(const string& filename);

private:
    Passenger* createPassenger(const string& CMND, const string& Ho, const string& Ten, const string& Phai);
    Passenger* insertPassenger(Passenger* root, const string& CMND, const string& Ho, const string& Ten, const string& Phai);
    Passenger* searchPassenger(Passenger* root, const string& CMND) const;
    void destroyTree(Passenger* root);
};

PassengerBST::PassengerBST() : root(nullptr) {}

PassengerBST::~PassengerBST() {
    destroyTree(root);
}

void PassengerBST::destroyTree(Passenger* root) {
    if (root != nullptr) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

Passenger* PassengerBST::createPassenger(const string& CMND, const string& Ho, const string& Ten, const string& Phai) {
    Passenger* newPassenger = new Passenger();
    newPassenger->CMND = CMND;
    newPassenger->Ho = Ho;
    newPassenger->Ten = Ten;
    newPassenger->Phai = Phai;
    newPassenger->left = nullptr;
    newPassenger->right = nullptr;
    return newPassenger;
}

Passenger* PassengerBST::insertPassenger(Passenger* root, const string& CMND, const string& Ho, const string& Ten, const string& Phai) {
    if (root == nullptr) {
        return createPassenger(CMND, Ho, Ten, Phai);
    }
    if (CMND < root->CMND) {
        root->left = insertPassenger(root->left, CMND, Ho, Ten, Phai);
    } else if (CMND > root->CMND) {
        root->right = insertPassenger(root->right, CMND, Ho, Ten, Phai);
    }
    return root;
}

Passenger* PassengerBST::searchPassenger(Passenger* root, const string& CMND) const {
    if (root == nullptr || root->CMND == CMND) {
        return root;
    }
    if (CMND < root->CMND) {
        return searchPassenger(root->left, CMND);
    }
    return searchPassenger(root->right, CMND);
}

Passenger* PassengerBST::searchPassenger(const string& CMND) const {
    return searchPassenger(root, CMND);
}

void PassengerBST::displayPassenger(const Passenger* passenger) const {
    if (passenger != nullptr) {
        cout << "Số CMND: " << passenger->CMND << endl;
        cout << "Họ: " << passenger->Ho << endl;
        cout << "Tên: " << passenger->Ten << endl;
        cout << "Phái: " << passenger->Phai << endl;
    } else {
        cout << "Hành khách không tồn tại." << endl;
    }
}
void PassengerBST::insertPassenger(const string& CMND, const string& Ho, const string& Ten, const string& Phai) {
    root = insertPassenger(root, CMND, Ho, Ten, Phai);

    ofstream file("passengers.txt", ios::app);
    if (file.is_open()) {
        file << CMND << "," << Ho << "," << Ten << "," << Phai << endl;
        file.close();
    } else {
        cerr << "Không thể mở file để ghi." << endl;
    }
}

void PassengerBST::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Không thể mở file để đọc." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string CMND, Ho, Ten, Phai;
        if (getline(iss, CMND, ',') &&
            getline(iss, Ho, ',') &&
            getline(iss, Ten, ',') &&
            getline(iss, Phai)) {
            if (searchPassenger(CMND) == nullptr) {
                insertPassenger(CMND, Ho, Ten, Phai);
            }
        }
    }
    file.close();
}


#endif
 