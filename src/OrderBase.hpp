#pragma once

#include "Prototypes.hpp"
#include "OrderType.hpp"

class OrderBase {
public:
	virtual ~OrderBase() = default;
	virtual size_t price() const = 0;
	virtual Time_t dateCreated() const = 0;
	virtual size_t quantity() const = 0;
	virtual OrderType type() const = 0;
	virtual OrderBasePtr cloneByQuantity(size_t qunatity) const = 0;
	virtual TraderPtr trader() const = 0;
};