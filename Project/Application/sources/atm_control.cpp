#include "Application/includes/atm_control.h"
#include "Application/includes/handlecommand.h"
#include "Application/includes/datahandler.h"
#include <string>
#include <iostream>


using namespace std;


void runATM(){
    int accnum[100];
    int PIN[100];
    double balance[100]; 
    int current[100];
    double ammount[100];//transaction ammount history
    int history[100];//acc num ammount history
    int count = LoadData(accnum,PIN,balance);//load data + return count at the start of the session
    for(int i = 0;i<count;i++){
        current[i]=5;
        history[i]=0;
        ammount[i]=0;
    }
    int running = 1;//active status
    if(running) cout<< "Status: Running "<<endl;
    cout<< "type 'help' for list of commands";
    while(running){
        string cmd;
        cout<< "ATM>";
        cin>> cmd; 
        handlecommand(cmd,running,accnum,PIN,balance,count,current,history,ammount);
    }
    Record(history,ammount);
    SaveData(accnum,PIN,balance,count); // Save data at the end of the session
}


