#include "auth.h"
#include "Data.h"
#include "UI.h"
#include <string>
#include <iostream>
#include <limits>
#include <conio.h>
#include <unistd.h>
#include <stdio.h>
#include <cctype>
using namespace std;

string getHiddenInput() {
    string input = "";
    char ch;
    
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') { //backspace
            if (input.length() > 0) {
                input.pop_back(); 
                cout << "\b \b";  
            }
        } else if (ch != '\n') { 
            input += ch;
            cout << "*"; // *
        }
    }
    cout << endl;
    return input;
}

int ITauth() {
    const string system_password = "12345";
    string password;

    cout << "IT AUTHENTICATION REQUIRED" << endl;
    cout << "Enter IT password: ";

    password = getHiddenInput();

    if (password == system_password) {
        cout << "Access Granted." << endl;
        delay(3);
        return 1;
    } else {
        cout << "Access Denied." << endl;
        delay(3);
        return 0;
    }
}
int Login(UserList* accounts, User *&currentUser)
{
    string input;
    int accnum;
    
    cout << "\n===== WELCOME TO ATM =====" << endl;
    cout << "Please enter your Account Number to proceed." << endl;
    cout << "Acc Num: ";
    
    if (!(cin >> input))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (input == "admin" || input == "IT")//hidden input
    {
        cout << "\n[SYSTEM] Maintenance Mode Requested." << endl;
        if (ITauth()) {
            return -1; 
        }
        return 0;
    }

    try
    {
        accnum = stoi(input);
    }
    catch (...)
    {
        cout << "Invalid Input. Please enter a valid account number." << endl;
        delay(2);
        return 0;
    }

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
        string pinStr = getHiddenInput();
        if (pinStr.empty()) return 0;

        int pin;
        try { pin = stoi(pinStr); }
        catch (...) { loginfailedannounce(); return 0; }

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