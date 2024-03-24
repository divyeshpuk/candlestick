#pragma once

#include <string>

class Candlestick {
    public:
        Candlestick(
            double _high, 
            double _low,
            double _close,
            double _open,
            std::string _timestamp
        );

        void setHigh(double n) {
            high = n;
        }

        double getHigh() {
            return high;
        }

        void setLow(double n) {
            low = n;
        }

        double getLow() {
            return low;
        }

        void setClose(double n) {
            close = n;
        }

        double getClose() {
            return close;
        }

        void setOpen(double n) {
            open = n;
        }

        double getOpen() {
            return open;
        }

        std::string getTimestamp() {
            return timestamp;
        }

        std::string getDate() {
            return timestamp.substr(0, 10);
        }

        std::string getTime() {
            return timestamp.substr(11, 8);
        }
            
    private:
        double high;
        double low;
        double close;
        double open;
        std::string timestamp;
        std::string date;
        std::string time;
};
