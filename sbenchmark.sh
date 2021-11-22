#!/bin/sh
#./benchmark
gcc sbenchmark.c -o sbenchmark -fno-stack-protector
echo 's,k,time' > result_time11_withoutN_changes.csv
N=10
S=1
N_TIMES=25

#220000000
#./sbenchmark 1280000 $S $N_TIMES

#for varN in $(seq 10000000 100000000)
#do
#	echo $varN
#	./benchmark $varN $S $N_TIMES
#done

C=6192000


#for varS in $(seq 1 256)
#do
#	./sbenchmark $C $varS $N_TIMES
#done



./sbenchmark $C 1 $N_TIMES
#./sbenchmark $C 2 $N_TIMES
i=2
while [ $i -le 3096000 ] 
do
	./sbenchmark $C $i $N_TIMES
	
	let i+=i/2

done
