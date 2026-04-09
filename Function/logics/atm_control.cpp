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
void RunUserSession(User *currentUser, SessionRecord *&sessionRec)
{
    int user_status = 1;
    while (user_status)
    {
        drawUserBox(currentUser->accnum, currentUser->balance, currentUser->maxtrans);
        string cmd;
        cout << "\nSelect Option: ";
        if (!(cin >> cmd))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        handlecommand(cmd, *currentUser, user_status, sessionRec);
    }
    logoutannounce();
}

void runATM()
{
    UserList *accounts = nullptr;
    if (!LoadData(accounts))
    {
        cout << "Can't load data from file!" << endl;
        delay(2);
        return;
    }
    SessionRecord *sessionRec = nullptr;
    int atm_running = 1;
    User *currentUser = nullptr;

    // system running
    while (atm_running)
    {
        int login_status = Login(accounts, currentUser);

        if (login_status == 1 && currentUser != nullptr) // log in
        {
            // user session
            RunUserSession(currentUser, sessionRec);
        }
        else if (login_status == -1)
        {   drawManagerBox();
            while(1){ 
                string cmd;
                cout << "\nSelect Option: ";
                if (!(cin >> cmd))
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (cmd == "1") // shutdown
                {
                    atm_running = 0;break;
                }
                else if (cmd == "2") break;
                else
                {
                    cout << "Invalid Option." << endl;
                    delay(3);
                }
            }
        }
    }
    clearScreen();
    cout << "[SYSTEM] LUU DU LIEU NGUOI DUNG..." << endl;
    SaveData(accounts); // save data cua user
    delay(1);
    cout << "Luu du lieu nguoi dung thanh cong." << endl;
    delay(1);
    cout << ">> Dang luu lich su giao dich..." << endl;
    Record(sessionRec); // save lich su giao dich cua atm
    cout << "Luu lich su giao dich thanh cong." << endl;
    delay(1);
    shutdownAnnounce(); // UI

    // free
    UserList *current = accounts;
    while (current != nullptr)
    {
        FreeHistory(current->data);
        UserList *temp = current;
        current = current->next;
        delete temp;
    }
    accounts = nullptr;
    SessionRecord *currentSession = sessionRec;
    while (currentSession != nullptr)
    {
        SessionRecord *tempSession = currentSession;
        currentSession = currentSession->next;
        delete tempSession;
    }
    sessionRec = nullptr;
}

void BootSystem()
{
    clearScreen();
    drawProjectIntro();
    cout << "=== SYSTEM BOOTING ===" << endl;

    // it auth
    if (!ITauth())
    {
        cout << "Fatal Error: IT Authentication Failed. Shutting down..." << endl;
        delay(3);
        return; // exit
    }

    // run atm sau khi xac minh
    runATM();
}