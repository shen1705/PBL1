#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <thread>//bo?
#include <chrono>//bo?
#include <cstdlib>
#include "UI.h"

using namespace std;

// utils
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void delay(int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
}

void drawTitle(ostream &os, string title)
{
    const int width = 60;
    os << "+" << string(width - 2, '=') << "+" << endl;
    int padding = (width - 2 - title.length()) / 2;
    os << "|" << setw(padding + title.length()) << right << title
       << setw(width - 2 - padding - title.length() + 1) << "|" << endl;
}

void drawDivider(ostream &os, int width, char symbol)
{
    os << "|" << string(width - 2, symbol) << "|" << endl;
}

void History(ostream &os, int no, double amount, string type)
{
    const int col1 = 6;
    const int col2 = 14;
    const int col3 = 36;

    string amtStr = to_string((int)amount) + " ";
    os << "|" << left << setw(col1) << (" " + to_string(no))
       << "|" << left << setw(col2) << (" " + type)
       << "|" << right << setw(col3) << amtStr << "|" << endl;
}

// 
void TransactionRecordRow(ostream &os, int accnum, string typeStr, double amount)
{
    os << "|" << left << setw(18) << accnum 
       << "|" << left << setw(10) << typeStr
       << "|" << right << setw(28) << fixed << setprecision(2) << amount << "|" << endl;
}
// Main

void drawMenuBox()
{
    clearScreen();
    drawTitle(cout, "WELCOME TO MY_ATM PROGRAM");
    drawDivider(cout, 60, '-');
    const int width = 60;
    cout << "| " << left << setw(width - 4) << "1. Login - Type 1 to Login" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "0. Exit - Type 0 to Exit (Permission required)" << " |" << endl;
    cout << "+" << string(width - 2, '=') << "+" << endl;
}

void drawUserBox(int accnum, double balance, int maxtrans)
{
    clearScreen();
    const int width = 60;

    drawTitle(cout, "ACCOUNT NUMBER: " + to_string(accnum));
    drawDivider(cout, width, '-');

    string balStr = "Balance: " + to_string(balance);
    cout << "| " << left << setw(width - 4) << balStr.substr(0, 20) << " |" << endl;
    string limStr = "Transaction Limit: " + to_string(maxtrans);
    cout << "| " << left << setw(width - 4) << limStr << " |" << endl;
    cout << "|" << string(width - 2, '-') << "|" << endl;

    cout << "| " << left << setw(width - 4) << "1. deposit  - Deposit money - Gửi tiền" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "2. withdraw - Withdraw money - Rút tiền" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "3. history  - Show transactions - Lịch sử giao dịch" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "4. exit     - Log out - Đăng xuất" << " |" << endl;
    cout << "+" << string(width - 2, '=') << "+" << endl;
}

void showMessageAndDelay()
{
    cout << "Processing transaction..." << endl;
    delay(2);
}

void logoutannounce()
{
    cout << "Logging out..." << endl;
    delay(3);
}

void loginfailedannounce()
{
    cout << "Login Failed! Wrong PIN" << endl;
    delay(3);
}

void shutdownAnnounce()
{
    clearScreen();
    cout << "Saving DATA..." << endl;
    delay(2);
    for (int i = 3; i > 0; i--)
    {
        clearScreen();
        cout << "Shutting down in " << i << endl;
        delay(1);
    }
}

void systemMenu()
{
     system("cls");
        cout << "=================================" << endl;
        cout << "         IT ADMIN MENU           " << endl;
        cout << "=================================" << endl;
        cout << "[1]. Start ATM Session (Launch UI)" << endl;
        cout << "[0]. Shutdown Entire Hardware" << endl;
        cout << "=================================" << endl;
}