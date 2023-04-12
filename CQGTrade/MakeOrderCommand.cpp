#include "MakeOrderCommand.hpp"
#include "BasicOrder.hpp"
#include "Market.hpp"
#include "utils.hpp"
#include "Trader.hpp"

std::string MakeOrderCommand::name() const
{
    return "add_trade";
}

bool MakeOrderCommand::execute()
{
    Market::instance()->placeOrder(
        std::make_shared<BasicOrder>(_trader, _type, _quantity, _price));

    return true;
}

bool MakeOrderCommand::parseArgs(std::string_view command)
{
    std::vector<std::string_view> argsList = splitSV(command);

    if (argsList.size() < 4) return false;
    _trader = std::make_shared<Trader>(std::string(argsList[0]));
    _type = argsList[1] == "B" ? OrderType::Buy : OrderType::Sell;
    _quantity = std::stoul(std::string(argsList[2]));
    _price = std::stoul(std::string(argsList[3]));

    return true;
}
