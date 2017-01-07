#!/bin/sh

echo "start"
rm ../nodes/nodes.*

for i in `seq 0 9`; do
    for j in `seq 0 99`; do
        empty=
        if [ $j -lt 10 ]; then
            empty=0
        fi
        ratio=`expr $i \* 10`
        ./create ${ratio} > "../nodes/nodes.${i}.${empty}${j}.csv"

        echo -en "${i}`expr ${j} / 10`% end\r"
    done
done

echo "complete!"
