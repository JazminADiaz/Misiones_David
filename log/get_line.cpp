#include <fstream>
#include <iostream>

int main()
{
    std::string s; //string
    std::fstream f; //file stream
    f.open("wordlist.txt"); //open your word list
    std::getline(f, s); //get line from f (your word list) and put it in s (the string)
    std::cout << s << "\n"; //output string
    return 0;
}