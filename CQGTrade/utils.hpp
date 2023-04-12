#pragma once

#include <string>
#include <set>
#include <functional>

#include "Prototypes.hpp"
#include "OrderType.hpp"
#include "OrderBase.hpp"

namespace utils {
	std::vector<std::string_view> splitSV(std::string_view strv, std::string_view delims = " ");
	void addTreadToList(TradePtr trade, std::vector<TradePtr>& trades);
	
	template<class T>
	bool canMakeTrades(OrderBasePtr order, std::set<OrderBasePtr, T>& orders,
		std::function<bool(size_t, size_t)>) {

		auto quantity = order->quantity();
		auto price = order->price();

		auto iter = orders.begin();
		while (iter != orders.end()) {
			const auto& it = *iter;
			bool res = order->type() == OrderType::Buy ?
				std::less_equal<size_t>{}(it->price(), price) :
				std::greater_equal<size_t>{}(it->price(), price);

			if (res) {
				if (quantity <= it->quantity()) {
					quantity = 0; break;
				}
				quantity -= it->quantity();
			}

			iter++;
		}
		return quantity < order->quantity();
	}

template<bool less>
struct OrderCompare
{
	constexpr bool operator() (const OrderBasePtr& first, const OrderBasePtr& second) const {
		if (first->price() == second->price()) {
			return less ? std::less<Time_t>{}(first->dateCreated(), second->dateCreated())
				: std::greater<Time_t>{}(first->dateCreated(), second->dateCreated());
		}

		return less ? std::less<size_t>{}(first->price(), second->price()) : 
			std::greater<size_t>{}(first->price(), second->price());
	}
};

}