#!/bin/sh

echo "start"

for i in `seq 0 9`; do
    for j in `seq 0 99`; do
        empty=
        if [ $j -lt 10 ]; then
            empty=0
        fi
        ratio=`expr $i \* 10`
        ./main "nodes/nodes.${i}.${empty}${j}.csv" "result/result.${i}.${empty}${j}.csv" > /dev/null
        echo -en "${i}`expr ${j} / 10`.`expr ${j} % 10`% end\r"
    done
done

echo "complete!"
