#include "atm_control.h"
#include "handlecommand.h"
#include "datahandler.h"
#include "Data.h"
#include <unordered_map>
#include <string>
#include <iostream>


using namespace std;


void runATM(){
    //data prepare
    unordered_map<int,User> accounts;
    if(!LoadData(accounts)){
        cout<< "cant load data from file";
    }
    SessionRecord SessionRecord;
    
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
    Record(SessionRecord);
    SaveData(accounts); // Save data at the end of the session
}


