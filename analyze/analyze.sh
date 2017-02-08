#!/bin/sh

echo "start"

echo -n "" > "../avg/avg.csv"
for i in `seq 0 9`; do
    echo -n "${i},," >> "../avg/avg.csv"
    ./analyze ${i} >> "../avg/avg.csv"
done

echo "complete!"
