#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include "UI.h"
using namespace std;

void drawHelpBox()
{   system("cls");
    const int width = 60; 
    string title = "MY ATM";
    cout << "+" << string(width - 2, '=') << "+" << endl;

    int padding = (width - 2 - title.length()) / 2;
    cout << "|" << setw(padding + title.length()) << right << title
         << setw(width - 2 - padding - title.length() + 1) << "|" << endl;
    cout << "|" << string(width - 2, '-') << "|" << endl;

    cout << "| " << left << setw(width - 4) << "deposit   - Deposit money" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "withdraw  - Withdraw money" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "balance   - Show balance" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "history   - Show transactions" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "shutdown  - Shutdown ATM" << " |" << endl;

    cout << "+" << string(width - 2, '=') << "+" << endl;
}

void drawMenuBox()
{
    const int width = 60; 
    string title = "WELCOME TO MY ATM PROGRAM";
    cout << "+" << string(width - 2, '=') << "+" << endl;

    int padding = (width - 2 - title.length()) / 2;
    cout << "|" << setw(padding + title.length()) << right << title
         << setw(width - 2 - padding - title.length() + 1) << "|" << endl;
    cout << "|" << setw(padding + title.length()) << right << "Type help for more information"
         << setw(width - 2 - padding - title.length() + 1) << "|" << endl;

    cout << "+" << string(width - 2, '=') << "+" << endl;

}

void showMessageAndDelay() {
    cout << "Processing transaction..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
}


