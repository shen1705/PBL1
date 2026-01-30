#include "auth.h"
#include <string>
#include <iostream>
#include <limits>
using namespace std;




int ITauth() {
    const string system_password = "12345";
    string password = "";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "IT authentication required" << endl;
    cout << "Enter IT password: ";
    
    getline(cin, password);

    if (password == system_password) {
        cout << "Access Granted." << endl;
        return 1; 
    } else {
        cout << "Access Denied." << endl;
        return 0; 
    }
}



int Userauth(int pin){
    int PIN;
    cout<< "Enter PIN:";
    cin>>PIN;
    cin.ignore(1000, '\n');
    return PIN==pin;

}