#include "auth.h"
#include "Data.h"
#include "UI.h"
#include <string>
#include <iostream>
#include <limits>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <cctype>
using namespace std;

// Hàm này thay thế hoàn toàn getch() trên Mac
static int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

static string readMaskedInput(bool digitsOnly)
{
    string value;
    while (true)
    {
        int ch = getch();

        // macOS/Linux Enter is '\n' (10); some terminals may still report '\r' (13).
        if (ch == '\n' || ch == '\r')
        {
            break;
        }

        // Backspace is usually 127 on macOS terminal, sometimes 8.
        if (ch == 127 || ch == 8)
        {
            if (!value.empty())
            {
                value.pop_back();
                cout << "\b \b";
            }
            continue;
        }

        if (ch < 32 || ch > 126)
        {
            continue;
        }

        if (digitsOnly && !isdigit(static_cast<unsigned char>(ch)))
        {
            continue;
        }

        value += static_cast<char>(ch);
        cout << '*';
    }

    cout << endl;
    return value;
}

int ITauth() {
    const string system_password = "12345";
    string password;

    cout << "IT AUTHENTICATION REQUIRED" << endl;
    cout << "Enter IT password: ";

    password = readMaskedInput(false);

    if (password == system_password) {
        cout << "Access Granted." << endl;
        delay(2);
        return 1;
    } else {
        cout << "Access Denied." << endl;
        delay(2);
        return 0;
    }
}
int Login(UserList* accounts, User *&currentUser)
{
    string input;
    int accnum;
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
        string pinStr = readMaskedInput(true);
        if (pinStr.empty())
        {
            return 0;
        }

        int pin;
        try
        {
            pin = stoi(pinStr);
        }
        catch (...)
        {
            loginfailedannounce();
            return 0;
        }

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