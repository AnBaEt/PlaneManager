#include <iostream>
#include <string>
#include "passenger.h"

using namespace std;

void displayMenu() {
    cout << "Chương trình Quản lý Hành khách" << endl;
    cout << "1. Thêm hành khách" << endl;
    cout << "2. Tìm hành khách" << endl;
    cout << "3. Hiển thị thông tin hành khách" << endl;
    cout << "4. Thoát" << endl;
    cout << "Chọn một tùy chọn: ";
}

int main() {
    PassengerBST bst;
    bst.loadFromFile("passengers.txt");
    int choice;
    string CMND, Ho, Ten, Phai;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Nhập Số CMND: ";
                getline(cin, CMND);
                cout << "Nhập Họ: ";
                getline(cin, Ho);
                cout << "Nhập Tên: ";
                getline(cin, Ten);
                cout << "Nhập Phái: ";
                getline(cin, Phai);
                bst.insertPassenger(CMND, Ho, Ten, Phai);
                cout << "Hành khách đã được thêm thành công và ghi vào file." << endl;
                break;

            case 2:
                cout << "Nhập Số CMND để tìm: ";
                getline(cin, CMND);
                {
                    Passenger* passenger = bst.searchPassenger(CMND);
                    if (passenger != nullptr) {
                        bst.displayPassenger(passenger);
                    } else {
                        cout << "Không tìm thấy hành khách với Số CMND: " << CMND << endl;
                    }
                }
                break;

            case 3:
                cout << "Nhập Số CMND để hiển thị thông tin: ";
                getline(cin, CMND);
                {
                    Passenger* passenger = bst.searchPassenger(CMND);
                    bst.displayPassenger(passenger);
                }
                break;

            case 4:
                cout << "Đang thoát chương trình..." << endl;
                break;

            default:
                cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;
                break;
        }
        cout << endl;

    } while (choice != 4);
    return 0;
}
