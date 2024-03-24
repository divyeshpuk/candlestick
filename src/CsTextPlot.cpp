#include "Candlestick.h"
#include "CsPlot.h"
#include "CsTextPlot.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>

CsTextPlot::CsTextPlot() {
}

void CsTextPlot::drawCsTextPlot(std::vector<OrderBookEntry>& orderBookEntries, plotConfig& config) {
    if (config.type == CsPlotType::vertical) {
        drawVerticalPlot(orderBookEntries, config);
    } else if (config.type == CsPlotType::horizontal) {
        drawHorizontalPlot(orderBookEntries, config);
    } else {
        // ignore
    }
}

void CsTextPlot::drawVerticalPlot(std::vector<OrderBookEntry>& orderBookEntries, plotConfig& config) {
    CsPlot csPlot;
    csPlot.setCsPlot(orderBookEntries);
    
    // highest and lowest values of candlestick plot data
    double pHigh = csPlot.getHigh();
    double pLow = csPlot.getLow();

    // division decrement value
    // 2 is substracted as we add an extra division at the top and the bottom of the plot,
    // so the plot has exact divisions as config.divs on y-axis (and minimum 3 divisions as default)
    int divs = (config.divs < 3) ? 3 : config.divs;
    double dec = (pHigh - pLow) / (divs - 2);

    // minimum 2 sub-divisions by default
    int subDivs = (config.subDivs < 2) ? 2 : config.subDivs;
    // sub-division decrement value
    double subDec = (dec / subDivs);
    // each point on y-axis
    double pt = 0;

    // get the reference of candlesticks
    std::vector<Candlestick>& candlesticks = csPlot.getCandlesticks();
    int csLen = candlesticks.size();
    int startIndex = csLen - config.tail;

    // plot header
    std::cout << "" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "Product: " <<  csPlot.getProduct() << std::endl;
    std::cout << "OrderType: " << OrderBookEntry::orderBookTypeToString(csPlot.getOrderType()) << std::endl;
    std::cout << csPlot.getCandlestick(0).getDate() << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "" << std::endl;

    // y-axis
    for (double j = pHigh + dec; j >= pLow - subDec; j = j - dec) {
        // init pt with the highest point on y-axis
        pt = j;
        
        for (int k = 0; k < subDivs; ++k) {
            double curPt = (k == 0) ? pt : pt - (subDec * k); 
            double nxtPt = curPt - subDec;

            for (int i = startIndex; i < csLen; ++i) {
                double cHigh = csPlot.getCandlestick(i).getHigh();
                double cLow = csPlot.getCandlestick(i).getLow();
                double close = csPlot.getCandlestick(i).getClose();
                double open = csPlot.getCandlestick(i).getOpen();
                double bg = close > open ? close : open;
                double sm = close > open ? open : close;
                // if close is greater than or equal to open then use — sign, else = sign
                std::string boxLid = (close >= open) ? "—" : "=";

                // check the range between the current point (including) and the next point (not including)
                if (cHigh <= curPt && cHigh > nxtPt) {
                    std::cout << "        | ";
                } else if (cLow <= curPt && cLow > nxtPt) {
                    std::cout << "        | ";
                } else if (open <= curPt && open > nxtPt && close <= curPt && close > nxtPt) {
                    std::cout << "       |" << boxLid << "|";
                } else if (open <= curPt && open > nxtPt) {
                    std::cout << "       |" << boxLid << "|";
                } else if (close <= curPt && close > nxtPt) {
                    std::cout << "       |—|";
                } else if (curPt <= bg && curPt >= sm) {       
                    std::cout << "       | |";
                } else if (curPt <= cHigh && curPt >= cLow) {
                    std::cout << "        | ";
                } else {
                    // move forward
                    std::cout << "        " << ((curPt == pt) ? "· " : "  ");
                }
            }

            std::cout << "        ";

            if (curPt == pt) {
                std::cout << pt;
            } else {
                std::cout << "-";
            }

            std::cout << "" << std::endl;
        }
    }

    // go to the end
    for (int s = startIndex; s < csLen; ++s) {
        std::cout << "        " << ((s == csLen) ? "" : "· ");
    }

    // print the last (the lowest) value on y-axis
    std::cout << "        " << pt - dec << std::endl;
    std::cout << "" << std::endl;

    // x-axis
    for (int t = startIndex; t < csLen; ++t) {
        std::string sp = t == startIndex ? "    " : "  ";
        std::cout << sp << csPlot.getCandlestick(t).getTime();
    }
    
    std::cout << "" << std::endl;
}

