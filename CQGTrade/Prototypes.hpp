#pragma once

#include <memory>
#include <chrono>

class Trade;

class Trader;
using TraderPtr = std::shared_ptr<Trader>;

class OrderBase;
using OrderBasePtr = std::shared_ptr<OrderBase>;

// move to namespace
using Time_t = std::chrono::time_point<std::chrono::system_clock>;

class CommandBase;
using CommandBasePtr = std::shared_ptr<CommandBase>;

using Trades = std::vector<std::shared_ptr<Trade>>;

class CommandEngine;
