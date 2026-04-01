#include "handlecommand.h"
#include "auth.h"
#include "Data.h"
#include "UI.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

void handlecommand(const string &cmd, int &running, User &current, int &user_status, SessionRecord *&Record)
{
    if (cmd == "1") // Deposit - gui tien 
        transaction(current, deposit, 'd', Record);
    else if (cmd == "2") //Withdraw - rut tien
        transaction(current, withdraw, 'w', Record);
    else if (cmd == "3") // Show History
        ShowHistory(current);
    else if (cmd == "4") // log out
    {
        user_status = 0;
    }
    else
    {
        cout << "Invalid Option." << endl;
        delay(3);
    }
}

void shutdown(int &running)
{
    running = 0;
}
void ShowHistory(User &U)
{
    const int width = 100;
    const int col1 = 10;
    const int col2 = 30;
    const int col3 = 56;

    clearScreen();
    int i = 1;
    TransactionList *current = U.List;
    if (current == nullptr)
    {
        drawTitle(cout, "TRANSACTION HISTORY");
        drawDivider(cout, width, '-');
        cout << "| " << left << setw(width - 4) << "Ban chua co lich su giao dich nao." << " |" << endl;
        cout << "+" << string(width - 2, '=') << "+" << endl;
        pauseScreen();
        return;
    }

    drawTitle(cout, "TRANSACTION HISTORY");
    drawDivider(cout, width, '-');
    cout << "|" << left << setw(col1) << " STT"
         << "|" << left << setw(col2) << " LOAI GIAO DICH"
         << "|" << right << setw(col3) << " SO TIEN" << "|" << endl;
    drawDivider(cout, width, '-');

    while (current != nullptr)
    {
        string typeStr = (current->type == 'd') ? "Deposit" : "Withdraw";
        History(cout, i, current->amount, typeStr);
        i++;
        current = current->next;
    }

    cout << "+" << string(width - 2, '=') << "+" << endl;
    pauseScreen();
}

int withdraw(User &U, double amount)
{
    if (U.balance >= amount)
    {
        U.balance -= amount;
        cout << "withdraw successfully. " << U.balance << endl;
        return 1;
    }
    else
    {
        cout << "Invalid.You dont have enough money to withdraw" << endl;
        return 0;
    }
}

int deposit(User &U, double amount)
{
    U.balance += amount;
    cout << "deposit successfully. " << U.balance << endl;
    return 1;
}

void transaction(User &U, int (*type)(User &, double), const char transtype, SessionRecord *&Record)
{
    if (U.maxtrans != 0)
    {
        double amount;
        cout << "Enter amount: ";
        if (!(cin >> amount))
        { // input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ;
            return;
        }
        int success = type(U, amount);

        if (success)
        {
            if (transtype == 'w')
            {
                amount = -amount;
                TransUpdt(U, amount, 'w');
            }
            else if (transtype == 'd')
            {
                TransUpdt(U, amount, 'd');
            }
            TransRecord(U, amount, Record,transtype);
            U.maxtrans--;
            showMessageAndDelay();
            clearScreen();
            drawUserBox(U.accnum, U.balance, U.maxtrans);
        }
        else
        {
            delay(3);
        }
    }
    else
    {
        cout << "Transaction limit reached" << endl;
        delay(3);
    }
}
void TransUpdt(User &U, double amount, char type)
{
    TransactionList *newNode = new TransactionList;
    newNode->amount = amount;
    newNode->type = type;
    newNode->next = U.List;
    U.List = newNode;
}
void TransRecord(User &U, double amount, SessionRecord *&Record,char type)
{
    SessionRecord *newNode = new SessionRecord;
    newNode->accnum = U.accnum;
    newNode->amount = amount;
    newNode->next = Record;
    newNode->type = type;
    Record = newNode;
}
