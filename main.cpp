#include "ContactList.h"
#include <iostream>
#include <sstream>
using namespace std;

void showMenu() {
    cout << "*************************" << endl;
    cout << "***** 1、添加联系人 ******" << endl;
    cout << "***** 2、显示联系人 ******" << endl;
    cout << "***** 3、删除联系人 ******" << endl;
    cout << "***** 4、查找联系人 ******" << endl;
    cout << "***** 5、修改联系人 ******" << endl;
    cout << "***** 6、清空联系人 ******" << endl;
    cout << "***** 0、退出通讯录 ******" << endl;
    cout << "*************************" << endl;
}

void waitForEnter() {
    cout << "按回车键继续..." << endl;
    cin.get();
}

int main() {
    ContactList contactList;
    contactList.loadFromFile("contacts.txt");
    string input;
    int choice = 0;
    do {
        showMenu();
        cout << "请选择操作：";
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> choice)) {
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }
        switch (choice) {
            case 1:
                contactList.addPerson();
                waitForEnter();
                break;
            case 2:
                contactList.showAll();
                waitForEnter();
                break;
            case 3:
                contactList.deletePerson();
                waitForEnter();
                break;
            case 4:
                contactList.findPerson();
                waitForEnter();
                break;
            case 5:
                contactList.modifyPerson();
                waitForEnter();
                break;
            case 6:
                contactList.clear();
                waitForEnter();
                break;
            case 0:
                cout << "正在退出通讯录，欢迎下次使用..." << endl;
                contactList.saveToFile("contacts.txt");
                return 0;
            default:
                cout << "无效的选择，请重新输入！" << endl;
        }
    } while (true);
    return 0;
}