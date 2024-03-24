#pragma once

#include <string>
#include "OrderBookEntry.h"
#include "Candlestick.h"
#include <vector>

class CsPlot {
    public:
        CsPlot();     

        double getHigh() {
            return high;
        }

        double getLow() {
            return low;
        }

        std::vector<Candlestick>& getCandlesticks() {
            return candlesticks;
        }

        Candlestick& getCandlestick(int index) {
            return candlesticks[index];
        }

        void setProduct(std::string p) {
            product = p;
        }

        std::string getProduct() {
            return product;
        }

        void setOrderType(OrderBookType o) {
            orderType = o;
        }

        OrderBookType getOrderType() {
            return orderType;
        }

        void setCsPlot(std::vector<OrderBookEntry>& orderBookEntries);

    private:
        std::vector<Candlestick> candlesticks;
        double high;
        double low;
        std::string product;
        OrderBookType orderType;

        void setHigh(double n) {
            high = n;
        }

        void setLow(double n) {
            low = n;
        }
};
