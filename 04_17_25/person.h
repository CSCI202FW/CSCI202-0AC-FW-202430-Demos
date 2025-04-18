#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Person
{
public:
    Person() {};
    Person(const std::string &n, int a, double h)
        : name(n), age(a), height(h) {}

    void print() const
    {
        std::cout << name << " (Age: " << age << ", Height: " << height << " cm)\n";
    }
    std::string getName() const { return name; };
    int getAge() const { return age; };
    double getHeight() const { return height; };

private:
    std::string name;
    int age;
    double height; // in cm
};
#endif