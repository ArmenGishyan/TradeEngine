# CMakeList.txt : CMake project for TradeEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 20)

# Add source to this project's executable.
add_executable (TradeEngine "main.cpp" "MakeOrderCommand.cpp" "App.cpp" "Market.cpp" "CommandEngine.cpp" "Trader.cpp" "Trade.cpp" "BasicOrder.cpp" "utills.cpp" "PrintTrades.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TradeEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
