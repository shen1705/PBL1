#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include "UI.h"

using namespace std;

void drawTitle(ostream &os, string title)
{
    const int width = 60;
    os << "+" << string(width - 2, '=') << "+" << endl;
    int padding = (width - 2 - title.length()) / 2;
    os << "|" << setw(padding + title.length()) << right << title
       << setw(width - 2 - padding - title.length() + 1) << "|" << endl;
    os << "+" << string(width - 2, '=') << "+" << endl;
    cout << "|" << string(width - 2, '-') << "|" << endl;
}

void drawUserBox(int accnum, double balance, int maxtrans)
{
    system("cls");
    const int width = 60;
    drawTitle("Account Number: "+to_string(accnum));

    string balStr = "Balance: " + to_string(balance);
    cout << "| " << left << setw(width - 4) << balStr.substr(0, 20) << " |" << endl;

    string limStr = "Transaction Limit: " + to_string(maxtrans);
    cout << "| " << left << setw(width - 4) << limStr << " |" << endl;

    cout << "|" << string(width - 2, '-') << "|" << endl;

    cout << "| " << left << setw(width - 4) << "deposit  - Deposit money" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "withdraw - Withdraw money" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "history  - Show transactions" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "exit     - Log out" << " |" << endl;

    cout << "+" << string(width - 2, '=') << "+" << endl;
}

void drawMenuBox()
{
    const int width = 60;
    drawTitle("WELCOME TO MY ATM");
    cout << "| " << left << setw(width - 4) << "1. Login - Type 1 to Login" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "0. Shutdown - Type 0 to shutdown the program" << " |" << endl;
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
    delay(2);
}

void shutdownAnnounce()
{
    system("cls");
    cout << "Saving DATA..." << endl;
    delay(2);

    for (int i = 3; i > 0; i--)
    {
        system("cls");
        cout << "Shutting down in " << i << endl;
        delay(1);
    }
}
void History(int no, double amount, string type)
{
    const int col1_w = 6;  
    const int col2_w = 14; 
    const int col3_w = 36; 

    string amtStr = to_string((int)amount) + " "; 

    cout << "|" << left << setw(col1_w) << (" " + to_string(no))
         << "|" << left << setw(col2_w) << (" " + type)
         << "|" << right << setw(col3_w) << amtStr << "|" << endl;
}


void delay(int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
}
