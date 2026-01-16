#include "Application/includes/auth.h"
#include <string>
#include <iostream>
using namespace std;





int ITauth(){
    const string system_password = "12345";
    string password;
    cout<< "Enter IT password:";
    cin>> password;
    cin.ignore(1000, '\n');//clear buffer de khong bi loi (enter van con trong lenh)
    return password == system_password;
    
}


int Userauth(int pin){
    int PIN;
    cout<< "Enter PIN:";
    cin>>PIN;
    cin.ignore(1000, '\n');
    return PIN==pin;

}