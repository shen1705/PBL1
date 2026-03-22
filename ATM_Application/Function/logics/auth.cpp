#include "auth.h"
#include "Data.h"
#include "UI.h"
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int ITauth()
{
    const string system_password = "12345";
    string password = "";

    cout << "IT AUTHENTICATION REQUIRED" << endl;
    cout << "Enter IT password: ";

    if (!(cin >> password))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (password == system_password)
    {
        cout << "Access Granted." << endl;
        delay(2);
        return 1;
    }
    else
    {
        cout << "Access Denied." << endl;
        delay(3);
        return 0;
    }
}

int Login(UserList* accounts, User *&currentUser)
{
    string input;
    int accnum, pin;
    cout << "\n===== LOGIN REQUIRED =====" << endl;
    cout << "Please login for further actions" << endl;
    cout << "Enter your account number: ";
    if (!(cin >> input))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    try
    {
        accnum = stoi(input);
    }
    catch (...)
    {
        cout << "Invalid Input. Please enter a number." << endl;
        delay(2);
        return 0;
    }
    //search
    UserList* current = accounts;
    bool found = false;

    while (current != nullptr)
    {
        if (current->data.accnum == accnum)
        {
            found = true;
            break;
        }
        current = current->next;
    }

    if (found)
    {
        cout << "Enter PIN: ";
        if (!(cin >> pin))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return 0;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pin == current->data.PIN)
        {
            currentUser = &(current->data);
            return 1;
        }
        else
        {
            loginfailedannounce();
            return 0;
        }
    }
    else
    {
        cout << "Login Failed! Can not find your account number" << endl;
        delay(2);
        return 0;
    }
}