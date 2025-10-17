#pragma once
#include <map>
#include <cstdint>
#include <optional>

namespace eng{

    enum class Side { Buy, Sell };


    struct Level {
        double price{};
        std::int64_t qty{};
    };


    class OrderBook{
    public:
        void add_limit(Side side, double price, std::int64_t qty);
        void cancel_at_price(Side side, double price, std::int64_t qty);

        std::optional<Level> best_bid() const;
        std::optional<Level> best_ask() const;

        std::size_t bid_levels() const {return bids_.size();}
        std::size_t ask_levels() const {return asks_.size();}


    private:
        struct Desc {bool operator()(double a, double b) const {return a > b;}};

        std::map<double, std::int64_t, Desc> bids_;
        std::map<double, std::int64_t>       asks_;
    };
}