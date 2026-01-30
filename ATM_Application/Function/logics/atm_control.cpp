#include "atm_control.h"
#include "handlecommand.h"
#include "datahandler.h"
#include "Data.h"
#include "UI.h"
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

void runATM()
{
    // data prepare
    unordered_map<int, User> accounts;
    if (!LoadData(accounts))
    {
        cout << "cant load data from file";
    }
    SessionRecord *SessionRecord=nullptr;

    int running = 1; // active status
    system("cls");   // clearscreen

    if (running)
    {
        drawMenuBox();

        while (running)
        {
            string cmd;
            cout << "ATM>";
            cin >> cmd;
            handlecommand(cmd, running, accounts, SessionRecord);
        }
    }
    Record(SessionRecord);
    SaveData(accounts); // Save data at the end of the session
}