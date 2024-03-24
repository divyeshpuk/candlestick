#pragma once

#include <string>
#include "OrderBookEntry.h"
#include "Candlestick.h"
#include <vector>

/**
  vertical: plot with multiple candlesticks positioned vertical (x = time, y = price)
  horizontal: plot with multiple candlesticks positioned horizontal (x = price, y = time)
  */
enum class CsPlotType { vertical, horizontal };

struct plotConfig {           
    CsPlotType type;
    int tail;
    int divs;
    int subDivs;
};

class CsTextPlot {
    public:
        CsTextPlot();     
        void drawCsTextPlot(std::vector<OrderBookEntry>& orderBookEntries, plotConfig& config);

    private:
        void drawVerticalPlot(std::vector<OrderBookEntry>& orderBookEntries, plotConfig& config);
        void drawHorizontalPlot(std::vector<OrderBookEntry>& orderBookEntries, plotConfig& config);
};