#include <iostream>
#include <string>
#include <limits>

const int DEFAULT = 0;

void resetStream();
bool intInRange(int num, int lower, int upper);
bool intGT(int num, int lower = 0, int = 0);
bool intLT(int num, int upper = 0, int = 0);
bool intGTEQ(int num, int lower = 0, int = 0);
bool intLTEQ(int num, int upper = 0, int = 0);
int inputInt(std::string &prompt, std::string &err, bool (*valid)(int, int, int), int lower = 0, int upper = 0);
int factorial(int n);

int main()
{
    std::string prompt = "Enter a number between 1 and 50: ";
    std::string err = "You did not enter a number between 1 and 50.";
    int num = inputInt(prompt, err, intInRange, 1, 50);
    std::cout << "Factorial of " << num << " is " << factorial(num) << std::endl;

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int inputInt(std::string &prompt, std::string &err, bool (*valid)(int, int, int), int lower, int upper)
{
    int theNum;
    std::cout << prompt;
    std::cin >> theNum;
    std::cout << std::endl;
    if (std::cin && valid(theNum, lower, upper))
    {
        return theNum;
    }
    if (!std::cin)
    {
        std::cout << "You entered something that is not a number!" << std::endl;
        resetStream();
    }
    std::cout << err << std::endl;
    return inputInt(prompt, err, valid, lower, upper);

    /* if (!std::cin)
    {
        std::cout << "You entered something that is not a number!" << std::endl;
        std::cout << err << std::endl;
        resetStream();
        theNum = inputInt(prompt, err, valid, lower, upper);
    }
    if (!valid(theNum, lower, upper))
    {
        std::cout << err << std::endl;
        theNum = inputInt(prompt, err, valid, lower, upper);
    } */
}

bool intInRange(int num, int lower, int upper)
{
    return num >= lower && num <= upper;
}
bool intGT(int num, int lower, int)
{
    return num > lower;
}
bool intLT(int num, int upper, int)
{
    return num < upper;
}
bool intGTEQ(int num, int lower, int)
{
    return num >= lower;
}
bool intLTEQ(int num, int upper, int)
{
    return num <= upper;
}

int factorial(int n)
{
    if (n < 0)
    {
        return 0;
    }
    if (n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}