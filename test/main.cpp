#include <iostream>
#include "xpatche.h"

int main()
{
    using namespace std;
    cout << "Compatibility: "<<xpCheckCompatibility("0.0.15","64") <<endl;
    cout << xpRegisterPlugin("../testplugin/main.lua") << endl;
    xpEvent("initial_window.load");
    xpEvent("initial_window.load");
}