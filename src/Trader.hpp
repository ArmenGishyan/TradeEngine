#pragma once

#include <string>

class Trader {
public:
	explicit Trader(std::string ID);
	std::string ID() const;

private:
	std::string _id;
};