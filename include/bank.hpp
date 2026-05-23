#pragma once

#include <string>
#include <vector>

struct Card; // defined in atm_controller_test.hpp

struct Account {
    std::string id;
    int money;
};

class Bank {
public:
    virtual ~Bank() = default;
    virtual std::vector<Account> getAccountsForCard(const Card& card) = 0;
    virtual bool verifyPin(const Card& card, const std::string& pin) = 0;
};