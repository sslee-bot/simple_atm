#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>

#include "bank.hpp"
#include "cash_bin.hpp"

using namespace std;

struct Card {
    std::string number;
};

class AtmController {
public:
    void insertCard(const Card& card);
    // NOTE: Controller may know which bank should be called.
    // Bank selection process is not implemented yet.
    void setBank(shared_ptr<Bank> bank);
    void setCashBin(shared_ptr<CashBin> cashBin);
    bool enterPin(const std::string& pin);
    std::vector<Account> getAvailableAccounts();
    void selectAccount(const Account& account);
    bool getMoney(int& money);
    bool withdraw(int amount);
    bool deposit(int amount);
    std::shared_ptr<Card> getCard() const;
    std::shared_ptr<Account> getAccount() const;

private:
    std::shared_ptr<Card> card_ = nullptr;
    std::shared_ptr<Bank> bank_ = nullptr;
    std::shared_ptr<Account> account_ = nullptr;
    std::shared_ptr<CashBin> cashBin_ = nullptr;
};
