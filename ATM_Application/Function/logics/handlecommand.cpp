#include "handlecommand.h"
#include "auth.h"
#include "Data.h"
#include "UI.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void handlecommand(const string &cmd, int &running, User &current, int &user_status, SessionRecord *&Record)
{
    if (cmd == "deposit")
        transaction(current, deposit, 'd', Record);
    else if (cmd == "withdraw")
        transaction(current, withdraw, 'w', Record);
    else if (cmd == "history")
        ShowHistory(current);
    else if (cmd == "exit" || cmd == "logout")
    {
        user_status = 0;
    }
    else if (cmd == "shutdown")
    {
        if (ITauth())
            shutdown(running);
        else
            cout << "Authorization is failed" << std::endl;
    }
    else
        cout << "Unknown command." << endl;
}
void shutdown(int &running)
{
    running = 0;
}
void ShowHistory(User &U)
{
    int i = 1;
    TransactionList *current = U.List;
    if (current == nullptr)
    {
        cout << "No history found." << endl;
        delay(2);
        return;
    }
    drawTitle(cout, "Transaction History");
    while (current != nullptr)
    {
        string typeStr = (current->type == 'd') ? "Deposit" : "Withdraw";
        History(cout, i, current->amount, typeStr);
        i++;
        current = current->next;
    }
    cout << "+" << string(58, '=') << "+" << endl;
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
            delay(2);
        }
    }
    else
    {
        cout << "Transaction limit reached" << endl;
        delay(2);
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
