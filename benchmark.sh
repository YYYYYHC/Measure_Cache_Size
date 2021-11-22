#!/bin/sh
#./benchmark
gcc benchmark.c -o benchmark
echo "N,K,time" > result_time11_withoutN_changeN.csv
N=10
S=40
N_TIMES=100

#benchmark 5120000 $S $N_TIMES

#5120000

for varN in $(seq 1000000  10 5124000)
do
	echo $varN
	./benchmark $varN $S $N_TIMES
done

