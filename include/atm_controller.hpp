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
        currentCard_ = std::make_shared<Card>(card);
        cout << "Inserted card number: " << currentCard_->number << endl;
    }

    // NOTE: Controller may know which bank should be called.
    // Bank selection process is not implemented yet.
    void setBank(shared_ptr<Bank> bank) {
        bank_ = bank;
    }

    bool enterPin(const std::string& pin) {
        cout << "Input PIN number: " << pin << endl;
        if (!currentCard_) {
            cout << "[Error] A card must be inserted first." << endl;
            return false;
        }
        if (!bank_) {
            cout << "[Error] Bank is not set." << endl;
            return false;
        }
        return bank_->verifyPin(*currentCard_, pin);
    }

    std::shared_ptr<Card> getCurrentCard() const {
        return currentCard_;
    }

private:
    std::shared_ptr<Card> currentCard_ = nullptr;
    std::shared_ptr<Bank> bank_ = nullptr;
};
