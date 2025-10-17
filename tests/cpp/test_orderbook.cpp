#include <gtest/gtest.h>
#include "engine/OrderBook.hpp"

using namespace eng;

TEST(OrderBook, InsertsAndBestPrices) {
    OrderBook ob;
    EXPECT_FALSE(ob.best_bid().has_value());
    EXPECT_FALSE(ob.best_ask().has_value());

    ob.add_limit(Side::Buy, 10.00, 100);
    ob.add_limit(Side::Buy, 10.05, 200);
    ob.add_limit(Side::Sell, 10.20, 150);
    ob.add_limit(Side::Sell, 10.15, 50);

    auto bb = ob.best_bid();
    auto ba = ob.best_ask();
    ASSERT_TRUE(bb.has_value());
    ASSERT_TRUE(ba.has_value());
    EXPECT_DOUBLE_EQ(bb->price, 10.05);
    EXPECT_EQ(bb->qty, 200);
    EXPECT_DOUBLE_EQ(ba->price, 10.15);
    EXPECT_EQ(ba->qty, 50);
}

TEST(OrderBook, CancelRemovesLevels) {
    OrderBook ob;
    ob.add_limit(Side::Buy, 10.00, 100);
    ob.add_limit(Side::Buy, 10.00, 50);
    auto bb = ob.best_bid();
    ASSERT_TRUE(bb.has_value());
    EXPECT_EQ(bb->qty, 150);

    ob.cancel_at_price(Side::Buy, 10.00, 150);
    EXPECT_FALSE(ob.best_bid().has_value());
}
