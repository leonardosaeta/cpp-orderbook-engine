#include "engine/OrderBook.hpp"

namespace eng {

void OrderBook::add_limit(Side side, double price, std::int64_t qty) {
    if (side == Side::Buy) {
        auto it = bids_.find(price);
        if (it == bids_.end()) {
            bids_.emplace(price, qty);
        } else {
            it->second += qty;
        }
    } else {
        auto it = asks_.find(price);
        if (it == asks_.end()) {
            asks_.emplace(price, qty);
        } else {
            it->second += qty;
        }
    }
}

void OrderBook::cancel_at_price(Side side, double price, std::int64_t qty) {
    if (side == Side::Buy) {
        auto it = bids_.find(price);
        if (it == bids_.end()) return;
        if (qty >= it->second) {
            bids_.erase(it);
        } else {
            it->second -= qty;
        }
    } else {
        auto it = asks_.find(price);
        if (it == asks_.end()) return;
        if (qty >= it->second) {
            asks_.erase(it);
        } else {
            it->second -= qty;
        }
    }
}

std::optional<Level> OrderBook::best_bid() const {
    if (bids_.empty()) return std::nullopt;
    auto it = bids_.begin();
    return Level{it->first, it->second};
}

std::optional<Level> OrderBook::best_ask() const {
    if (asks_.empty()) return std::nullopt;
    auto it = asks_.begin();
    return Level{it->first, it->second};
}

}


