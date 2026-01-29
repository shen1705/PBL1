#include "atm_control.h"
#include "handlecommand.h"
#include "datahandler.h"
#include <string>
#include <iostream>


using namespace std;


void runATM(){
    //data prepare
    int count = UserCount();
    int accnum[count];
    int PIN[count];
    double balance[count]; 
    int maxtrans[count];//transaction limit 
    double ammount[count];//transaction ammount history
    int history[count];//acc num ammount history
    if(!LoadData(accnum,PIN,balance))cout<<"cant load data from files";//load data + return count at the start of the session
    for(int i = 0;i<count;i++){
        maxtrans[i]=5;
        history[i]=0;
        ammount[i]=0;
    }
    int running = 1;//active status
    system("cls");//clearscreen
    if(running) cout<< "Status: Running "<<endl;
    cout<<"=================================="<<endl;
    cout<< "type 'help' for list of commands"<<endl;
    while(running){
        string cmd;
        cout<< "ATM>";
        cin>> cmd; 
        handlecommand(cmd,running,accnum,PIN,balance,count,maxtrans,history,ammount);
    }
    Record(history,ammount);
    SaveData(accnum,PIN,balance,count); // Save data at the end of the session
}


