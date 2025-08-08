#include "ContactList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

ContactList::ContactList() {}

void ContactList::addPerson() {
    if (m_PersonArray.size() >= MAX) {
        cout << "通讯录已满，无法添加新联系人！" << endl;
        return;
    }
    string name, number, address, input;
    int sex = 0, age = 0;

    cout << "请输入姓名：" << endl;
    getline(cin >> ws, name);

    cout << "请输入性别（男:1;女:2）：" << endl;
    while (true) {
        getline(cin, input);
        stringstream ss(input);
        if (ss >> sex && (sex == 1 || sex == 2)) break;
        cout << "输入错误，请重新输入性别（男:1;女:2）：" << endl;
    }

    cout << "请输入年龄：" << endl;
    while (true) {
        getline(cin, input);
        stringstream ss(input);
        if (ss >> age && age > 0 && age < 150) break;
        cout << "输入错误，请重新输入年龄（1-149）：" << endl;
    }

    cout << "请输入电话号码：" << endl;
    getline(cin, number);
    cout << "请输入地址：" << endl;
    getline(cin, address);

    m_PersonArray.emplace_back(name, sex, age, number, address);
    cout << "添加联系人成功！" << endl;
}

void ContactList::showAll() const {
    if (m_PersonArray.empty()) {
        cout << "通讯录为空！" << endl;
    } else {
        for (const auto& p : m_PersonArray) {
            cout << "姓名：" << p.getName() << endl;
            cout << "性别：" << (p.getSex() == 1 ? "男" : "女") << endl;
            cout << "年龄：" << p.getAge() << endl;
            cout << "电话：" << p.getNumber() << endl;
            cout << "地址：" << p.getAddress() << endl;
            cout << "-------------------------" << endl;
        }
    }
}

int ContactList::findIndexByName(const std::string& name) const {
    for (size_t i = 0; i < m_PersonArray.size(); ++i) {
        if (m_PersonArray[i].getName() == name) return i;
    }
    return -1;
}

void ContactList::deletePerson() {
    if (m_PersonArray.empty()) {
        cout << "通讯录为空，无法删除联系人！" << endl;
        return;
    }
    string name;
    cout << "请输入要删除的联系人姓名：" << endl;
    getline(cin >> ws, name);
    int idx = findIndexByName(name);
    if (idx == -1) {
        cout << "查无此人！" << endl;
    } else {
        cout << "确认删除联系人：" << m_PersonArray[idx].getName() << "？(y/n)" << endl;
        string confirm;
        getline(cin, confirm);
        if (confirm == "y" || confirm == "Y") {
            m_PersonArray.erase(m_PersonArray.begin() + idx);
            cout << "删除成功！" << endl;
        } else {
            cout << "取消删除操作！" << endl;
        }
    }
}

void ContactList::findPerson() const {
    if (m_PersonArray.empty()) {
        cout << "通讯录为空，无法查找联系人！" << endl;
        return;
    }
    string name;
    cout << "请输入要查找的联系人姓名：" << endl;
    getline(cin >> ws, name);
    int idx = findIndexByName(name);
    if (idx == -1) {
        cout << "查无此人！" << endl;
    } else {
        const auto& p = m_PersonArray[idx];
        cout << "姓名：" << p.getName() << endl;
        cout << "性别：" << (p.getSex() == 1 ? "男" : "女") << endl;
        cout << "年龄：" << p.getAge() << endl;
        cout << "电话：" << p.getNumber() << endl;
        cout << "地址：" << p.getAddress() << endl;
    }
}

void ContactList::modifyPerson() {
    if (m_PersonArray.empty()) {
        cout << "通讯录为空，无法修改联系人！" << endl;
        return;
    }
    string name;
    cout << "请输入要修改的联系人姓名：" << endl;
    getline(cin >> ws, name);
    int idx = findIndexByName(name);
    if (idx == -1) {
        cout << "查无此人！" << endl;
        return;
    }
    cout << "正在修改联系人信息..." << endl;
    string input;
    cout << "请输入新的姓名（留空则不修改）：" << endl;
    getline(cin, input);
    if (!input.empty()) m_PersonArray[idx].setName(input);

    cout << "请输入新的性别（男:1;女:2，留空则不修改）：" << endl;
    getline(cin, input);
    if (!input.empty()) {
        int sex = 0;
        stringstream ss(input);
        if (ss >> sex && (sex == 1 || sex == 2)) {
            m_PersonArray[idx].setSex(sex);
        } else {
            cout << "输入错误，性别未修改！" << endl;
        }
    }

    cout << "请输入新的年龄（留空则不修改）：" << endl;
    getline(cin, input);
    if (!input.empty()) {
        int age = 0;
        stringstream ss(input);
        if (ss >> age && age > 0 && age < 150) {
            m_PersonArray[idx].setAge(age);
        } else {
            cout << "输入错误，年龄未修改！" << endl;
        }
    }

    cout << "请输入新的电话（留空则不修改）：" << endl;
    getline(cin, input);
    if (!input.empty()) m_PersonArray[idx].setNumber(input);

    cout << "请输入新的地址（留空则不修改）：" << endl;
    getline(cin, input);
    if (!input.empty()) m_PersonArray[idx].setAddress(input);

    cout << "修改成功！" << endl;
}

void ContactList::clear() {
    m_PersonArray.clear();
    cout << "通讯录已清空！" << endl;
}

void ContactList::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    for (const auto& p : m_PersonArray) {
        ofs << p.getName() << '\n'
            << p.getSex() << '\n'
            << p.getAge() << '\n'
            << p.getNumber() << '\n'
            << p.getAddress() << '\n';
    }
}

void ContactList::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    m_PersonArray.clear();
    while (ifs && m_PersonArray.size() < MAX) {
        std::string name, sexStr, ageStr, number, address;
        if (!std::getline(ifs, name)) break;
        if (!std::getline(ifs, sexStr)) break;
        if (!std::getline(ifs, ageStr)) break;
        if (!std::getline(ifs, number)) break;
        if (!std::getline(ifs, address)) break;

        if (name.empty()) continue;
        try {
            int sex = std::stoi(sexStr);
            int age = std::stoi(ageStr);
            m_PersonArray.emplace_back(name, sex, age, number, address);
        } catch (const std::exception&) {
            continue;
        }
    }
}
