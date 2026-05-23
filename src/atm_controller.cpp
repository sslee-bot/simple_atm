#include "atm_controller.hpp"

void AtmController::insertCard(const Card& card) {
    if (!cashBin_) {
        cout << "[Error] Cash bin is not set." << endl;
        return;
    }
    card_ = std::make_shared<Card>(card);
    cout << "Inserted card number: " << card_->number << endl;
}

void AtmController::setBank(shared_ptr<Bank> bank) {
    bank_ = bank;
}

void AtmController::setCashBin(shared_ptr<CashBin> cashBin) {
    cashBin_ = cashBin;
}

bool AtmController::enterPin(const std::string& pin) {
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

std::vector<Account> AtmController::getAvailableAccounts() {
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

void AtmController::selectAccount(const Account& account) {
    if (!cashBin_) {
        cout << "[Error] Cash bin is not set." << endl;
        return;
    }
    account_ = std::make_shared<Account>(account);
    cout << "Selected account: " << account.id << endl;
}

bool AtmController::getMoney(int& money) {
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

bool AtmController::withdraw(int amount) {
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

bool AtmController::deposit(int amount) {
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

std::shared_ptr<Card> AtmController::getCard() const {
    return card_;
}

std::shared_ptr<Account> AtmController::getAccount() const {
    return account_;
}
