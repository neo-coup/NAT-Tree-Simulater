#!/bin/sh

echo "start"

echo -n "" > "../avg/avg.csv"
echo ",input node,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000" >> "../avg/avg.csv"
echo "mobile ratio" >> "../avg/avg.csv"
for i in `seq 0 9`; do
    echo -n "${i},," >> "../avg/avg.csv"
    ./analyze ${i} >> "../avg/avg.csv"
done

echo "complete!"
