#include "Trader.hpp"

Trader::Trader(std::string ID):_id(ID)
{
}

std::string Trader::ID() const
{
	return _id;
}
