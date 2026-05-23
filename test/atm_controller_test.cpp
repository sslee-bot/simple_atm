#include "atm_controller.hpp"

#include <gtest/gtest.h>

using namespace std;

class TestBank: public Bank
{
public:
    vector<Account> getAccountsForCard(const Card& card) override {
        // TODO: add test accounts
        return {};
    }
    bool verifyPin(const Card& card, const std::string& pin) override {
        // TODO: add detailed verification process
        return pin == "1234";
    }
};

TEST(AtmControllerTest, InsertCard) {
    AtmController atm;
    atm.insertCard(Card{"1234-5678-1234-5678"});
    EXPECT_NE(atm.getCurrentCard(), nullptr);
}

TEST(AtmControllerTest, ValidPin) {
    AtmController atm;
    auto bank = make_shared<TestBank>();
    atm.setBank(bank);
    atm.insertCard(Card{"1234-5678-1234-5678"});
    EXPECT_TRUE(atm.enterPin("1234"));
}

TEST(AtmControllerTest, InvalidPin) {
    AtmController atm;
    auto bank = make_shared<TestBank>();
    atm.setBank(bank);
    atm.insertCard(Card{"1234-5678-1234-5678"});
    EXPECT_FALSE(atm.enterPin("4321"));
}
