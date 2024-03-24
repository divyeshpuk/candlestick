# Candlestick
<h3>Compile and run:</h3>
<code>g++ main.cpp CsMain.cpp Candlestick.cpp CsPlot.cpp CsTextPlot.cpp CSVReader.cpp OrderBook.cpp OrderBookEntry.cpp && ./a.out</code>

<h3>View the candlestick plot:</h3>
<p>Type in 0-9 to choose the specific product and type (ask or bid), and press Enter.</p>

<h3>Plot parameters</h3>
<code>type</code>
<p>Type of plot, vertical or horizontal.</p>
<code>vertical</code>
<p>Vertical plot: x-axis is timeframe, y-axis is price.</p>
<code>horizontal</code>
<p>Horizontal plot: x-axis is price, y-axis is timeframe.</p>
<hr>
<code>tail</code>
<p>The value for the number of last candlesticks in a timeframe.</p>
<hr>
<code>divs</code>
<p>The number of divisions on the axis (y-axis for vertical plot, x-axis for horizontal plot).</p>
<hr>
<code>subDivs</code>
<p>The number of sub-divisions between the points on the axis (y-axis for vertical plot, x-axis for horizontal plot).</p>