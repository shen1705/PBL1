#include "atm_control.h"
#include "auth.h"
#include <iostream>


int main() {
    if(ITauth())
        runATM();
    else  std::cout<<"Authorization is failed"<<std::endl;
    std::cout<<"Shutting down now";

    return 0;
}