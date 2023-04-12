#pragma once

#include <vector>
#include <string>

#include <algorithm>
#include "Trade.hpp"
#include "Trader.hpp"
#include "utils.hpp"

namespace utils {
    std::vector<std::string_view> splitSV(std::string_view strv, std::string_view delims)
    {
        std::vector<std::string_view> output;
        size_t first = 0;

        while (first < strv.size())
        {
            const auto second = strv.find_first_of(delims, first);

            if (first != second)
                output.emplace_back(strv.substr(first, second - first));

            if (second == std::string_view::npos)
                break;

            first = second + 1;
        }

        return output;
    }

    void addTreadToList(std::shared_ptr<Trade> trade, std::vector<std::shared_ptr<Trade>>& trades) {
        auto it = std::find_if(std::begin(trades), std::end(trades), [trade](std::shared_ptr<Trade> t) {
            return t->trader()->ID() == trade->trader()->ID() && t->type() == trade->type() &&
                t->price() == trade->price();
            });

        if (it != trades.end()) {
            auto newTrade = std::make_shared<Trade>(trade->trader(), trade->type(),
                trade->quantity() + (*it)->quantity(), trade->price());
            trades.erase(it);
            trades.push_back(newTrade);
        }
        else {
            trades.push_back(trade);
        }
    }

} // namespace utils