void CsTextPlot::drawHorizontalPlot(std::vector<OrderBookEntry>& orderBookEntries, plotConfig& config) {
    CsPlot csPlot;
    csPlot.setCsPlot(orderBookEntries);
    
    // highest and lowest values of candlestick plot data
    double pHigh = csPlot.getHigh();
    double pLow = csPlot.getLow();

    // division increment value
    // 2 is substracted as we add an extra division at the start and the end of the plot,
    // so the plot gets exact divisions as config.divs on x-axis (and minimum 3 divisions as default)
    int divs = (config.divs < 3) ? 3 : config.divs;
    double inc = (pHigh - pLow) / (divs - 2);

    // minimum 2 sub-divisions by default
    int subDivs = (config.subDivs < 2) ? 2 : config.subDivs;
    double subInc = (inc / subDivs);
    double pt = 0;

    // get the reference of candlesticks
    std::vector<Candlestick>& candlesticks = csPlot.getCandlesticks();
    int csLen = candlesticks.size();
    int lastIndex = csLen - config.tail;

    // plot header
    std::cout << "" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "Product: " <<  csPlot.getProduct() << std::endl;
    std::cout << "OrderType: " << OrderBookEntry::orderBookTypeToString(csPlot.getOrderType()) << std::endl;
    std::cout << csPlot.getCandlestick(0).getDate() << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "" << std::endl;

    for (int i = csLen - 1; i >= lastIndex; --i) {
        std::string cTime = csPlot.getCandlestick(i).getTime();
        double cHigh = csPlot.getCandlestick(i).getHigh();
        double cLow = csPlot.getCandlestick(i).getLow();
        double close = csPlot.getCandlestick(i).getClose();
        double open = csPlot.getCandlestick(i).getOpen();
        double bg = close > open ? close : open;
        double sm = close > open ? open : close;
        std::string closeBr = (close >= open) ? "  |" : "|//";
        std::string openBr = (close >= open) ? "|  " : "//|";
        std::string smBoxFill = (close >= open) ? " " : "/";
        std::string boxFill = (close >= open) ? "   " : "///";

        // y-axis
        std::cout << cTime << " -         ";

        // x-axis
        for (double j = pLow - inc; j <= pHigh + subInc; j = j + inc) {
            pt = j;

            for (int k = 0; k < subDivs; ++k) {
                double curPt = (k == 0) ? pt : pt + (subInc * k); 
                double nxtPt = curPt + subInc;

                if (cLow >= curPt && cLow < nxtPt) {
                    std::cout << "———";
                } else if (cHigh >= curPt && cHigh < nxtPt) {
                    std::cout << "———";
                } else if (open >= curPt && open < nxtPt && close >= curPt && close < nxtPt) {
                    std::cout << "|" << smBoxFill << "|";
                } else if (open >= curPt && open < nxtPt) {
                    std::cout << openBr;
                } else if (close >= curPt && close < nxtPt) {
                    std::cout << closeBr;                    
                } else if (curPt >= sm && curPt <= bg) {
                    std::cout << boxFill;
                } else if (curPt >= cLow && curPt <= cHigh) {
                    std::cout << "———";
                } else {
                    // move forward
                    std::cout << ".  ";
                }
            }
        }
        std::cout << "" << std::endl;
    }

    // x-axis points to be implemented
}
