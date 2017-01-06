#!/bin/sh

echo "start"

for i in `seq 0 9`; do
    for j in `seq 0 99`; do
        empty=
        if [ $j -lt 10 ]; then
            empty=0
        fi
        ratio=$i*10
        ./main ${ratio} >> "../nodes/nodes.${i}.${empty}${j}.csv"

        echo -en "${i}`expr ${j} / 10` end%\r"
    done
done

echo "complete!"
