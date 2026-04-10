#include "atm_control.h"

int main() 
{
    if (!SystemStart()) {
        return 1;
    }
    while (IsSystemRunning()) 
    { 
        if (SystemLogin()) 
        {
            RunUserSession(); 
            SystemLogout(); 
        }
    }
    SystemShutdown(); 
    
    return 0;
}