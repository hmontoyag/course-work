#!/bin/bash

username="hmontoya@csora"
pword="a0axT5SE"

# echo $1
# echo $2
echo "$1"

get_result () {
	sqlplus -s $1/$2 << EOF
	whenever sqlerror exit 1;
	set echo on
	SET FEEDBACK OFF 
	set pagesize 0
	set wrap off
	set linesize 200
	$3
	exit
EOF
}

if [[ -z "$1"  ]] 
then
	echo "Test all sql querys"
	count=0
	for i in {1..10};
	do
		echo Query"$i";
		sql=$(awk -v n=$i '/-- Query/{l++;next}(l==n){print}' answer.sql)
		echo "---- student query:"
		echo "$sql"
		echo "---- result:"
		v1=$(get_result "$username" "$pword" "$sql")
		echo "$v1"
		# echo ">>>Query$i" >> result.txt
		# echo "$v1" >> result.txt
		ans=$(awk -v n=$i '/>>>Query/{l++;next}(l==n){print}' result.txt )
		if [[ "$v1" = "$ans" ]]
		then
			echo -e "\e[42mPass\e[0m"
			count=$((count + 1))
		else
			echo -e "\e[31mFail\e[0m"
			echo "Expected:"
			echo "$ans"
		fi
		echo -e "\e[34m====================================\e[0m"
	done
	echo -e "+++++ Total pass: \e[32m$count\e[0m"
else 
	echo ">>> Test Query$1 "
	sql=$(awk -v n=$1 '/-- Query/{l++;next}(l==n){print}' answer.sql)
	echo "---- student query:"
	echo "$sql"
	v1=$(get_result "$username" "$pword" "$sql")
	echo "---- result of Query$1"
	for i in "${v1[@]}"
	do
		echo "$i"
	done
	ans=$(awk -v n=$1 '/>>>Query/{l++;next}(l==n){print}' result.txt)
	if [[ "$v1" = "$ans" ]]
	then
		echo -e "\e[42mPass\e[0m"
	else
		echo -e "\e[31mFail\e[0m"
		echo "Expected:"
		echo "$ans"
	fi
fi
