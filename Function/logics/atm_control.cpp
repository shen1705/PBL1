#include "atm_control.h"
#include "handlecommand.h"
#include "datahandler.h"
#include "Data.h"
#include "auth.h"
#include "UI.h"
#include <limits>
#include <string>
#include <iostream>

using namespace std;

// Customer Session (LOGIN)
void RunUserSession(User* currentUser, int& system_running, SessionRecord*& sessionRec) 
{
    int user_status = 1; 
    while (user_status) 
    {
        drawUserBox(currentUser->accnum, currentUser->balance, currentUser->maxtrans);
        string cmd;
        cout << "\nSelect Option: ";
        if (!(cin >> cmd)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        handlecommand(cmd, system_running, *currentUser, user_status, sessionRec);
        if (system_running == 0) {
            break; 
        }
    }
    logoutannounce();
}


void runATM()
{
    UserList* accounts = nullptr; 
    if (!LoadData(accounts)) {
        cout << "Can't load data from file!" << endl;
        delay(2);
        return; 
    }
    
    SessionRecord *sessionRec = nullptr; 
    int atm_running = 1;
    User *currentUser = nullptr;
    
    while (atm_running)
    {
        int login_status = Login(accounts, currentUser);
        
        if (login_status == 1 && currentUser != nullptr)
        {
            int dummy_system = 1; 
            RunUserSession(currentUser, dummy_system, sessionRec);
        }
        else if (login_status == -1)
        {
            atm_running = 0; 
        }
    }
    

    SaveData(accounts);
    Record(sessionRec);
    shutdownAnnounce();

    UserList* current = accounts;
    while (current != nullptr) {
        FreeHistory(current->data);
        UserList* temp = current;
        current = current->next;
        delete temp; 
    }
    accounts = nullptr;
}


void BootSystem()
{
    drawProjectIntro();
    cout << "=== SYSTEM BOOTING ===" << endl;
    if (!ITauth()) {
        cout << "Fatal Error: IT Authentication Failed. Shutting down hardware..." << endl;
        delay(3);
        return; //exit 
    }
    int hardware_running = 1;
    while (hardware_running)
    {
        systemMenu();
        string cmd;
        cout << "Admin> ";
        cin >> cmd;
        if (cmd == "1") {
            //run atm
            runATM(); 
        }
        else if (cmd == "0") {
            cout << "Shutting down all hardware components..." << endl;
            delay(2);
            hardware_running = 0; 
        }
        else {
            cout << "Invalid." << endl;
            delay(2);
        }
    }
}