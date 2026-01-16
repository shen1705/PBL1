#include "Application/includes/handlecommand.h"
#include "Application/includes/auth.h"
#include <iostream>
#include <string>
using namespace std;


void commandlist(){
    cout<<  "  deposit   - Deposit money"<<endl
        <<"  withdraw  - Withdraw money"<<endl
        <<"  balance   - Show balance"<<endl
        <<"  history   - Show transactions"<<endl
        <<"  help      - Show this list"<<endl
        <<"  shutdown  - Shutdown ATM"<<endl;
}

void handlecommand(const std::string &cmd,int &running,int accnum[],int PIN[],double balance[],int count,int current[],int history[],double ammount[]){
   
    if(cmd == "help")
            commandlist();
    else if (cmd=="deposit"||cmd=="withdraw"||cmd=="balance"||cmd=="history"){
        int accountnumber;
        cout<<"Please input your account number:";
        if (!(cin >> accountnumber)){//input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();            
            cin.ignore(1000, '\n'); 
            return;              
        }
        int index;
        if(search(accountnumber,accnum,count,index)){
            if(Userauth(PIN[index])){
                if (cmd == "deposit") transaction(index,balance,current,history,ammount,deposit,accnum);
                else if (cmd == "withdraw") transaction(index,balance,current,history,ammount,withdraw,accnum);
                else if (cmd == "balance") ShowBalance(index,balance);
                else if (cmd == "history")ShowHistory(index,history,ammount,accnum);
    
            }
        }
        else cout<<"Can not find your account"<<endl;
    }    
    else if (cmd == "shutdown"){
        if(ITauth())shutdown(running);
        else cout<<"Authorization is failed"<<std::endl;
    }
    else cout << "Unknown command. Type 'help'."<<endl;
}

void shutdown(int &running){
    cout<<"shutting down"<<endl;
    running = 0;
}

int search(int id,int accnum[],int count,int &index){
    for(int i=0; i<count;i++){
        if(id==accnum[i]){
            index=i;
            return 1;
        }
    }
    return 0;
}

void ShowBalance(int index,double balance[]){   
    cout<< "Your balance:"<<balance[index]<<endl;
}

int withdraw(int index,double money,double balance[]){
    if(balance[index]>money){
        balance[index]-=money;
        cout<<"withdraw successfully. Your new balance:"<<balance[index]<<endl;
        return 1;
    }
    else{
        cout<<"Invalid.You dont have enough money to withdraw" <<endl;
        return 0;
    }
}

int deposit(int index,double money,double balance[]){
    balance[index]+=money;
    cout<<"deposit successfully. Your new balance:"<<balance[index]<<endl;
    return 1;
}

void transaction(int index,double balance[],int current[],int history[],double ammount[],int (*type)(int,double,double*),int accnum[]){
    if(current[index]!=0){
        double money;
        cout<<"Your balance: "<< balance[index]<<endl;
        cout<<"Type ammount of money you want to withdraw/deposit:";
        if (!(cin >> money)) {//input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();            
            cin.ignore(1000, '\n');
            return;                 
        }
        int success = type(index, money, balance);
        
        if(success) {
            if (type == withdraw){
                record(index, history, ammount, accnum, -money);
            } 
            else{
                record(index, history, ammount, accnum, money);
            }
        current[index]--;}
    }
    else cout<<"Transaction limit reached"<<endl;
}

void record(int index ,int history[] ,double ammount[],int accnum[],double money){
    int i =0;
    while(history[i]!=0){
        i++;
    }
    history[i]=accnum[index];
    ammount[i]=money;
}

void ShowHistory(int index, int history[], double ammount[],int accnum[]){
    int i =0;
    int j =0;
    cout<<"Your transaction history:"<<endl;
    while( history[i]!=0){
        if(history[i]==accnum[index]){
            cout<<++j<<"." <<ammount[i]<<endl;
            i++;
        }
    }
}