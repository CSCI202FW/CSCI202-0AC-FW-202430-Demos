// person class by ChatGPT 4
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person
{
public:
    Person(const std::string &name, int age);

    bool operator==(const Person &other) const;
    bool operator!=(const Person &other) const;
    bool operator<(const Person &other) const;
    bool operator<=(const Person &other) const;
    bool operator>(const Person &other) const;
    bool operator>=(const Person &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Person &person);

    int hash();

private:
    std::string name;
    int age;
};

#endif // PERSON_H
