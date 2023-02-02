#include <iostream>

using namespace std;

int main()
{
    string possible_aah;
    string needed_aah;

    cin >> possible_aah;
    cin >> needed_aah;

    if (possible_aah.length() >= needed_aah.length())
        cout << "go";
    else
        cout << "no";
}