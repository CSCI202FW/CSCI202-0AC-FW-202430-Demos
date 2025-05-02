#include "person.h"

Person::Person(const std::string &name, int age) : name(name), age(age) {}

bool Person::operator==(const Person &other) const
{
    return this->name == other.name && this->age == other.age;
}

bool Person::operator!=(const Person &other) const
{
    return !(*this == other);
}

bool Person::operator<(const Person &other) const
{
    return this->age < other.age;
}

bool Person::operator<=(const Person &other) const
{
    return this->age <= other.age;
}

bool Person::operator>(const Person &other) const
{
    return this->age > other.age;
}

bool Person::operator>=(const Person &other) const
{
    return this->age >= other.age;
}

int Person::hash()
{
    int sum = 0;
    int len = name.length();
    for (int i = 0; i < 15 - len; i++)
    {
        name = name + " ";
    }
    int index = 0;
    for (int i = 0; i < 5; i++)
    {
        sum = sum + static_cast<int>(name[index]) * 33 * 33 + static_cast<int>(name[index + 1]) * 33 + static_cast<int>(name[index + 2]);
        index = index + 3;
    }
    sum = sum + age;
    return sum;
}

std::ostream &operator<<(std::ostream &os, const Person &person)
{
    os << "Name: " << person.name << ", Age: " << person.age;
    return os;
}
