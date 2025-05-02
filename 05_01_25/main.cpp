#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <string>
#include <cmath>
#include <vector>
#include <functional>
#include <random>
#include "person.h"

const int HT_SIZE = 10007;

// lecture activity implement universal hashing (number 6) from https://www.geeksforgeeks.org/hash-functions-and-list-types-of-hash-functions/
// rerun both experiments
// submit the clustered and uniform distribution results

void setup();
int hash(int);
int hashing_midsquare(long key, int size);

int main()
{
    setup();
    std::ifstream in("exp.txt");
    int ht[HT_SIZE];
    int collisions = 0;
    int count = 0;
    unsigned long probeCount = 0;

    for (int i = 0; i < HT_SIZE; i++)
    {
        ht[i] = -1;
    }

    while (!in.eof())
    {
        int num;
        in >> num;
        int hashValue = hash(num);
        if (ht[hashValue] == -1)
        {
            ht[hashValue] = num;
            std::cout << num << " inserted at " << hashValue << std::endl;
            count++;
        }
        else
        {
            std::cout << num << " collided with " << ht[hashValue] << std::endl;
            collisions++;
            bool found = false;
            int pCount = 0;
            int i = 1;
            while (ht[hashValue] != -1 && !found)
            {
                if (ht[hashValue] == num)
                {
                    found = true;
                }
                else
                {
                    hashValue = hashValue + i % HT_SIZE;
                    probeCount++;
                    pCount++;
                }
            }
            if (found)
            {
                collisions--;
                probeCount -= pCount;
                std::cout << "Duplicates are not allowed" << std::endl;
            }
            else
            {
                ht[hashValue] = num;
                count++;
            }
        }
    }

    std::cout << "There were " << collisions << " collisions." << std::endl;
    std::cout << "There were " << count << " items inserted." << std::endl;

    Person **people = new Person *[13];
    Person james("james", 28);
    Person semaj("semaj", 28);
    int jamesHash = james.hash();
    int semajHash = semaj.hash();
    jamesHash = jamesHash % 13;
    semajHash = semajHash % 13;
    people[jamesHash] = &james;
    people[semajHash] = &semaj;

    return 0;
}

void setup()
{
    std::ofstream out("exp.txt");
    std::unordered_set<int> randomData;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1000);
    std::uniform_int_distribution<int> distribution2(1, 9);
    std::uniform_int_distribution<int> distribution3(100000, 999999);
    while (randomData.size() < 5000)
    {
        int num = 0;
        // num = distribution2(generator) * 100000 + distribution(generator);
        num = distribution3(generator);
        randomData.insert(num);
    }
    for (int i : randomData)
    {
        out << i << std::endl;
    }
    out.close();
}

int hash(int key)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, 1);
    static double A = distribution(generator);
    double hash;
    double fraction = std::modf(key * A, &hash);
    hash = HT_SIZE * fraction;
    hash = floor(hash);
    return static_cast<int>(hash);
    //  return key % HT_SIZE;
    // return hashing_midsquare(key, 4);
}

int hashing_midsquare(long key, int size)
{
    int squareLen = 0;
    int mid_pos = 0;
    unsigned long keysquare = key * key;
    std::string squaredStr = std::to_string(keysquare);
    squareLen = squaredStr.length();
    if (squareLen < size)
    {
        squaredStr = std::string(size - squareLen, '0') + squaredStr;
        squareLen = size;
    }
    mid_pos = (squareLen - size) / 2;
    std::string midDigits = squaredStr.substr(mid_pos, size);
    return std::stoi(midDigits) % HT_SIZE;
}