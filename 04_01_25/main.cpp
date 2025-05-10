#include <iostream>
#include <limits>
#include <cmath>
#include "linkedStack.h"
#include "drink.h"
#include "arrayStack.h"

void resetStream();
sizeType inputDrinkSize();
baseType inputDrinkBase();
tempType inputDrinkTemperature();
std::string inputDrinkFlavor();
std::string inputDrinkDairy();
bool numInRange(int num, int lower, int upper);
bool numGT0(int num, int = 0, int = 0);
bool negNum(int num, int = 0, int = 0);
int inputInt(std::string prompt, bool (*func)(int, int, int), int lower = 0, int upper = 0);
long getBinaryNumber();

// lecture activity change binary number conversion code to use strings
// subtract '0' from each character in the string to convert it to it's number form.
// note you will only need 1 stack for this method.

int main()
{
    /* drink d(inputDrinkBase(), inputDrinkTemperature(), inputDrinkSize(), inputDrinkDairy(), inputDrinkFlavor()); */

    long binNumber = getBinaryNumber();
    long copyNum = binNumber;
    linkedStack<int> binary;
    arrayStack<int> binReverse;

    //covert getBinary to strings.
    std::string binaryStr = std::to_string(getBinaryNumber());  //get our input in string form
    std::stack<int> binaryStack;                                //make our stack

    for (char c : binaryStr) {                                  //get only 0 or 1 to the stack
        if (c != '0' && c != '1') {
            std::cout << "Binary Numbers only have 1s and 0s." << std::endl;
            return 1; // Indicate an error
        }
        binaryStack.push(c - '0');                             //convert chars 0/1 to ints
    }

    
    //now we start to convert to decimal
    int decimal = 0;
    int position = 0;

    //do the conversion of binary to decimal
    while (!binaryStack.empty()) {                            //while not empty
        decimal += binaryStack.top() * pow(2, position);      //decimal += top stack element at pos n^2
        binaryStack.pop();                                    //after it's added to decimal we pop it off
        position++;                                           //increment postion.
    }

    std::cout << binaryStr << " is " << decimal << " in decimal." << std::endl;

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

sizeType inputDrinkSize()
{
    std::ostringstream out;

    out << "Please choose the drink size:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << sizeStr[i] << std::endl;
    }
    int drinkSize = inputInt(out.str(), numInRange, 1, 3);

    return sizes[drinkSize - 1];
}

baseType inputDrinkBase()
{
    std::ostringstream out;
    out << "Please choose the drink base:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << baseStr[i] << std::endl;
    }
    int drinkBase = inputInt(out.str(), numInRange, 1, 3);

    return bases[drinkBase - 1];
}

tempType inputDrinkTemperature()
{
    std::ostringstream out;
    int drinkTemp;
    out << "Please choose the drink temperature:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << tempStr[i] << std::endl;
    }
    drinkTemp = inputInt(out.str(), numInRange, 1, 3);

    return temps[drinkTemp - 1];
}

std::string inputDrinkFlavor()
{
    std::string flavor;
    std::cout << "Please enter a flavor for your drink: ";
    std::cin >> std::ws;
    std::getline(std::cin, flavor);
    return flavor;
}

std::string inputDrinkDairy()
{
    std::string dairy;
    std::cout << "What kind of dairy would you like? ";
    std::cin >> std::ws;
    std::getline(std::cin, dairy);
    return dairy;
}

int *newArray()
{
    int *list;
    int numRand = inputInt("How many numbers do you want? ", numGT0);
    list = new int[numRand];
    for (int i = 0; i < numRand; i++)
    {
        list[i] = rand() % 50 + 1;
    }
    return list;
}

bool numInRange(int num, int lower, int upper)
{
    return lower <= num && num <= upper;
}

bool numGT0(int num, int, int)
{

    return num > 0;
}

bool negNum(int num, int, int)
{
    return num < 0;
}

int inputInt(std::string prompt, bool (*func)(int, int, int), int lower, int upper)
{
    int theNum;
    std::cout << prompt;
    std::cin >> theNum;
    std::cout << std::endl;
    while (!std::cin || !func(theNum, lower, upper))
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "You have entered invalid data." << std::endl;
        std::cout << prompt;
        std::cin >> theNum;
        std::cout << std::endl;
    }

    return theNum;
}

long getBinaryNumber()
{
    long x;
    std::cout << "Enter a number in binary: ";
    std::cin >> x;
    while (!std::cin || x < 0)
    {
        if (!std::cin)
            resetStream();
        std::cout << "Enter a number in binary: ";
        std::cin >> x;
    }
    return x;
}
