#pragma once

#include <string>
#include <memory>
#include <iostream>

struct Card {
    std::string pin;
};

class AtmController {
public:
    void insertCard(const Card& card) {
        currentCard_ = std::make_shared<Card>(card);
        std::cout << "Inserted card (PIN): " << currentCard_->pin << std::endl;
    }

private:
    std::shared_ptr<Card> currentCard_;
};
