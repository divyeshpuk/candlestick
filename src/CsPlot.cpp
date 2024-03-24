#include "Candlestick.h"
#include "CsPlot.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>

CsPlot::CsPlot() {
}

void CsPlot::setCsPlot(std::vector<OrderBookEntry>& orderBookEntries) {
    // instantiate values
    double totalValue = 0;
    double totalAmount = 0;

    for (OrderBookEntry const& orderBookEntry : orderBookEntries) {
        // first item of the timeframe
        if (candlesticks.size() == 0) {
            // set values
            totalValue = orderBookEntry.price * orderBookEntry.amount;
            totalAmount = orderBookEntry.amount;

            // instantiate values of class properties
            setProduct(orderBookEntry.product);
            setOrderType(orderBookEntry.orderType);
            setHigh(orderBookEntry.price);
            setLow(orderBookEntry.price);

            // instantiate the first candlestick
            Candlestick candlestick {
                getHigh(), // init high with first value
                getLow(), // init low with first value
                0, // init close with default zero
                0, // open with default zero
                orderBookEntry.timestamp
            };
            candlesticks.push_back(candlestick);
        } else {
            int lastIndex = candlesticks.size() - 1;
            Candlestick& lastCandlestick = getCandlestick(lastIndex);

            double h = (orderBookEntry.price > getHigh()) ? orderBookEntry.price : getHigh();
            double l = (orderBookEntry.price < getLow()) ? orderBookEntry.price : getLow();

            setHigh(h);
            setLow(l);

            if (lastCandlestick.getTimestamp() == orderBookEntry.timestamp) {
                // in the same timeframe
                // update values
                double high = (orderBookEntry.price > lastCandlestick.getHigh()) ? orderBookEntry.price : lastCandlestick.getHigh();
                lastCandlestick.setHigh(high);
                double low = (orderBookEntry.price < lastCandlestick.getLow()) ? orderBookEntry.price : lastCandlestick.getLow();
                lastCandlestick.setLow(low);
                double currentValue = orderBookEntry.price * orderBookEntry.amount;
                totalValue = totalValue + currentValue;
                totalAmount = totalAmount + orderBookEntry.amount;
                double close = totalValue / totalAmount;
                lastCandlestick.setClose(close);
            } else {
                // in the next timeframe
                // reset values
                totalValue = orderBookEntry.price * orderBookEntry.amount;
                totalAmount = orderBookEntry.amount;

                // instantiate the next candlestick
                Candlestick candlestick {
                    orderBookEntry.price, // init high with first value
                    orderBookEntry.price, // init low with first value
                    0, // init close with default zero
                    lastCandlestick.getClose(), // open with the average price per unit in the previous timeframe
                    orderBookEntry.timestamp
                };
                candlesticks.push_back(candlestick);
            }
        }
    }
}
