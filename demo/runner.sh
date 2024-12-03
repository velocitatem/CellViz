#!/bin/bash

BINARIES="/home/velocitatem/CLionProjects/CellViz/cmake-build-debug/"
STOCKS_LIST=(APPL GOOGL MSFT TSLA AMZN)
for STOCK in "${STOCKS_LIST[@]}"
do
  echo "Processing $STOCK"
  $BINARIES/data $STOCK
  $BINARIES/CellViz output.json $STOCK".mp4"
  rm -f frame*.png
done
rm -f output.json