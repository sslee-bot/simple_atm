#include "atm_controller.hpp"

#include <gtest/gtest.h>

TEST(AtmControllerTest, InsertCard) {
    AtmController atm;
    atm.insertCard(Card{"1234-5678-1234-5678"});
    EXPECT_NE(atm.getCurrentCard(), nullptr);
}
