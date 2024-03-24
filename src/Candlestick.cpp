#include "Candlestick.h"

Candlestick::Candlestick(
    double _high, 
    double _low,
    double _close,
    double _open,
    std::string _timestamp
)
: high(_high),
  low(_low),
  close(_close),
  open(_open),
  timestamp(_timestamp) {
}
