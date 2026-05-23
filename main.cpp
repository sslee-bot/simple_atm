#include <iostream>
#include "atm_controller.hpp"

int main(int argc, char** argv) {
    // ATM
    AtmController atm;
    atm.insertCard(Card{"1234-5678-1234-5678"});
    atm.enterPin("1234");

    return 0;
}
