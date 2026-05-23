#pragma once

class CashBin {
public:
    virtual ~CashBin() = default;
    virtual int getCash() = 0;
    virtual bool withdraw(int amount) = 0;
};
