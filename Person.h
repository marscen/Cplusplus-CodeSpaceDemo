#pragma once
#include <string>

class Person {
public:
    Person() = default;
    Person(const std::string& name, int sex, int age, const std::string& number, const std::string& address)
        : m_Name(name), m_Sex(sex), m_Age(age), m_Number(number), m_Address(address) {}

    // getter/setter
    std::string getName() const { return m_Name; }
    int getSex() const { return m_Sex; }
    int getAge() const { return m_Age; }
    std::string getNumber() const { return m_Number; }
    std::string getAddress() const { return m_Address; }

    void setName(const std::string& name) { m_Name = name; }
    void setSex(int sex) { m_Sex = sex; }
    void setAge(int age) { m_Age = age; }
    void setNumber(const std::string& number) { m_Number = number; }
    void setAddress(const std::string& address) { m_Address = address; }

private:
    std::string m_Name;
    int m_Sex;
    int m_Age;
    std::string m_Number;
    std::string m_Address;
};