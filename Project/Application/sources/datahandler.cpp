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
int UserCount(){
    ifstream DATA("DATA/User.txt");
    if(!DATA)return -1;
    int count=0;
    string line;
    while(getline(DATA,line))
        count++;
    return count;
}
int LoadData(int accnum[],int PIN[],double balance[]){
    ifstream ATMDATA ("DATA/user.txt");
    if(!ATMDATA){
        return 0;
    }
    string line;
    int count=0;

    while(getline(ATMDATA,line)){
        stringstream data(line);
        string temp;
        
        getline(data,temp,'|');//get line from data -> temp splitted by | 
        accnum[count]=stoi(temp);
        getline(data,temp,'|');
        PIN[count]=stoi(temp);
        getline(data,temp,'|');
        balance[count]=stod(temp);
        count++;
    }
    return 1;
}

int SaveData(int accnum[],int PIN[],double balance[],int count){
    ofstream ATMDATA("DATA/user.txt");
    if(!ATMDATA)return -1;
    for(int i=0;i<count;i++){
        ATMDATA << accnum[i]<<"|"<<PIN[i]<<"|"<<balance[i]<<endl;
    }
    ATMDATA.close();
    return 1;
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
