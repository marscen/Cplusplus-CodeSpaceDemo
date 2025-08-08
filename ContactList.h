#pragma once
#include "Person.h"
#include <vector>
#include <string>

class ContactList {
public:
    ContactList();

    void addPerson();
    void showAll() const;
    void deletePerson();
    void findPerson() const;
    void modifyPerson();
    void clear();
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

private:
    int findIndexByName(const std::string& name) const;
    std::vector<Person> m_PersonArray;
    static const int MAX = 1000;
};