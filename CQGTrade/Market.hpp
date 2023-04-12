#pragma once

#include <set>
#include <functional>

#include "OrderType.hpp"
#include "Prototypes.hpp"
#include "OrderBase.hpp"
#include "Trade.hpp"

namespace {
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
			else {
				break;
			}

			iter++;
		}
		return quantity == 0;
	}
}

// Move to utility
template<bool less>
struct OrderCompare
{
	constexpr bool operator() (const OrderBasePtr& first, const OrderBasePtr& second) const {
		if (first->price() == second->price()) {
			return less ? std::less<Time_t>{}(first->dateCreated(), second->dateCreated())
				: std::greater<Time_t>{}(first->dateCreated(), second->dateCreated());
		}

		return less ? std::less<size_t>{}(first->price(), second->price()) : std::greater<size_t>{}(first->price(), second->price());
	}
};

class Market {
public:
	void placeOrder(OrderBasePtr order);

	static std::shared_ptr<Market> instance();

	std::vector<Trades> existingTrads() const;

private:
	static std::shared_ptr<Market> _instance;

	using BuyOrderContainerType = std::set<OrderBasePtr, OrderCompare<true> >;
	using SellOrderContainerType = std::set<OrderBasePtr, OrderCompare<false> >;

	// move to cpp
	template<class T>
	void processAgressor(OrderBasePtr aggresor, std::set<OrderBasePtr, T>& restingOrders) {
		if (!canMakeTrades(aggresor, restingOrders, std::less_equal<size_t>{})) {
			restingOrders.insert(aggresor);
			return;
		}

		// error in else case
		//auto compare = aggresor->type() == OrderType::Buy ? std::less_equal<size_t>{} :
		//	std::greater_equal<size_t>{};

		std::vector<std::shared_ptr<Trade>> trades;

		size_t quantity = aggresor->quantity();
		auto price = aggresor->price();

		auto iter = _restingOrdersSell.begin();
		while (iter != _restingOrdersSell.end()) {
			if (quantity == 0) break;
			const auto& it = *iter;
			bool res = aggresor->type() == OrderType::Buy ?
				std::less_equal<size_t>{}(it->price(), price) :
					std::greater_equal<size_t>{}(it->price(), price);

			if (res) {
				std::shared_ptr<Trade> trade = std::make_shared<Trade>(it->trader(),
					it->type(), it->quantity(),
					it->price());

				if (quantity < it->quantity()) {
					quantity = 0;

					_restingOrdersSell.insert(it->cloneByQuantity(it->quantity() - quantity));
				}
				else {
					quantity -= it->quantity();
				}
				iter = _restingOrdersSell.erase(iter);
				trades.push_back(trade);
			}
			else {
				++iter;
			}
		}

		if (!trades.empty())
			_tradeOfOneAggressorList.push_back(std::move(trades));
	}

private:
	SellOrderContainerType _restingOrdersSell;
	BuyOrderContainerType _restingOrdersBuy;

	std::vector<Trades> _tradeOfOneAggressorList;
};
