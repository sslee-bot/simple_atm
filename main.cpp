#include <iostream>
#include "atm_controller.hpp"

int main(int argc, char** argv) {
    // ATM
    AtmController atm;
    atm.insertCard(Card{"123456"});

    return 0;
}
