#include "atm_controller.hpp"

#include <gtest/gtest.h>

using namespace std;

class TestBank: public Bank
{
public:
    vector<Account> getAccountsForCard(const Card& card) override {
        // NOTE: Bank should return proper account lists.
        return {Account{"BEAR-001", 100},
                Account{"TIGER-002", 200} };
    }
    bool verifyPin(const Card& card, const std::string& pin) override {
        // NOTE: Bank should implement proper verification processes.
        return pin == "1234";
    }
    void withdraw(const Account& account, int amount) override {
        // NOTE: Bank should update its own balance records.
    }
    void deposit(const Account& account, int amount) override {
        // NOTE: Bank should update its own balance records.
    }
};

class TestCashBin: public CashBin
{
public:
    TestCashBin(int initCash): cash_(initCash)
    {
    }
    int getCash() override {
        return cash_;
    }
    bool withdraw(int amount) override {
        if (cash_ < amount){
            return false;
        }
        cash_ -= amount;
        return true;
    }
    void deposit(int amount) override {
        cash_ += amount;
    }
private:
    int cash_;
};

// test card data saving
TEST(AtmControllerTest, InsertCard) {
    AtmController atm;
    auto cashBin = make_shared<TestCashBin>(10000);
    atm.setCashBin(cashBin);
    atm.insertCard(Card{"1234-5678-1234-5678"});
    EXPECT_NE(atm.getCard(), nullptr);
}

// test PIN verification if "valid"
TEST(AtmControllerTest, ValidPin) {
    AtmController atm;
    auto cashBin = make_shared<TestCashBin>(10000);
    auto bank = make_shared<TestBank>();
    atm.setCashBin(cashBin);
    atm.setBank(bank);
    atm.insertCard(Card{"1234-5678-1234-5678"});
    EXPECT_TRUE(atm.enterPin("1234"));
}

// test PIN verification if "invalid"
TEST(AtmControllerTest, InvalidPin) {
    AtmController atm;
    auto cashBin = make_shared<TestCashBin>(10000);
    auto bank = make_shared<TestBank>();
    atm.setCashBin(cashBin);
    atm.setBank(bank);
    atm.insertCard(Card{"1234-5678-1234-5678"});
    EXPECT_FALSE(atm.enterPin("4321"));
}

// test select and get account info
TEST(AtmControllerTest, SelectAccount) {
    AtmController atm;
    auto cashBin = make_shared<TestCashBin>(10000);
    auto bank = make_shared<TestBank>();
    atm.setCashBin(cashBin);
    atm.setBank(bank);
    atm.insertCard(Card{"1234-5678-1234-5678"});

    auto accounts = atm.getAvailableAccounts();
    atm.selectAccount(accounts[0]);

    EXPECT_NE(atm.getAccount(), nullptr);
    EXPECT_EQ(atm.getAccount()->id, accounts[0].id);
    EXPECT_EQ(atm.getAccount()->money, accounts[0].money);
    int money;
    EXPECT_EQ(atm.getMoney(money), true);
    EXPECT_EQ(money, accounts[0].money);
}

// test withdraw
// TODO: low cash case
TEST(AtmControllerTest, Withdraw) {
    AtmController atm;
    auto bank = make_shared<TestBank>();
    auto cashBin = make_shared<TestCashBin>(10000);
    atm.setBank(bank);
    atm.setCashBin(cashBin);
    atm.insertCard(Card{"1234-5678-1234-5678"});

    auto accounts = atm.getAvailableAccounts();
    atm.selectAccount(accounts[0]);

    int amount = 30; // to withdraw
    int initMoney;
    atm.getMoney(initMoney);            // money in system
    int initCash = cashBin->getCash();  // money in real

    EXPECT_TRUE(atm.withdraw(amount));
    int postMoney;
    atm.getMoney(postMoney);
    EXPECT_EQ(postMoney, initMoney - amount);
    EXPECT_EQ(cashBin->getCash(), initCash - amount);
}

// test deposit
TEST(AtmControllerTest, Deposit) {
    AtmController atm;
    auto bank = make_shared<TestBank>();
    auto cashBin = make_shared<TestCashBin>(10000);
    atm.setBank(bank);
    atm.setCashBin(cashBin);
    atm.insertCard(Card{"1234-5678-1234-5678"});

    auto accounts = atm.getAvailableAccounts();
    atm.selectAccount(accounts[0]);

    int amount = 30;  // to deposit
    int initMoney;
    atm.getMoney(initMoney);
    int initCash = cashBin->getCash();

    EXPECT_TRUE(atm.deposit(amount));
    int postMoney;
    atm.getMoney(postMoney);
    EXPECT_EQ(postMoney, initMoney + amount);
    EXPECT_EQ(cashBin->getCash(), initCash + amount);
}
