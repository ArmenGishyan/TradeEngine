#include "Market.hpp"

#include <set>
#include <memory>
#include <vector>
#include <functional>

#include "Prototypes.hpp"
#include "OrderBase.hpp"

std::shared_ptr<Market> Market::_instance = nullptr;

void Market::placeOrder(OrderBasePtr aggressor) {
	if (aggressor->type() == OrderType::Sell) {
		// make sell case
		processAgressor<OrderCompare<true>>(aggressor, _restingOrdersBuy);

	}
	else if (aggressor->type() == OrderType::Buy) {
		// buy 
		processAgressor<OrderCompare<false>>(aggressor, _restingOrdersSell);
	}
}

std::shared_ptr<Market> Market::instance() {
	if (!_instance)
		_instance = std::make_shared<Market>();

	return _instance;
}

std::vector<Trades> Market::existingTrads() const {
	return _tradeOfOneAggressorList;
}


