#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class CsMain {
    public:
        CsMain();
        /** Call this to start the sim */
        void init();
        
    private: 
        void drawCsTextPlot(OrderBookType orderBookType, std::string product);
        int getUserOption();

	OrderBook orderBook{"20200601.csv"};
};
