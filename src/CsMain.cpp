#include "CsMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "CsTextPlot.h"

CsMain::CsMain() {
}

void CsMain::init() {
    int input;

    // cache known products
    std::vector<std::string> products;
    for (std::string const& p : orderBook.getKnownProducts()) {
        products.push_back(p);
    }

    while(true) {
        std::cout << "" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "View the candlestick plot by product and type" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;

        struct item {           
            std::string product;
            OrderBookType orderBookType;
        };
        std::vector<item> items;
        int count = -1;

        // loop through cached known products
        for (std::string const& p : products) {
            count++;
            item i;
            i.product = p;
            i.orderBookType = OrderBookType::ask;
            items.push_back(i);

            std::cout << count << ": " << p << " " << OrderBookEntry::orderBookTypeToString(OrderBookType::ask) << std::endl;

            count++;
            item j;
            j.product = p;
            j.orderBookType = OrderBookType::bid;
            items.push_back(j);

            std::cout << count << ": " << p << " " << OrderBookEntry::orderBookTypeToString(OrderBookType::bid) << std::endl;
        }

        input = getUserOption();
        drawCsTextPlot(items[input].orderBookType, items[input].product);
    }
}

int CsMain::getUserOption() {
    int userOption = 0;
    std::string line;
    std::cout << "" << std::endl;
    std::cout << "Type in 0-9 to choose an option and press Enter" << std::endl;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    } catch(const std::exception& e) {
        // err
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void CsMain::drawCsTextPlot(OrderBookType orderBookType, std::string product) {
    std::vector<OrderBookEntry> entries = orderBook.getOrdersByTypeAndProduct(orderBookType, product);

    plotConfig config;
    config.type = CsPlotType::vertical; // vertical, horizontal
    config.tail = 18; // prints last 18 candlesticks, can be any positive integer
    // divisions and sub-divisions on the axis (y-axis for vertical, x-axis for horizontal)
    config.divs = 12; // can be any positive integer > 2
    config.subDivs = 4; // can be any positive integer > 1

    CsTextPlot csTextPlot;
    csTextPlot.drawCsTextPlot(entries, config);
}
