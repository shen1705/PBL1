#include "Application\includes\\atm_controll.h"
#include "Application\includes\auth.h"
#include <iostream>


int main() {
    if(ITauth)
        runATM();
    else  std::cout<<"Authorization is failed"<<std::endl;
    return 0;
}