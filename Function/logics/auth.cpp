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
#include <iomanip>
using namespace std;

static const int LOGIN_FRAME_WIDTH = 100;

static void drawLoginFieldLine(const string &label, const string &value)
{
    const int innerWidth = LOGIN_FRAME_WIDTH - 4;
    string line = label + value;
    if (static_cast<int>(line.size()) > innerWidth)
    {
        line = line.substr(0, innerWidth);
    }
    cout << "| " << left << setw(innerWidth) << line << " |" << endl;
}

static void drawCredentialBox(const string &accNumValue, const string &pinValue, const string &note)
{
    clearScreen();
    cout << "+" << string(LOGIN_FRAME_WIDTH - 2, '=') << "+" << endl;
    cout << "| " << left << setw(LOGIN_FRAME_WIDTH - 4) << "WELCOME TO ATM" << " |" << endl;
    cout << "|" << string(LOGIN_FRAME_WIDTH - 2, '-') << "|" << endl;
    if (!note.empty())
    {
        drawLoginFieldLine("Thong bao: ", note);
    }
    else
    {
        drawLoginFieldLine("Thong bao: ", "Vui long nhap thong tin dang nhap.");
    }
    drawLoginFieldLine("Huong dan: ", "Nhap 'IT' tai Acc Num neu can xac thuc IT.");
    cout << "|" << string(LOGIN_FRAME_WIDTH - 2, '-') << "|" << endl;
    drawLoginFieldLine("Acc Num  : ", accNumValue);
    drawLoginFieldLine("Enter PIN: ", pinValue);
    cout << "+" << string(LOGIN_FRAME_WIDTH - 2, '=') << "+" << endl;
}

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

    drawCredentialBox("", "", "Nhap Acc Num roi nhan Enter.");
    cout << "| Acc Num  : ";
    if (!getline(cin >> ws, input))
    {
        cin.clear();
        return 0;
    }

    if (input == "IT")
    {
        drawCredentialBox(input, "", "Yeu cau xac thuc IT.");
        cout << "\n[SYSTEM] IT authentication requested." << endl;
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
        drawCredentialBox(to_string(accnum), "", "Tai khoan hop le. Vui long nhap PIN.");
        cout << "| Enter PIN: ";
        string pinStr = readMaskedInput(true);
        if (pinStr.empty()) return 0;

        int pin;
        try { pin = stoi(pinStr); }
        catch (...) { loginfailedannounce(); return 0; }

        if (pin == current->data.PIN)
        {
            drawCredentialBox(to_string(accnum), string(pinStr.size(), '*'), "Dang nhap thanh cong.");
            currentUser = &(current->data);
            return 1;
        }
        else
        {
            drawCredentialBox(to_string(accnum), string(pinStr.size(), '*'), "PIN khong dung. Vui long thu lai.");
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