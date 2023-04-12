#pragma once

#include "OrderType.hpp"
#include "OrderBase.hpp"
#include "Trade.hpp"
#include "Trader.hpp"
#include "utils.hpp"

class Market {
public:
	void placeOrder(OrderBasePtr order);

	static std::shared_ptr<Market> instance();

	std::vector<Trades> existingTrads() const;

private:
	//Market() = default;

	static std::shared_ptr<Market> _instance;

	using BuyOrderContainerType = std::set<OrderBasePtr, utils::OrderCompare<false> >;
	using SellOrderContainerType = std::set<OrderBasePtr, utils::OrderCompare<true> >;

	template<class T>
	void processAggressor(OrderBasePtr aggressor, std::set<OrderBasePtr, T>& restingOrders) {
		if (!utils::canMakeTrades(aggressor, restingOrders, std::less_equal<size_t>{})) {
			if (aggressor->type() == OrderType::Buy) {
				_restingOrdersBuy.insert(aggressor);
			}
			else if (aggressor->type() == OrderType::Sell) {
				_restingOrdersSell.insert(aggressor);
			}
			return;
		}

		std::vector<TradePtr> trades;

		auto quantity = aggressor->quantity();
		const auto price = aggressor->price();

		auto iter = restingOrders.begin();
		std::shared_ptr<OrderBase> missingOrder;

		while (iter != restingOrders.end()) {
			if (quantity == 0) break;
			const auto& it = *iter;
			bool res = aggressor->type() == OrderType::Buy ?
				std::less_equal<size_t>{}(it->price(), price) :
					std::greater_equal<size_t>{}(it->price(), price);

			if (res) {
				std::shared_ptr<Trade> trade;
				std::shared_ptr<Trade> oppositeTrade;

				if (quantity < it->quantity()) {
					trade = std::make_shared<Trade>(it->trader(),
						it->type(), quantity,
						it->price());

					oppositeTrade = std::make_shared<Trade>(aggressor->trader(),
						aggressor->type(), quantity,
						it->price());

					missingOrder = it->cloneByQuantity(it->quantity() - quantity);

					quantity = 0;
				}
				else {
					trade = std::make_shared<Trade>(it->trader(),
						it->type(), it->quantity(),
						it->price());

					oppositeTrade = std::make_shared<Trade>(aggressor->trader(),
						aggressor->type(), it->quantity(),
						it->price());

					if (auto newQuantity = aggressor->quantity() - it->quantity(); newQuantity) {
						missingOrder = aggressor->cloneByQuantity(aggressor->quantity() - it->quantity());
					}
					quantity -= it->quantity();

					aggressor = aggressor->cloneByQuantity(quantity);
				}

				iter = restingOrders.erase(iter);

				utils::addTreadToList(trade, trades);
				utils::addTreadToList(oppositeTrade, trades);
			}
			else {
				++iter;
			}
		}

		if (missingOrder) {
			if (missingOrder->type() == OrderType::Buy) {
				_restingOrdersBuy.insert(missingOrder);
			}
			else if (missingOrder->type() == OrderType::Sell) {
				_restingOrdersSell.insert(missingOrder);
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
