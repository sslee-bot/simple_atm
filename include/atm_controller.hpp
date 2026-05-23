#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "bank.hpp"

using namespace std;

struct Card {
    std::string number;
};

class AtmController {
public:
    void insertCard(const Card& card) {
        card_ = std::make_shared<Card>(card);
        cout << "Inserted card number: " << card_->number << endl;
    }

    // NOTE: Controller may know which bank should be called.
    // Bank selection process is not implemented yet.
    void setBank(shared_ptr<Bank> bank) {
        bank_ = bank;
    }

    bool enterPin(const std::string& pin) {
        cout << "Input PIN number: " << pin << endl;
        if (!card_) {
            cout << "[Error] A card must be inserted first." << endl;
            return false;
        }
        if (!bank_) {
            cout << "[Error] Bank is not set." << endl;
            return false;
        }
        return bank_->verifyPin(*card_, pin);
    }

    std::vector<Account> getAvailableAccounts() {
        if (!card_) {
            cout << "[Error] A card must be inserted first." << endl;
            return {};
        }
        if (!bank_) {
            cout << "[Error] Bank is not set." << endl;
            return {};
        }
        return bank_->getAccountsForCard(*card_);
    }

    void selectAccount(const Account& account) {
        account_ = std::make_shared<Account>(account);
        cout << "Selected account: " << account.id << endl;
    }

    bool getMoney(int& money) {
        if (!account_)  {
            cout << "[Error] An account must be selected first." << endl;
            return false;
        }
        money = account_->money;
        return true;
    }

    std::shared_ptr<Card> getCard() const {
        return card_;
    }

    std::shared_ptr<Account> getAccount() const {
        return account_;
    }

private:
    std::shared_ptr<Card> card_ = nullptr;
    std::shared_ptr<Bank> bank_ = nullptr;
    std::shared_ptr<Account> account_ = nullptr;
};
