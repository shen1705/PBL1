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


static UserList *accounts = nullptr;
static SessionRecord *sessionRec = nullptr;
static User *currentUser = nullptr;
static bool atm_running = false;


bool SystemStart()
{
    clearScreen();
    drawProjectIntro();
    cout << "=== SYSTEM BOOTING ===" << endl;

    // IT Auth
    if (!ITauth())
    {
        cout << "Fatal Error: IT Authentication Failed. Shutting down..." << endl;
        delay(3);
        return false; 
    }

    // Load Data
    if (!LoadData(accounts))
    {
        cout << "Can't load data from file!" << endl;
        delay(2);
        return false;
    }

    atm_running = true;
    return true;
}

bool IsSystemRunning()
{
    return atm_running;
}

bool SystemLogin()
{
    int login_status = Login(accounts, currentUser);

    if (login_status == 1 && currentUser != nullptr) 
    {
        return true; 
    }
    else if (login_status == -1)
    {   
      
        drawManagerBox();
        while(1)
        { 
            string cmd;
            cout << "\nSelect Option: ";
            if (!(cin >> cmd))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (cmd == "1") // Shutdown
            {
                atm_running = false;
                break;
            }
            else if (cmd == "2") 
            {
                break; 
            }
            else
            {
                cout << "Invalid Option." << endl;
                delay(3);
            }
        }
        return false;
    }
    return false; 
}

void RunUserSession()
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
}

void SystemLogout()
{
    logoutannounce();
    currentUser = nullptr;
}

void SystemShutdown()
{
    clearScreen();
    cout << "[SYSTEM] LUU DU LIEU NGUOI DUNG..." << endl;
    SaveData(accounts);
    delay(1);
    cout << "Luu du lieu nguoi dung thanh cong." << endl;
    
    delay(1);
    cout << ">> Dang luu lich su giao dich..." << endl;
    Record(sessionRec);
    cout << "Luu lich su giao dich thanh cong." << endl;
    
    delay(1);
    shutdownAnnounce();

    
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