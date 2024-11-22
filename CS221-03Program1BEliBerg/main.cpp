#include "TwoDay.h"
#include "Overnight.h"
#include <iostream>
using namespace std;

int main() {
    // Test TwoDay shipping
    TwoDay Package;
    // Set package details
    Package.SetAddress("123 Nowhere lane");
    Package.SetName("Eli");
    Package.SetNumOz(6);
    Package.PrintInfo();
    
    

  
}
