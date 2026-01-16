#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/*
struct User{
    unsigned int accountnumber;
    unsigned int PIN;
    double balance;
};

struct DataList{
    unsigned int total;
    struct User *a;
};

neu duoc su dung struct 
*/ 
int LoadData(int accnum[],int PIN[],int balance[]){
    ifstream ATMDATA ("DATA/user.txt");
    if(!ATMDATA){
        return -1;
    }
    string line;
    int count=0;

    while(getline(ATMDATA,line)){
        stringstream data;
        string temp;
        
        getline(data,temp,'|');//get line from data -> temp splitted by | 
        accnum[count]=stoi(temp);
        getline(data,temp,'|');
        PIN[count]=stoi(temp);
        getline(data,temp,'|');
        balance[count]=stod(temp);
        count++;
    }
    return count;
}

int SaveData(int accnum[],int PIN[],int balance[],int count){
    ofstream ATMDATA("user.txt");
    if(!ATMDATA)return -1;
    for(int i=0;i<count;i++){
        ATMDATA << accnum[i]<<"|"<<PIN[i]<<"|"<<balance[i]<<endl;
    }
    ATMDATA.close();
    return 1;
}

int Record(int history[],double ammount[]){
    ofstream record("record.txt",ios::app);
        if(!record)return -1;
        int i = 0 ;
        while(history[i]!=0){
            record << history[i]<< ":"<<ammount[i]<<"|";
            i++;
        }
    record.close();
    }
