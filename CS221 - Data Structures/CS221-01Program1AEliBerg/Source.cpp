#include "TwoDay.h"
#include "Overnight.h"
#include <iostream>
using namespace std;

int main() {
    // Test TwoDay shipping
    Overnight overnightPackage;
    // Set package details
    overnightPackage.SetName("Eli Berg");
    overnightPackage.SetAddress("123 Main St");
    overnightPackage.SetCostPerOz(2);
    overnightPackage.SetNumOz(4);
    overnightPackage.SetExtraPerOz(5.0f);

    // Display package information
    overnightPackage.PrintInfo();
}
