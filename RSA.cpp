
#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
#include <vector>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>


// to increase the size of the primes you can use
// change the data type from int(64bit)
// to a custom type (cpp_int above 128 bit )
// this is because the decrypt, encrypt and keygen processes 
// raises a large numbers to more large numbers
// easily exceding 64bit limits

namespace mp = boost::multiprecision;
mp::cpp_int p = 89;
mp::cpp_int q = 59;


mp::cpp_int gcd(mp::cpp_int m, mp::cpp_int n);
mp::cpp_int find_coprime(mp::cpp_int tot);
mp::cpp_int find_decrypt(mp::cpp_int e, mp::cpp_int tot);

void newprimes();

void encrypt();
void decrypt();



int main()
{
    char cinput;
    std::cout << "Encrypt(1) or decrypt(2)\n";
    std::cin >> cinput;
    int input = (int)cinput - 48;

    if (input == 1)
        encrypt();
    if (input == 2)
        decrypt();

}

void decrypt()
{
    int d, n;
    std::string input;
    std::cout << "Enter Numbers\n";

    std::cout << "d: ";
    std::cin >> input;
    d = stoi(input);

    std::cout << "n: ";
    std::cin >> input;
    n = stoi(input);

    std::cout << "Enter Cypher as integers, with spaces between each character\n: ";
    std::cin >> input;

    /*
    std::vector<mp::cpp_int> msg;
    std::stringstream ss(input);
    std::string temp;
    while (ss >> temp)
        msg.push_back(mp::cpp_int(temp));
        

    std::cout << "Decrypted Message: ";
    for (auto i : msg)
        std::cout << static_cast<char>(mp::pow(i, d) % n);
    */
    // only does one letter right now
    std::cout << static_cast<char>(mp::pow(mp::cpp_int(input), d) % n)  << std::endl;

}



void encrypt()
{
    /*
    char cinput;
    std::cout << "enter new primes(2) or use default(1)\n";
    std::cin >> cinput; 
    int input = (int)cinput - 48;
    if (input == 2)
        newprimes();
    */
    mp::cpp_int tot = (p-1)* (q-1);
    mp::cpp_int n = p*q;

    mp::cpp_int e = find_coprime(tot);

    mp::cpp_int d = find_decrypt(e, tot);

    std::cout << "\x1B[2J\x1B[H";

    std::cout << "n: " << n << "\n";

    std::cout << "e: " << e << "\n";
    std::cout << "d: " << d << "\n";

    std::string msg;
    std::cout << "Message to Send\n:";
    std::cin >> msg;


    std::string encrypted;

    for (char& c : msg)
    {
        std::cout << (mp::pow((mp::cpp_int)c, static_cast<int>(e)) % n) << '\n';
    }



};

mp::cpp_int find_decrypt(mp::cpp_int e, mp::cpp_int tot) 
{
    mp::cpp_int k = 1;

    while (((k * tot) + 1) % e != 0)
    {
        k++;
    }
    return ((k * tot) + 1) / e;
}


mp::cpp_int find_coprime(mp::cpp_int tot)
{
    mp::cpp_int i = 3;
    while (true)
    {
        if (gcd(i, tot) == 1) 
            return i;
        i++;
    }
}


// https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/
mp::cpp_int gcd(mp::cpp_int m, mp::cpp_int n)
{
    if (n)
        return gcd(n, m % n);
    else
        return m;
}


void newprimes()
{
    std::string input;
    std::cout << "Prime 1(p): ";
    std::cin >> input;
    p = stoi(input);

    std::cout << "Prime 2(q): ";
    std::cin >> input;
    q = stoi(input);
}