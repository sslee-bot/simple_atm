#pragma once

#include <string>
#include <memory>
#include <iostream>

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

    bool enterPin(const std::string& pin) {
        if (!currentCard_) {
            cout << "[Error] A card must be inserted first." << endl;
            return false;
        }
        cout << "Input PIN number: " << pin << endl;
        // TODO: load account info from bank
        return true;
    }

private:
    std::shared_ptr<Card> currentCard_;
};
