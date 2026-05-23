#include <iostream>
#include "atm_controller.hpp"

using namespace std;

class DemoBank: public Bank
{
public:
    vector<Account> getAccountsForCard(const Card&) override {
        return {{"BEAR-001", 100}, {"TIGER-002", 200}};
    }
    bool verifyPin(const Card&, const string& pin) override { return pin == "1234"; }
    void withdraw(const Account&, int) override {}
    void deposit(const Account&, int) override {}
};

class DemoCashBin: public CashBin
{
public:
    DemoCashBin(int initial) : cash_(initial) {}
    int getCash() override { return cash_; }
    bool withdraw(int amount) override {
        if (cash_ < amount) return false;
        cash_ -= amount;
        return true;
    }
    void deposit(int amount) override { cash_ += amount; }
private:
    int cash_;
};

int main(int argc, char** argv) {
    const string CARD_NUMBER = "1234-5678-1234-5678";
    const string PIN = "1234";
    const int INITIAL_CASH = 10000;
    const int WITHDRAW_AMOUNT = 30;
    const int DEPOSIT_AMOUNT = 50;

    // 1. ATM steup
    cout << "=== ATM Setup ===" << endl;
    AtmController atm;
    auto bank = make_shared<DemoBank>();
    auto cashBin = make_shared<DemoCashBin>(INITIAL_CASH);
    atm.setBank(bank);
    atm.setCashBin(cashBin);
    cout << "Cash in ATM: " << cashBin->getCash() << endl;

    // 2. Card insertion
    cout << "\n=== Card Insertion ===" << endl;
    atm.insertCard(Card{CARD_NUMBER});
    atm.enterPin(PIN);
    auto accounts = atm.getAvailableAccounts();
    atm.selectAccount(accounts[0]);

    // 3. Do Task
    cout << "\n=== Do Task ===" << endl;
    atm.withdraw(WITHDRAW_AMOUNT);
    atm.deposit(DEPOSIT_AMOUNT);

    // 4. Final
    cout << "\n=== Final ===" << endl;
    int money;
    atm.getMoney(money);
    cout << "Account balance: " << money << endl;
    cout << "Cash in ATM: " << cashBin->getCash() << endl;

    return 0;
}
