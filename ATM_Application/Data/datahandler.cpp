#include "User.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

int LoadData(unordered_map<int,User>& accounts){
    ifstream ATMDATA ("DATA/user.txt");
    if(!ATMDATA){
        return 0;
    }
    string line;

    while(getline(ATMDATA,line)){
        stringstream data(line);
        string temp;
        User U;
        U.maxtrans=5;


        getline(data,temp,'|');
        U.accnum=stoi(temp);

        getline(data,temp,'|');
        U.PIN=stoi(temp);
        
        getline(data,temp,'|');
        U.balance=stod(temp);
        
        accounts[U.accnum]=U;
    }
    return 1;
}

void SaveData(unordered_map<int,User>& accounts){
    ofstream ATMDATA("DATA/user.txt", ios::out | ios::trunc);    
    if(!ATMDATA)return;
    for(const auto& pair: accounts){
        const User& u = pair.second;

        ATMDATA << u.accnum << "|"<<u.PIN << "|"<< u.balance << "\n";
    }
    ATMDATA.close();
}

int Record(int history[],double ammount[]){
    ofstream record("DATA/record.txt",ios::app);
        if(!record)return -1;
        int i = 0 ;
        while(history[i]!=0){
            record << history[i]<< ":"<<ammount[i]<<"|";
            i++;
        }
    record.close();
    return 1;
}
