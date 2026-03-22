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

void runATM()
{
    // data prepare
    UserList* accounts = nullptr;
    if (!LoadData(accounts))
    {
        cout << "cant load data from file";
    }
    SessionRecord *sessionrecord = nullptr;
    int system_running = 1; // active status
    struct User *currentUser = nullptr;

    while (system_running)
    {
        system("cls");
        drawMenuBox();
        string menuOption;
        cout << "Select Option: ";

        if (!(cin >> menuOption))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');;
        if (menuOption == "1")
        {
            int LoggedIn = Login(accounts, currentUser);
            if (LoggedIn == 1 && currentUser != nullptr)
            {
                int user_status = 1;
                while (user_status)
                {
                    {
                        drawUserBox(currentUser->accnum, currentUser->balance, currentUser->maxtrans);
                        string cmd;
                        cout << "ATM>";
                        cin >> cmd;
                        handlecommand(cmd, system_running, *currentUser, user_status, sessionrecord);
                    }
                }
                logoutannounce();
                
            }
        }
        else if (menuOption == "0")
        {
            if (ITauth())
            {
                system_running = 0;
            }
        }
        else {cout<<"Invalid Option."<<endl;
            delay(3);
        }
        // Save data at the end of the session
    }
    shutdownAnnounce();
    Record(sessionrecord);
    SaveData(accounts);
    UserList* current = accounts;
    while (current != nullptr) {
        FreeHistory(current->data); 
        UserList* temp = current;
        current = current->next;
        delete temp; 
    }
    accounts = nullptr;
}