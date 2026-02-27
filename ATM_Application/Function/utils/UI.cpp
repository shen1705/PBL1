#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <thread> 
#include <chrono> 
#include <cstdlib> 
#include "UI.h"

using namespace std;



void pauseScreen() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void delay(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void drawTitle(string title) {
    const int width = 60;
    cout << "+" << string(width - 2, '=') << "+" << endl;
    int padding = (width - 2 - title.length()) / 2;
    cout << "|" << setw(padding + title.length()) << right << title
       << setw(width - 2 - padding - title.length() + 1) << "|" << endl;
}

void drawDivider(int width, char symbol) {
    cout << "|" << string(width - 2, symbol) << "|" << endl;
}

void History(int no, double amount, string type) {
    const int col1 = 6;  
    const int col2 = 14; 
    const int col3 = 36; 

    string amtStr = to_string((int)amount) + " "; 
    cout << "|" << left << setw(col1) << (" " + to_string(no))
       << "|" << left << setw(col2) << (" " + type)
       << "|" << right << setw(col3) << amtStr << "|" << endl;
}

void TransactionRecordRow( int accNum, double amount) {
    const int col1 = 20;
    const int col2 = 36;
    string accStr = " " + to_string(accNum);
    string amtStr = to_string((int)amount) + " ";
    cout << "|" << left << setw(col1) << accStr
       << "|" << right << setw(col2) << amtStr << "|" << endl;
}

// Main

void drawMenuBox() {
    system("cls"); 
    drawTitle("WELCOME TO MY ATM PROGRAM");
    drawDivider(60,'-');
    const int width = 60;
    cout << "| " << left << setw(width - 4) << "1. Login - Type 1 to Login" << " |" << endl;
    cout << "| " << left << setw(width - 4) << "0. Shutdown - Type 0 to shutdown the program" << " |" << endl;
    cout << "+" << string(width - 2, '=') << "+" << endl;
}   

void drawUserBox(int accnum, double balance, int maxtrans) {
    system("cls"); 
    const int width = 60;
    
    drawTitle("Account Number: "+to_string(accnum));
    drawDivider(width,'-');

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
    system("cls");
    cout << "Saving DATA..." << endl;
    delay(2);
    for (int i = 3; i > 0; i--) {
        system("cls");
        cout << "Shutting down in " << i << endl;
        delay(1);
    }
}