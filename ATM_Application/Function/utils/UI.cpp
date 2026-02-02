#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <thread> // For sleep_for
#include <chrono> // For seconds
#include <cstdlib> // For system()
#include "UI.h"

using namespace std;


//utils
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear"); 
    #endif
}

void pauseScreen() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void delay(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void drawTitle(ostream &os, string title) {
    const int width = 60;
    os << "+" << string(width - 2, '=') << "+" << endl;
    int padding = (width - 2 - title.length()) / 2;
    os << "|" << setw(padding + title.length()) << right << title
       << setw(width - 2 - padding - title.length() + 1) << "|" << endl;
    os << "+" << string(width - 2, '=') << "+" << endl;
}

void drawDivider(ostream &os, int width, char symbol) {
    os << "|" << string(width - 2, symbol) << "|" << endl;
}

void History(ostream &os, int no, double amount, string type) {
    const int col1 = 6;  
    const int col2 = 14; 
    const int col3 = 36; 

    string amtStr = to_string((int)amount) + " "; 
    os << "|" << left << setw(col1) << (" " + to_string(no))
       << "|" << left << setw(col2) << (" " + type)
       << "|" << right << setw(col3) << amtStr << "|" << endl;
}

void TransactionRecordRow(ostream &os, int accNum, double amount) {
    const int col1 = 20;
    const int col2 = 36;
    string accStr = " " + to_string(accNum);
    string amtStr = to_string((int)amount) + " ";
    os << "|" << left << setw(col1) << accStr
       << "|" << right << setw(col2) << amtStr << "|" << endl;
}

// Main

void ShowHistory(User &U) {
    clearScreen(); 
    const int width = 60;

    drawTitle(cout, "Transaction History"); 
    drawDivider(cout,width,'-');
    cout << "|" << left << setw(6) << " No."
         << "|" << left << setw(14) << " Type"
         << "|" << right << setw(36) << "Amount " << "|" << endl;

    cout << "|" << string(6, '-') << "+" << string(14, '-') << "+" << string(36, '-') << "|" << endl;

    TransactionList *current = U.List;
    if (current == nullptr) {
        cout << "|" << left << setw(width - 4) << " No history found." << " |" << endl;
    } else {
        int i = 1;
        while (current != nullptr) {
            string typeStr = (current->type == 'd') ? "Deposit" : "Withdraw";
            History(cout, i, current->amount, typeStr);
            i++;
            current = current->next;
        }
    }
    
    cout << "+" << string(width - 2, '=') << "+" << endl;
    pauseScreen(); 
}

void drawMenuBox() {
    clearScreen(); 
    drawTitle(cout, "WELCOME TO MY ATM PROGRAM");
    const int width = 60;
    cout << "| " << left << setw(width - 4) << "1. Login - Type 1 to Login" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "0. Shutdown - Type 0 to shutdown the program" << " |" << endl;
    cout << "+" << string(width - 2, '=') << "+" << endl;
}

void drawUserBox(int accnum, double balance, int maxtrans) {
    clearScreen(); 
    const int width = 60;
    
    drawTitle(cout,"Account Number: "+to_string(accnum));
    drawDivider(cout,width,'-');

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

void showMessageAndDelay() {
    cout << "Processing transaction..." << endl;
    delay(2); 
}

void logoutannounce() {
    cout << "Logging out..." << endl;
    delay(3);
}

void loginfailedannounce() {
    cout << "Login Failed! Wrong PIN" << endl;
    delay(3);
}

void shutdownAnnounce() {
    clearScreen();
    cout << "Saving DATA..." << endl;
    delay(2);
    for (int i = 3; i > 0; i--) {
        clearScreen();
        cout << "Shutting down in " << i << endl;
        delay(1);
    }
}