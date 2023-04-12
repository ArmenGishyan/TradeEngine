#pragma once

#include "OrderBase.hpp"
#include "Prototypes.hpp"
#include "OrderType.hpp"

class BasicOrder : public OrderBase {
public:
	BasicOrder(TraderPtr, OrderType, size_t, size_t);

	size_t price() const override;
	Time_t dateCreated() const override;
	size_t quantity() const override;
	OrderType type() const override;

	OrderBasePtr cloneByQuantity(size_t qunatity) const override;

	TraderPtr trader() const override;

private:
	TraderPtr _traderPtr;
	OrderType _type;
	size_t _quantity;
	size_t _price;
	Time_t _timeCreated;
};