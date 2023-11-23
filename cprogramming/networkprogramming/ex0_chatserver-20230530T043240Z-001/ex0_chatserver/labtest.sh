#!/bin/bash

# input
rm -f a.out *.JPG _allmsg.txt _totalmsg.txt _tempout_* _kk1 _kk2 _uid*.sh _tempoutall.txt _user*.txt

src=$1;
port=$2;

echo $1 $2

gcc -pthread $src 
./a.out $port &

sleep 2
usercnt=8
#usercnt=3
count=1
while [ "$count" -le $usercnt ]
do
	userid=uid$count..$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 5 | head -n 1)
	echo "" > _$userid.sh
	echo "sleep" $(($RANDOM%5+3)) >> _$userid.sh
	cnt=$(($RANDOM%6+5)) 
	echo $cnt
	for ((i=1;i<=cnt;i++)); do
		strlen=$(($RANDOM%30+5)) 
		newstr=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $strlen | head -n 1 | sed 's/S/ /g' | sed 's/K/ /g')
		echo "echo" $userid $newstr >> _$userid.sh
		echo $userid $newstr >> _allmsg.txt
		sltms=$(($RANDOM%4)).$(($RANDOM%1000))
		echo "sleep" $sltms >> _$userid.sh
	done
	echo "sleep 50" >> _$userid.sh

	bash _$userid.sh | telnet localhost $port > _tempout_$count &
	let "count += 1"  # 카운터 증가.
done



sleep 120
echo "Programs ended"

sleep 1
killall -q  a.out 

count=1
succcnt=0
while [ "$count" -le $usercnt ]
do
	grep -v uid$count.. _allmsg.txt > _user$count.txt
	sort _user$count.txt > _kk1
	grep "^uid"  _tempout_$count | sort  > _kk2
	diff _kk1 _kk2
	if [[ $? == 0 ]];
	then
		let "succcnt += 1"  # 카운터 증가.
	fi
	let "count += 1"  # 카운터 증가.
done


echo "Result: " $succcnt $src



rm -f a.out *.JPG _allmsg.txt _totalmsg.txt _tempout_* _kk1 _kk2 _uid*.sh _tempoutall.txt _user*.txt
