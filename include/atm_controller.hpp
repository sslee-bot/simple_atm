#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "bank.hpp"
#include "cash_bin.hpp"

using namespace std;

struct Card {
    std::string number;
};

class AtmController {
public:
    void insertCard(const Card& card) {
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return;
        }
        card_ = std::make_shared<Card>(card);
        cout << "Inserted card number: " << card_->number << endl;
    }

    // NOTE: Controller may know which bank should be called.
    // Bank selection process is not implemented yet.
    void setBank(shared_ptr<Bank> bank) {
        bank_ = bank;
    }

    void setCashBin(shared_ptr<CashBin> cashBin) {
        cashBin_ = cashBin;
    }

    bool enterPin(const std::string& pin) {
        cout << "Input PIN number: " << pin << endl;
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return false;
        }
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
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return {};
        }
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
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return;
        }
        account_ = std::make_shared<Account>(account);
        cout << "Selected account: " << account.id << endl;
    }

    bool getMoney(int& money) {
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return false;
        }
        if (!account_)  {
            cout << "[Error] An account must be selected first." << endl;
            return false;
        }
        money = account_->money;
        return true;
    }

    bool withdraw(int amount) {
        cout << "Withdraw amount: " << amount << endl;
        // check conditions
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return false;
        }
        if (!account_) {
            cout << "[Error] An account must be selected first." << endl;
            return false;
        }
        if (!bank_) {
            cout << "[Error] Bank is not set." << endl;
            return false;
        }
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return false;
        }

        // check money, withdraw from cash bin
        if (account_->money < amount) {
            cout << "[Error] low account balance." << endl;
            return false;
        }
        if (cashBin_->getCash() < amount) {
            cout << "[Error] low cash in ATM." << endl;
            return false;
        }
        if (!cashBin_->withdraw(amount)) {
            cout << "[Error] Cash bin failed to work (withdraw)." << endl;
            return false;
        }
        
        // success case
        account_->money -= amount;
        bank_->withdraw(*account_, amount);
        return true;
    }

    bool deposit(int amount) {
        cout << "Deposit amount: " << amount << endl;
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return false;
        }
        if (!account_) {
            cout << "[Error] An account must be selected first." << endl;
            return false;
        }
        if (!bank_) {
            cout << "[Error] Bank is not set." << endl;
            return false;
        }
        if (!cashBin_) {
            cout << "[Error] Cash bin is not set." << endl;
            return false;
        }
        
        cashBin_->deposit(amount);
        account_->money += amount;
        bank_->deposit(*account_, amount);
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
    std::shared_ptr<CashBin> cashBin_ = nullptr;
};
