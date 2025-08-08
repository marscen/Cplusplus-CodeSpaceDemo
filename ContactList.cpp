#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#define MAX 1000
using namespace std;

struct Person {
    string m_Name;
    int m_Sex; //性别：1、男，2、女
    int m_Age; //年龄
    string m_Number; //电话
    string m_Address; //地址
};

struct ContactList {
    Person m_PersonArray[MAX]; //联系人数组
    int m_Size; //当前联系人个数
};

void showMenu(){
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
    //cin.clear();
    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

//添加联系人
void addPerson(ContactList *contactList) {
    if (contactList->m_Size >= MAX) {
        cout << "通讯录已满，无法添加新联系人！" << endl;
        return;
    }
    else
    {
        string input;
        cout << "请输入姓名：" << endl;
        getline(cin >> ws, contactList->m_PersonArray[contactList->m_Size].m_Name);

        cout << "请输入性别（男:1;女:2）：" << endl;
        int sex = 0;
        while(true) {
            getline(cin, input);
            stringstream ss(input);
            if (ss >> sex && (sex == 1 || sex == 2)){
                contactList->m_PersonArray[contactList->m_Size].m_Sex = sex;
                break;
            }
            else
            {
                cout << "输入错误，请重新输入性别（男:1;女:2）：" << endl;
            }
        }

        cout << "请输入年龄：" << endl;
        int age = 0;
        while (true) {
            getline(cin, input);
            stringstream ss(input);
            if (ss >> age && age > 0 && age < 150) {
                contactList->m_PersonArray[contactList->m_Size].m_Age = age;
                break;
            } else {
                cout << "输入错误，请重新输入年龄（1-149）：" << endl;
            }
        }

        cout << "请输入电话号码：" << endl;
        getline(cin, contactList->m_PersonArray[contactList->m_Size].m_Number);
        cout << "请输入地址：" << endl;
        getline(cin, contactList->m_PersonArray[contactList->m_Size].m_Address);

        contactList->m_Size++; //联系人个数加1
        cout << "添加联系人成功！" << endl;
    }
    waitForEnter();
}

void showPerson(ContactList *contactList){
    if (contactList->m_Size == 0) {
        cout << "通讯录为空！" << endl;
    }
    else{
        for (int i = 0; i < contactList->m_Size; i++) {
            cout << "姓名：" << contactList->m_PersonArray[i].m_Name << endl;
            cout << "性别：" << (contactList->m_PersonArray[i].m_Sex == 1 ? "男" : "女") << endl;
            cout << "年龄：" << contactList->m_PersonArray[i].m_Age << endl;
            cout << "电话：" << contactList->m_PersonArray[i].m_Number << endl;
            cout << "地址：" << contactList->m_PersonArray[i].m_Address << endl;
        }
    }
    waitForEnter();
}

int findIndexByName(string name, ContactList *contactList) {
    for (int i = 0; i < contactList->m_Size; i++) {
        if (contactList->m_PersonArray[i].m_Name == name) {
            return i; // 返回找到的索引
        }
    }
    return -1; // 未找到
}

void deletePerson(ContactList *contactList) {
    if (contactList->m_Size == 0) {
        cout << "通讯录为空，无法删除联系人！" << endl;
        waitForEnter();
        return;
    }
    else {
        string name;
        cout << "请输入要删除的联系人姓名：" << endl;
        getline(cin >> ws, name);
        int index = findIndexByName(name, contactList); // 查找联系人
        // 如果未找到联系人，提示用户
        if (index == -1) {
            cout << "查无此人！" << endl;
            return;
        }
        else {
            // 找到联系人后，删除该联系人
            cout << "确认删除联系人：" << contactList->m_PersonArray[index].m_Name << "？(y/n)" << endl;
            string confirm;
            getline(cin, confirm);
            if (confirm != "y" && confirm != "Y") {
                cout << "取消删除操作！" << endl;
                return;
            }
            // 删除联系人，移动后面的联系人到前面
            cout << "正在删除联系人..." << endl;
            cout << "删除联系人：" << contactList->m_PersonArray[index].m_Name << endl;
            for (int i = index; i < contactList->m_Size - 1; i++) {
                contactList->m_PersonArray[i] = contactList->m_PersonArray[i + 1];
            }
            contactList->m_Size--; // 更新联系人个数
            cout << "删除成功！" << endl;
        }
    }
    waitForEnter();
}

void findPerson(ContactList *contactList) {
    if (contactList->m_Size == 0) {
        cout << "通讯录为空，无法查找联系人！" << endl;
        return;
    }
    else {
        string name;
        cout << "请输入要查找的联系人姓名：" << endl;
        getline(cin >> ws, name);
        int index = findIndexByName(name, contactList); // 查找联系人
        if (index == -1) {
            cout << "查无此人！" << endl;
            return;
        }
        else {
            // 找到联系人后，显示其信息
            cout << "姓名：" << contactList->m_PersonArray[index].m_Name << endl;
            cout << "性别：" << (contactList->m_PersonArray[index].m_Sex == 1 ? "男" : "女") << endl;
            cout << "年龄：" << contactList->m_PersonArray[index].m_Age << endl;
            cout << "电话：" << contactList->m_PersonArray[index].m_Number << endl;
            cout << "地址：" << contactList->m_PersonArray[index].m_Address << endl;
        }
    }
    waitForEnter();
}

void modifyPerson(ContactList *contactList) {
    if (contactList->m_Size == 0) {
        cout << "通讯录为空，无法修改联系人！" << endl;
        return;
    }
    else {
        string name;
        cout << "请输入要修改的联系人姓名：" << endl;
        getline(cin >> ws, name);
        int index = findIndexByName(name, contactList); // 查找联系人
        if (index == -1) {
            cout << "查无此人！" << endl;
            return;
        }
        else {
            // 找到联系人后，修改其信息
            cout << "正在修改联系人信息..." << endl;
            cout << "请输入新的姓名（留空则不修改）：" << endl;
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                contactList->m_PersonArray[index].m_Name = newName;
            }
            cout << "请输入新的性别（男:1;女:2，留空则不修改）：" << endl;
            string sexInput;
            getline(cin, sexInput);
            if (!sexInput.empty()) {
                int newSex = 0;
                stringstream ss(sexInput);
                if (ss >> newSex && (newSex == 1 || newSex == 2)) {
                    contactList->m_PersonArray[index].m_Sex = newSex;
                }
                else {
                    cout << "输入错误，性别未修改！" << endl;
                }
            }
            cout << "请输入新的年龄（留空则不修改）：" << endl;
            string ageInput;
            getline(cin, ageInput);
            if (!ageInput.empty()) {
                int newAge = 0;
                stringstream ss(ageInput);
                if (ss >> newAge && newAge > 0 && newAge < 150) {
                    contactList->m_PersonArray[index].m_Age = newAge;
                } else {
                    cout << "输入错误，年龄未修改！" << endl;
                }
            }
            cout << "请输入新的电话（留空则不修改）：" << endl;
            string numberInput;
            getline(cin, numberInput);
            if (!numberInput.empty()) {
                contactList->m_PersonArray[index].m_Number = numberInput;
            }
            cout << "请输入新的地址（留空则不修改）：" << endl;
            string addressInput;
            getline(cin, addressInput);
            if (!addressInput.empty()) {
                contactList->m_PersonArray[index].m_Address = addressInput;
            }
            cout << "修改成功！" << endl;
        }
    }
    waitForEnter();
}

void clearPerson(ContactList *contactList) {
    contactList->m_Size = 0; // 清空联系人个数
    cout << "通讯录已清空！" << endl;
    waitForEnter();
}

int main() {
    ContactList contactList;
    contactList.m_Size = 0; // 初始化联系人个数为0
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
                addPerson(&contactList); // 添加联系人
                break;
            case 2:
                showPerson(&contactList); // 显示联系人
                break;
            case 3:
                deletePerson(&contactList); // 删除联系人
                break;
            case 4:
                findPerson(&contactList); // 查找联系人
                break;
            case 5:
                modifyPerson(&contactList); // 修改联系人
                break;
            case 6:
                clearPerson(&contactList); // 清空联系人
                break;
            case 0:
                cout << "正在退出通讯录，欢迎下次使用..." << endl;
                return 0; // 退出程序
            default:
                cout << "无效的选择，请重新输入！" << endl;
        }
    } while (true);

    return 0;
}
