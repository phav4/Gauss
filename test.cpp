// Simple C++ program to take input and give output

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string name;
    int age;

    cout << "Enter your name: ";
    getline(cin, name); // use getline to accept full names

    cout << "Enter your age: ";
    cin >> age;

    cout << "\nHello, " << name << "!" << endl;
    cout << "You are " << age << " years old." << endl;
    cout << "In 5 years, you will be " << age + 5 << " years old." << endl;

    return 0;
}
