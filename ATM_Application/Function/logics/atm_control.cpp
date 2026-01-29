#include "atm_control.h"
#include "handlecommand.h"
#include "datahandler.h"
#include "User.h"
#include <unordered_map>
#include <string>
#include <iostream>


using namespace std;


void runATM(){
    //data prepare
    unordered_map<int,User> accounts;
    if(!LoadData(accounts))cout<<"cant load data from files";
    int running = 1;//active status
    system("cls");//clearscreen
    if(running) cout<< "Status: Running "<<endl;
    cout<<"=================================="<<endl;
    cout<< "type 'help' for list of commands"<<endl;
    while(running){
        string cmd;
        cout<< "ATM>";
        cin>> cmd; 
        handlecommand(cmd,running,accounts);
    }
    Record(history,ammount);
    SaveData(accnum,PIN,balance,count); // Save data at the end of the session
}


